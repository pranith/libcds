//$$CDS-header$$

#ifndef __CDS_CONTAINER_IMPL_ELLEN_BINTREE_SET_H
#define __CDS_CONTAINER_IMPL_ELLEN_BINTREE_SET_H

#include <type_traits>
#include <cds/container/details/ellen_bintree_base.h>
#include <cds/intrusive/impl/ellen_bintree.h>
#include <cds/container/details/guarded_ptr_cast.h>

namespace cds { namespace container {

    /// Set based on Ellen's et al binary search tree
    /** @ingroup cds_nonintrusive_set
        @ingroup cds_nonintrusive_tree
        @anchor cds_container_EllenBinTreeSet

        Source:
            - [2010] F.Ellen, P.Fatourou, E.Ruppert, F.van Breugel "Non-blocking Binary Search Tree"

        %EllenBinTreeSet is an unbalanced leaf-oriented binary search tree that implements the <i>set</i>
        abstract data type. Nodes maintains child pointers but not parent pointers.
        Every internal node has exactly two children, and all data of type \p T currently in
        the tree are stored in the leaves. Internal nodes of the tree are used to direct \p find
        operation along the path to the correct leaf. The keys (of \p Key type) stored in internal nodes
        may or may not be in the set. \p Key type is a subset of \p T type.
        There should be exactly defined a key extracting functor for converting object of type \p T to
        object of type \p Key.

        Due to \p extract_min and \p extract_max member functions the \p %EllenBinTreeSet can act as
        a <i>priority queue</i>. In this case you should provide unique compound key, for example,
        the priority value plus some uniformly distributed random value.

        @warning Recall the tree is <b>unbalanced</b>. The complexity of operations is <tt>O(log N)</tt>
        for uniformly distributed random keys, but in worst case the complexity is <tt>O(N)</tt>.

        @note In the current implementation we do not use helping technique described in original paper.
        So, the current implementation is near to fine-grained lock-based tree.
        Helping will be implemented in future release

        <b>Template arguments</b> :
        - \p GC - safe memory reclamation (i.e. light-weight garbage collector) type, like cds::gc::HP, cds::gc::PTB
            Note that cds::gc::HRC is not supported.
        - \p Key - key type, a subset of \p T
        - \p T - type to be stored in tree's leaf nodes.
        - \p Traits - type traits. See ellen_bintree::type_traits for explanation.

        It is possible to declare option-based tree with ellen_bintree::make_set_traits metafunction
        instead of \p Traits template argument.
        Template argument list \p Options of ellen_bintree::make_set_traits metafunction are:
        - ellen_bintree::key_extractor - key extracting functor, mandatory option. The functor has the following prototype:
            \code
                struct key_extractor {
                    void operator ()( Key& dest, T const& src );
                };
            \endcode
            It should initialize \p dest key from \p src data. The functor is used to initialize internal nodes.
        - opt::compare - key compare functor. No default functor is provided.
            If the option is not specified, \p %opt::less is used.
        - opt::less - specifies binary predicate used for key compare. At least \p %opt::compare or \p %opt::less should be defined.
        - opt::item_counter - the type of item counting feature. Default is \ref atomicity::empty_item_counter that is no item counting.
        - opt::memory_model - C++ memory ordering model. Can be opt::v::relaxed_ordering (relaxed memory model, the default)
            or opt::v::sequential_consistent (sequentially consisnent memory model).
        - opt::allocator - the allocator used for \ref ellen_bintree::node "leaf nodes" which contains data.
            Default is \ref CDS_DEFAULT_ALLOCATOR.
        - opt::node_allocator - the allocator used for internal nodes. Default is \ref CDS_DEFAULT_ALLOCATOR.
        - ellen_bintree::update_desc_allocator - an allocator of \ref ellen_bintree::update_desc "update descriptors",
            default is \ref CDS_DEFAULT_ALLOCATOR.
            Note that update descriptor is helping data structure with short lifetime and it is good candidate for pooling.
            The number of simultaneously existing descriptors is a relatively small number limited the number of threads
            working with the tree and GC buffer size.
            Therefore, a bounded lock-free container like \p cds::container::VyukovMPMCCycleQueue is good choice for the free-list
            of update descriptors, see cds::memory::vyukov_queue_pool free-list implementation.
            Also notice that size of update descriptor is not dependent on the type of data
            stored in the tree so single free-list object can be used for several EllenBinTree-based object.
        - opt::stat - internal statistics. Available types: ellen_bintree::stat, ellen_bintree::empty_stat (the default)

        @note Do not include <tt><cds/container/impl/ellen_bintree_set.h></tt> header file directly.
        There are header file for each GC type:
        - <tt><cds/container/ellen_bintree_set_hp.h></tt> - for Hazard Pointer GC cds::gc::HP
        - <tt><cds/container/ellen_bintree_set_ptb.h></tt> - for Pass-the-Buck GC cds::gc::PTB
        - <tt><cds/container/ellen_bintree_set_rcu.h></tt> - for RCU GC
            (see \ref cds_container_EllenBinTreeSet_rcu "RCU-based EllenBinTreeSet")

        @anchor cds_container_EllenBinTreeSet_less
        <b>Predicate requirements</b>

        opt::less, opt::compare and other predicates using with member fuctions should accept at least parameters
        of type \p T and \p Key in any combination.
        For example, for \p Foo struct with \p std::string key field the appropiate \p less functor is:
        \code
        struct Foo
        {
            std::string m_strKey;
            ...
        };

        struct less {
            bool operator()( Foo const& v1, Foo const& v2 ) const
            { return v1.m_strKey < v2.m_strKey ; }

            bool operator()( Foo const& v, std::string const& s ) const
            { return v.m_strKey < s ; }

            bool operator()( std::string const& s, Foo const& v ) const
            { return s < v.m_strKey ; }

            // Support comparing std::string and char const *
            bool operator()( std::string const& s, char const * p ) const
            { return s.compare(p) < 0 ; }

            bool operator()( Foo const& v, char const * p ) const
            { return v.m_strKey.compare(p) < 0 ; }

            bool operator()( char const * p, std::string const& s ) const
            { return s.compare(p) > 0; }

            bool operator()( char const * p, Foo const& v ) const
            { return v.m_strKey.compare(p) > 0; }
        };
        \endcode
    */
    template <
        class GC,
        typename Key,
        typename T,
#ifdef CDS_DOXYGEN_INVOKED
        class Traits = ellen_bintree::type_traits
#else
        class Traits
#endif
    >
    class EllenBinTreeSet
#ifdef CDS_DOXYGEN_INVOKED
        : public cds::intrusive::EllenBinTree< GC, Key, T, Traits >
#else
        : public ellen_bintree::details::make_ellen_bintree_set< GC, Key, T, Traits >::type
#endif
    {
        //@cond
        typedef ellen_bintree::details::make_ellen_bintree_set< GC, Key, T, Traits > maker;
        typedef typename maker::type base_class;
        //@endcond

    public:
        typedef GC      gc              ;   ///< Garbage collector
        typedef Key     key_type        ;   ///< type of a key stored in internal nodes; key is a part of \p value_type
        typedef T       value_type      ;   ///< type of value stored in the binary tree
        typedef Traits  options         ;   ///< Traits template parameter

#   ifdef CDS_DOXYGEN_INVOKED
        typedef implementation_defined key_comparator  ;    ///< key compare functor based on opt::compare and opt::less option setter.
#   else
        typedef typename maker::intrusive_type_traits::compare   key_comparator;
#   endif
        typedef typename base_class::item_counter           item_counter        ; ///< Item counting policy used
        typedef typename base_class::memory_model           memory_model        ; ///< Memory ordering. See cds::opt::memory_model option
        typedef typename base_class::stat                   stat                ; ///< internal statistics type
        typedef typename options::key_extractor             key_extractor       ; ///< key extracting functor

        typedef typename options::allocator                 allocator_type      ;   ///< Allocator for leaf nodes
        typedef typename base_class::node_allocator         node_allocator      ;   ///< Internal node allocator
        typedef typename base_class::update_desc_allocator  update_desc_allocator ; ///< Update descriptor allocator

    protected:
        //@cond
        typedef typename maker::cxx_leaf_node_allocator cxx_leaf_node_allocator;
        typedef typename base_class::value_type         leaf_node;
        typedef typename base_class::internal_node      internal_node;

        typedef std::unique_ptr< leaf_node, typename maker::leaf_deallocator > scoped_node_ptr;
        //@endcond

    public:
        /// Guarded pointer
        typedef cds::gc::guarded_ptr< gc, leaf_node, value_type, details::guarded_ptr_cast_set<leaf_node, value_type> > guarded_ptr;

    public:
        /// Default constructor
        EllenBinTreeSet()
            : base_class()
        {
            //static_assert( (std::is_same<gc, cds::gc::HP>::value || std::is_same<gc, cds::gc::PTB>::value), "GC must be cds::gc::HP or cds:gc::PTB" );
        }

        /// Clears the set
        ~EllenBinTreeSet()
        {}

        /// Inserts new node
        /**
            The function creates a node with copy of \p val value
            and then inserts the node created into the set.

            The type \p Q should contain at least the complete key for the node.
            The object of \ref value_type should be constructible from a value of type \p Q.
            In trivial case, \p Q is equal to \ref value_type.

            Returns \p true if \p val is inserted into the set, \p false otherwise.
        */
        template <typename Q>
        bool insert( Q const& val )
        {
            scoped_node_ptr sp( cxx_leaf_node_allocator().New( val ));
            if ( base_class::insert( *sp.get() )) {
                sp.release();
                return true;
            }
            return false;
        }

        /// Inserts new node
        /**
            The function allows to split creating of new item into two part:
            - create item with key only
            - insert new item into the set
            - if inserting is success, calls  \p f functor to initialize value-fields of \p val.

            The functor signature is:
            \code
                void func( value_type& val );
            \endcode
            where \p val is the item inserted. User-defined functor \p f should guarantee that during changing
            \p val no any other changes could be made on this set's item by concurrent threads.
            The user-defined functor is called only if the inserting is success. It may be passed by reference
            using \p std::ref
        */
        template <typename Q, typename Func>
        bool insert( Q const& val, Func f )
        {
            scoped_node_ptr sp( cxx_leaf_node_allocator().New( val ));
            if ( base_class::insert( *sp.get(), [&f]( leaf_node& val ) { f( val.m_Value ); } )) {
                sp.release();
                return true;
            }
            return false;
        }

        /// Ensures that the item exists in the set
        /**
            The operation performs inserting or changing data with lock-free manner.

            If the \p val key not found in the set, then the new item created from \p val
            is inserted into the set. Otherwise, the functor \p func is called with the item found.
            The functor \p Func should be a function with signature:
            \code
                void func( bool bNew, value_type& item, const Q& val );
            \endcode
            or a functor:
            \code
                struct my_functor {
                    void operator()( bool bNew, value_type& item, const Q& val );
                };
            \endcode

            with arguments:
            - \p bNew - \p true if the item has been inserted, \p false otherwise
            - \p item - item of the set
            - \p val - argument \p key passed into the \p ensure function

            The functor may change non-key fields of the \p item; however, \p func must guarantee
            that during changing no any other modifications could be made on this item by concurrent threads.

            You may pass \p func argument by reference using \p std::ref.

            Returns <tt> std::pair<bool, bool> </tt> where \p first is true if operation is successfull,
            \p second is true if new item has been added or \p false if the item with \p key
            already is in the set.
        */
        template <typename Q, typename Func>
        std::pair<bool, bool> ensure( const Q& val, Func func )
        {
            scoped_node_ptr sp( cxx_leaf_node_allocator().New( val ));
            std::pair<bool, bool> bRes = base_class::ensure( *sp,
                [&func, &val](bool bNew, leaf_node& node, leaf_node&){ func( bNew, node.m_Value, val ); });
            if ( bRes.first && bRes.second )
                sp.release();
            return bRes;
        }

        /// Inserts data of type \ref value_type constructed with <tt>std::forward<Args>(args)...</tt>
        /**
            Returns \p true if inserting successful, \p false otherwise.
        */
        template <typename... Args>
        bool emplace( Args&&... args )
        {
            scoped_node_ptr sp( cxx_leaf_node_allocator().New( std::forward<Args>(args)... ));
            if ( base_class::insert( *sp.get() )) {
                sp.release();
                return true;
            }
            return false;
        }

        /// Delete \p key from the set
        /** \anchor cds_nonintrusive_EllenBinTreeSet_erase_val

            The item comparator should be able to compare the type \p value_type
            and the type \p Q.

            Return \p true if key is found and deleted, \p false otherwise
        */
        template <typename Q>
        bool erase( Q const& key )
        {
            return base_class::erase( key );
        }

        /// Deletes the item from the set using \p pred predicate for searching
        /**
            The function is an analog of \ref cds_nonintrusive_EllenBinTreeSet_erase_val "erase(Q const&)"
            but \p pred is used for key comparing.
            \p Less functor has the interface like \p std::less.
            \p Less must imply the same element order as the comparator used for building the set.
        */
        template <typename Q, typename Less>
        bool erase_with( Q const& key, Less pred )
        {
            return base_class::erase_with( key, cds::details::predicate_wrapper< leaf_node, Less, typename maker::value_accessor >());
        }

        /// Delete \p key from the set
        /** \anchor cds_nonintrusive_EllenBinTreeSet_erase_func

            The function searches an item with key \p key, calls \p f functor
            and deletes the item. If \p key is not found, the functor is not called.

            The functor \p Func interface:
            \code
            struct extractor {
                void operator()(value_type const& val);
            };
            \endcode
            The functor may be passed by reference using <tt>boost:ref</tt>

            Since the key of MichaelHashSet's \p value_type is not explicitly specified,
            template parameter \p Q defines the key type searching in the list.
            The list item comparator should be able to compare the type \p T of list item
            and the type \p Q.

            Return \p true if key is found and deleted, \p false otherwise
        */
        template <typename Q, typename Func>
        bool erase( Q const& key, Func f )
        {
            return base_class::erase( key, [&f]( leaf_node const& node) { f( node.m_Value ); } );
        }

        /// Deletes the item from the set using \p pred predicate for searching
        /**
            The function is an analog of \ref cds_nonintrusive_EllenBinTreeSet_erase_func "erase(Q const&, Func)"
            but \p pred is used for key comparing.
            \p Less functor has the interface like \p std::less.
            \p Less must imply the same element order as the comparator used for building the set.
        */
        template <typename Q, typename Less, typename Func>
        bool erase_with( Q const& key, Less pred, Func f )
        {
            return base_class::erase_with( key, cds::details::predicate_wrapper< leaf_node, Less, typename maker::value_accessor >(),
                [&f]( leaf_node const& node) { f( node.m_Value ); } );
        }

        /// Extracts an item with minimal key from the set
        /**
            If the set is not empty, the function returns \p true, \p result contains a pointer to minimum value.
            If the set is empty, the function returns \p false, \p result is left unchanged.

            @note Due the concurrent nature of the set, the function extracts <i>nearly</i> minimum key.
            It means that the function gets leftmost leaf of the tree and tries to unlink it.
            During unlinking, a concurrent thread may insert an item with key less than leftmost item's key.
            So, the function returns the item with minimum key at the moment of tree traversing.

            The guarded pointer \p dest prevents deallocation of returned item,
            see cds::gc::guarded_ptr for explanation.
            @note Each \p guarded_ptr object uses the GC's guard that can be limited resource.
        */
        bool extract_min( guarded_ptr& result )
        {
            return base_class::extract_min_( result.guard() );
        }

        /// Extracts an item with maximal key from the set
        /**
            If the set is not empty, the function returns \p true, \p result contains a pointer to maximal value.
            If the set is empty, the function returns \p false, \p result is left unchanged.

            @note Due the concurrent nature of the set, the function extracts <i>nearly</i> maximal key.
            It means that the function gets rightmost leaf of the tree and tries to unlink it.
            During unlinking, a concurrent thread may insert an item with key great than leftmost item's key.
            So, the function returns the item with maximum key at the moment of tree traversing.

            The guarded pointer \p dest prevents deallocation of returned item,
            see cds::gc::guarded_ptr for explanation.
            @note Each \p guarded_ptr object uses the GC's guard that can be limited resource.
        */
        bool extract_max( guarded_ptr& result )
        {
            return base_class::extract_max_( result.guard() );
        }

        /// Extracts an item from the tree
        /** \anchor cds_nonintrusive_EllenBinTreeSet_extract
            The function searches an item with key equal to \p key in the tree,
            unlinks it, and returns pointer to an item found in \p result parameter.
            If the item  is not found the function returns \p false.

            The guarded pointer \p dest prevents deallocation of returned item,
            see cds::gc::guarded_ptr for explanation.
            @note Each \p guarded_ptr object uses the GC's guard that can be limited resource.
        */
        template <typename Q>
        bool extract( guarded_ptr& result, Q const& key )
        {
            return base_class::extract_( result.guard(), key );
        }

        /// Extracts an item from the set using \p pred for searching
        /**
            The function is an analog of \ref cds_nonintrusive_EllenBinTreeSet_extract "extract(guarded_ptr& dest, Q const&)"
            but \p pred is used for key compare.
            \p Less has the interface like \p std::less.
            \p pred must imply the same element order as the comparator used for building the set.
        */
        template <typename Q, typename Less>
        bool extract_with( guarded_ptr& result, Q const& key, Less pred )
        {
            return base_class::extract_with_( result.guard(), key,
                cds::details::predicate_wrapper< leaf_node, Less, typename maker::value_accessor >());
        }

        /// Find the key \p val
        /**
            @anchor cds_nonintrusive_EllenBinTreeSet_find_func

            The function searches the item with key equal to \p val and calls the functor \p f for item found.
            The interface of \p Func functor is:
            \code
            struct functor {
                void operator()( value_type& item, Q& val );
            };
            \endcode
            where \p item is the item found, \p val is the <tt>find</tt> function argument.

            You may pass \p f argument by reference using \p std::ref.

            The functor may change non-key fields of \p item. Note that the functor is only guarantee
            that \p item cannot be disposed during functor is executing.
            The functor does not serialize simultaneous access to the set's \p item. If such access is
            possible you must provide your own synchronization schema on item level to exclude unsafe item modifications.

            The \p val argument is non-const since it can be used as \p f functor destination i.e., the functor
            can modify both arguments.

            Note the hash functor specified for class \p Traits template parameter
            should accept a parameter of type \p Q that may be not the same as \p value_type.

            The function returns \p true if \p val is found, \p false otherwise.
        */
        template <typename Q, typename Func>
        bool find( Q& val, Func f )
        {
            return base_class::find( val, [&f]( leaf_node& node, Q& v ) { f( node.m_Value, v ); });
        }

        /// Finds the key \p val using \p pred predicate for searching
        /**
            The function is an analog of \ref cds_nonintrusive_EllenBinTreeSet_find_func "find(Q&, Func)"
            but \p pred is used for key comparing.
            \p Less functor has the interface like \p std::less.
            \p Less must imply the same element order as the comparator used for building the set.
        */
        template <typename Q, typename Less, typename Func>
        bool find_with( Q& val, Less pred, Func f )
        {
            return base_class::find_with( val, cds::details::predicate_wrapper< leaf_node, Less, typename maker::value_accessor >(),
                [&f]( leaf_node& node, Q& v ) { f( node.m_Value, v ); } );
        }

        /// Find the key \p val
        /** @anchor cds_nonintrusive_EllenBinTreeSet_find_cfunc

            The function searches the item with key equal to \p val and calls the functor \p f for item found.
            The interface of \p Func functor is:
            \code
            struct functor {
                void operator()( value_type& item, Q const& val );
            };
            \endcode
            where \p item is the item found, \p val is the <tt>find</tt> function argument.

            You may pass \p f argument by reference using \p std::ref.

            The functor may change non-key fields of \p item. Note that the functor is only guarantee
            that \p item cannot be disposed during functor is executing.
            The functor does not serialize simultaneous access to the set's \p item. If such access is
            possible you must provide your own synchronization schema on item level to exclude unsafe item modifications.

            Note the hash functor specified for class \p Traits template parameter
            should accept a parameter of type \p Q that may be not the same as \p value_type.

            The function returns \p true if \p val is found, \p false otherwise.
        */
        template <typename Q, typename Func>
        bool find( Q const& val, Func f )
        {
            return base_class::find( val, [&f]( leaf_node& node, Q const& v ) { f( node.m_Value, v ); });
        }

        /// Finds the key \p val using \p pred predicate for searching
        /**
            The function is an analog of \ref cds_nonintrusive_EllenBinTreeSet_find_cfunc "find(Q const&, Func)"
            but \p pred is used for key comparing.
            \p Less functor has the interface like \p std::less.
            \p Less must imply the same element order as the comparator used for building the set.
        */
        template <typename Q, typename Less, typename Func>
        bool find_with( Q const& val, Less pred, Func f )
        {
            return base_class::find_with( val, cds::details::predicate_wrapper< leaf_node, Less, typename maker::value_accessor >(),
                [&f]( leaf_node& node, Q const& v ) { f( node.m_Value, v ); } );
        }

        /// Find the key \p val
        /** @anchor cds_nonintrusive_EllenBinTreeSet_find_val

            The function searches the item with key equal to \p val
            and returns \p true if it is found, and \p false otherwise.

            Note the hash functor specified for class \p Traits template parameter
            should accept a parameter of type \p Q that may be not the same as \ref value_type.
        */
        template <typename Q>
        bool find( Q const & val )
        {
            return base_class::find( val );
        }

        /// Finds the key \p val using \p pred predicate for searching
        /**
            The function is an analog of \ref cds_nonintrusive_EllenBinTreeSet_find_val "find(Q const&)"
            but \p pred is used for key comparing.
            \p Less functor has the interface like \p std::less.
            \p Less must imply the same element order as the comparator used for building the set.
        */
        template <typename Q, typename Less>
        bool find_with( Q const& val, Less pred )
        {
            return base_class::find_with( val, cds::details::predicate_wrapper< leaf_node, Less, typename maker::value_accessor >());
        }

        /// Finds \p key and returns the item found
        /** @anchor cds_nonintrusive_EllenBinTreeSet_get
            The function searches the item with key equal to \p key and returns the item found in \p result parameter.
            The function returns \p true if \p key is found, \p false otherwise.

            The guarded pointer \p dest prevents deallocation of returned item,
            see cds::gc::guarded_ptr for explanation.
            @note Each \p guarded_ptr object uses the GC's guard that can be limited resource.
        */
        template <typename Q>
        bool get( guarded_ptr& result, Q const& key )
        {
            return base_class::get_( result.guard(), key );
        }

        /// Finds \p key with predicate \p pred and returns the item found
        /**
            The function is an analog of \ref cds_nonintrusive_EllenBinTreeSet_get "get(guarded_ptr&, Q const&)"
            but \p pred is used for key comparing.
            \p Less functor has the interface like \p std::less.
            \p pred must imply the same element order as the comparator used for building the set.
        */
        template <typename Q, typename Less>
        bool get_with( guarded_ptr& result, Q const& key, Less pred )
        {
            return base_class::get_with_( result.guard(), key,
                cds::details::predicate_wrapper< leaf_node, Less, typename maker::value_accessor >() );
        }

        /// Clears the set (non-atomic)
        /**
            The function unlink all items from the tree.
            The function is not atomic, thus, in multi-threaded environment with parallel insertions
            this sequence
            \code
            set.clear();
            assert( set.empty() );
            \endcode
            the assertion could be raised.

            For each leaf the \ref disposer will be called after unlinking.
        */
        void clear()
        {
            base_class::clear();
        }

        /// Checks if the set is empty
        bool empty() const
        {
            return base_class::empty();
        }

        /// Returns item count in the set
        /**
            Only leaf nodes containing user data are counted.

            The value returned depends on item counter type provided by \p Traits template parameter.
            If it is atomicity::empty_item_counter this function always returns 0.
            Therefore, the function is not suitable for checking the tree emptiness, use \ref empty
            member function for this purpose.
        */
        size_t size() const
        {
            return base_class::size();
        }

        /// Returns const reference to internal statistics
        stat const& statistics() const
        {
            return base_class::statistics();
        }

        /// Checks internal consistency (not atomic, not thread-safe)
        /**
            The debugging function to check internal consistency of the tree.
        */
        bool check_consistency() const
        {
            return base_class::check_consistency();
        }
    };

}} // namespace cds::container

#endif // #ifndef __CDS_CONTAINER_IMPL_ELLEN_BINTREE_SET_H
