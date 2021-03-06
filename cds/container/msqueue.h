//$$CDS-header$$

#ifndef __CDS_CONTAINER_MSQUEUE_H
#define __CDS_CONTAINER_MSQUEUE_H

#include <memory>
#include <functional>   // ref
#include <cds/intrusive/msqueue.h>
#include <cds/container/details/base.h>
#include <cds/details/trivial_assign.h>

namespace cds { namespace container {

    //@cond
    namespace details {
        template <typename GC, typename T, typename... Options>
        struct make_msqueue
        {
            typedef GC gc;
            typedef T value_type;

            struct default_options {
                typedef cds::backoff::empty     back_off;
                typedef CDS_DEFAULT_ALLOCATOR   allocator;
                typedef atomicity::empty_item_counter item_counter;
                typedef intrusive::queue_dummy_stat stat;
                typedef opt::v::relaxed_ordering    memory_model;
                enum { alignment = opt::cache_line_alignment };
            };

            typedef typename opt::make_options<
                typename cds::opt::find_type_traits< default_options, Options... >::type
                ,Options...
            >::type   options;

            struct node_type: public intrusive::single_link::node< gc >
            {
                value_type  m_value;
                node_type( const value_type& val )
                    : m_value( val )
                {}

                template <typename... Args>
                node_type( Args&&... args )
                    : m_value( std::forward<Args>(args)...)
                {}
            };

            typedef typename options::allocator::template rebind<node_type>::other allocator_type;
            typedef cds::details::Allocator< node_type, allocator_type >           cxx_allocator;

            struct node_deallocator
            {
                void operator ()( node_type * pNode )
                {
                    cxx_allocator().Delete( pNode );
                }
            };

            typedef intrusive::MSQueue< gc,
                node_type
                ,intrusive::opt::hook<
                    intrusive::single_link::base_hook< opt::gc<gc> >
                >
                ,opt::back_off< typename options::back_off >
                ,intrusive::opt::disposer< node_deallocator >
                ,opt::item_counter< typename options::item_counter >
                ,opt::stat< typename options::stat >
                ,opt::alignment< options::alignment >
                ,opt::memory_model< typename options::memory_model >
            >   type;
        };
    }
    //@endcond

