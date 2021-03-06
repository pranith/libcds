//$$CDS-header$$

// This header should be included AFTER <cds/cxx11_atomic.h> if needed

namespace misc {

    static inline atomics::memory_order convert_to_store_order( atomics::memory_order order )
    {
        switch ( order ) {
            case atomics::memory_order_acquire:
            case atomics::memory_order_consume:
                return atomics::memory_order_relaxed;
            case atomics::memory_order_acq_rel:
                return atomics::memory_order_release;
            default:
                return order;
        }
    }

    static inline atomics::memory_order convert_to_load_order( atomics::memory_order order )
    {
        switch ( order ) {
            case atomics::memory_order_release:
                return atomics::memory_order_relaxed;
            case atomics::memory_order_acq_rel:
                return atomics::memory_order_acquire;
            default:
                return order;
        }
    }

    template <typename T, bool Volatile>
    struct add_volatile;

    template <typename T>
    struct add_volatile<T, false>
    {
        typedef T   type;
    };

    template <typename T>
    struct add_volatile<T, true>
    {
        typedef T volatile   type;
    };

} // namespace misc