    /// Michael & Scott lock-free queue
    /** @ingroup cds_nonintrusive_queue
        It is non-intrusive version of Michael & Scott's queue algorithm based on intrusive implementation
        intrusive::MSQueue.

        Template arguments:
        - \p GC - garbage collector type: gc::HP, gc::HRC, gc::PTB
        - \p T is a type stored in the queue. It should be default-constructible, copy-constructible, assignable type.
        - \p Options - options

        Permissible \p Options:
        - opt::allocator - allocator (like \p std::allocator). Default is \ref CDS_DEFAULT_ALLOCATOR
        - opt::back_off - back-off strategy used. If the option is not specified, the cds::backoff::empty is used
        - opt::item_counter - the type of item counting feature. Default is \ref atomicity::empty_item_counter
        - opt::stat - the type to gather internal statistics.
            Possible option value are: intrusive::queue_stat, intrusive::queue_dummy_stat,
            user-provided class that supports intrusive::queue_stat interface.
            Default is \ref intrusive::queue_dummy_stat.
        - opt::alignment - the alignment for internal queue data. Default is opt::cache_line_alignment
        - opt::memory_model - C++ memory ordering model. Can be opt::v::relaxed_ordering (relaxed memory model, the default)
            or opt::v::sequential_consistent (sequentially consisnent memory model).
    */
    template <typename GC, typename T, typename... Options>
    class MSQueue:
#ifdef CDS_DOXYGEN_INVOKED
        intrusive::MSQueue< GC, intrusive::single_link::node< T >, Options... >
#else
        details::make_msqueue< GC, T, Options... >::type
#endif
    {
        //@cond
        typedef details::make_msqueue< GC, T, Options... > options;
        typedef typename options::type base_class;
        //@endcond

    public:
        /// Rebind template arguments
        template <typename GC2, typename T2, typename... Options2>
        struct rebind {
            typedef MSQueue< GC2, T2, Options2...> other   ;   ///< Rebinding result
        };

    public:
        typedef T value_type ; ///< Value type stored in the queue

        typedef typename base_class::gc             gc              ; ///< Garbage collector used
        typedef typename base_class::back_off       back_off        ; ///< Back-off strategy used
        typedef typename options::allocator_type    allocator_type  ; ///< Allocator type used for allocate/deallocate the nodes
        typedef typename base_class::item_counter   item_counter    ; ///< Item counting policy used
        typedef typename base_class::stat           stat            ; ///< Internal statistics policy used
        typedef typename base_class::memory_model   memory_model    ; ///< Memory ordering. See cds::opt::memory_model option

    protected:
        typedef typename options::node_type  node_type   ;   ///< queue node type (derived from intrusive::single_link::node)

        //@cond
        typedef typename options::cxx_allocator     cxx_allocator;
        typedef typename options::node_deallocator  node_deallocator;   // deallocate node
        typedef typename base_class::node_traits    node_traits;
        //@endcond

    protected:
        ///@cond
        static node_type * alloc_node()
        {
            return cxx_allocator().New();
        }
        static node_type * alloc_node( value_type const& val )
        {
            return cxx_allocator().New( val );
        }
        template <typename... Args>
        static node_type * alloc_node_move( Args&&... args )
        {
            return cxx_allocator().MoveNew( std::forward<Args>( args )... );
        }
        static void free_node( node_type * p )
        {
            node_deallocator()( p );
        }

        struct node_disposer {
            void operator()( node_type * pNode )
            {
                free_node( pNode );
            }
        };
        typedef std::unique_ptr< node_type, node_disposer >     scoped_node_ptr;
        //@endcond

    public:
        /// Initializes empty queue
        MSQueue()
        {}

        /// Destructor clears the queue
        ~MSQueue()
        {}

        /// Returns queue's item count (see \ref intrusive::MSQueue::size for explanation)
        size_t size() const
        {
            return base_class::size();
        }

        /// Returns reference to internal statistics
        const stat& statistics() const
        {
            return base_class::statistics();
        }

        /// Enqueues \p val value into the queue.
        /**
            The function makes queue node in dynamic memory calling copy constructor for \p val
            and then it calls intrusive::MSQueue::enqueue.
            Returns \p true if success, \p false otherwise.
        */
        bool enqueue( value_type const& val )
        {
            scoped_node_ptr p( alloc_node(val) );
            if ( base_class::enqueue( *p ) ) {
                p.release();
                return true;
            }
            return false;
        }

        /// Enqueues \p data to queue using copy functor
        /**
            \p Func is a functor called to copy value \p data of type \p Type
            which may be differ from type \ref value_type stored in the queue.
            The functor's interface is:
            \code
            struct myFunctor {
                void operator()(value_type& dest, Type const& data)
                {
                    // // Code to copy \p data to \p dest
                    dest = data;
                }
            };
            \endcode
            You may use \p boost:ref construction to pass functor \p f by reference.

            <b>Requirements</b> The functor \p Func should not throw any exception.
        */
        template <typename Type, typename Func>
        bool enqueue( Type const& data, Func f  )
        {
            scoped_node_ptr p( alloc_node() );
            f( p->m_value, data );
            if ( base_class::enqueue( *p )) {
                p.release();
                return true;
            }
            return false;
        }

        /// Dequeues a value using copy functor
        /**
            \p Func is a functor called to copy dequeued value to \p dest of type \p Type
            which may be differ from type \ref value_type stored in the queue.
            The functor's interface is:
            \code
            struct myFunctor {
                void operator()(Type& dest, value_type const& data)
                {
                    // Code to copy \p data to \p dest
                    dest = data;
                }
            };
            \endcode
            You may use \p boost:ref construction to pass functor \p f by reference.

            <b>Requirements</b> The functor \p Func should not throw any exception.
        */
        template <typename Type, typename Func>
        bool dequeue( Type& dest, Func f )
        {
            typename base_class::dequeue_result res;
            if ( base_class::do_dequeue( res )) {
                f( dest, node_traits::to_value_ptr( *res.pNext )->m_value );

                base_class::dispose_result( res );

                return true;
            }
            return false;
        }

        /// Dequeues a value from the queue
        /**
            If queue is not empty, the function returns \p true, \p dest contains copy of
            dequeued value. The assignment operator for type \ref value_type is invoked.
            If queue is empty, the function returns \p false, \p dest is unchanged.
        */
        bool dequeue( value_type& dest )
        {
            typedef cds::details::trivial_assign<value_type, value_type> functor;
            return dequeue( dest, functor() );
        }

        /// Synonym for \ref enqueue function
        bool push( value_type const& val )
        {
            return enqueue( val );
        }

        /// Synonym for template version of \ref enqueue function
        template <typename Type, typename Func>
        bool push( Type const& data, Func f  )
        {
            return enqueue( data, f );
        }

        /// Synonym for \ref dequeue function
        bool pop( value_type& dest )
        {
            return dequeue( dest );
        }

        /// Synonym for template version of \ref dequeue function
        template <typename Type, typename Func>
        bool pop( Type& dest, Func f )
        {
            return dequeue( dest, f );
        }

        /// Enqueues data of type \ref value_type constructed with <tt>std::forward<Args>(args)...</tt>
        template <typename... Args>
        bool emplace( Args&&... args )
        {
            scoped_node_ptr p( alloc_node_move( std::forward<Args>(args)... ) );
            if ( base_class::enqueue( *p )) {
                p.release();
                return true;
            }
            return false;
        }

        /// Checks if the queue is empty
        bool empty() const
        {
            return base_class::empty();
        }

        /// Clear the queue
        /**
            The function repeatedly calls \ref dequeue until it returns \p nullptr.
        */
        void clear()
        {
            base_class::clear();
        }
    };

}}  // namespace cds::container

#endif  // #ifndef __CDS_CONTAINER_MSQUEUE_H
