//$$CDS-header$$

#include "hdr_treiber_stack.h"
#include <cds/gc/ptb.h>
#include <cds/container/treiber_stack.h>

namespace stack {
#define TEST(X)     void TestStack::X() { test<defs::X>(); }
#define TEST_DYN(X)     void TestStack::X() { test_elimination<defs::X>(); }
    namespace cs = cds::container;

    namespace defs { namespace {

        typedef cs::TreiberStack< cds::gc::PTB, int
            ,cds::opt::enable_elimination<true>
        > Elimination_PTB;

        typedef cs::TreiberStack< cds::gc::PTB, int
            ,cds::opt::enable_elimination<true>
            , cds::opt::buffer< cds::opt::v::dynamic_buffer<void *> >
        > Elimination_PTB_dyn;

        typedef cs::TreiberStack< cds::gc::PTB, int
            , cds::opt::buffer< cds::opt::v::dynamic_buffer<int> >
            , cds::opt::stat< cs::treiber_stack::stat<> >
            ,cds::opt::enable_elimination<true>
        > Elimination_PTB_stat;

        typedef cs::TreiberStack< cds::gc::PTB, int
            , cds::opt::memory_model<cds::opt::v::relaxed_ordering>
            ,cds::opt::enable_elimination<true>
        > Elimination_PTB_relaxed;

        typedef cs::TreiberStack< cds::gc::PTB, int
            , cds::opt::back_off< cds::backoff::yield>
            ,cds::opt::enable_elimination<true>
        > Elimination_PTB_yield;

        typedef cs::TreiberStack< cds::gc::PTB, int
            ,cds::opt::back_off< cds::backoff::yield>
            ,cds::opt::memory_model<cds::opt::v::relaxed_ordering>
            ,cds::opt::enable_elimination<true>
        > Elimination_PTB_yield_relaxed;

        typedef cs::TreiberStack< cds::gc::PTB, int
            ,cds::opt::back_off< cds::backoff::pause>
            ,cds::opt::allocator< std::allocator< bool * > >
            ,cds::opt::enable_elimination<true>
        > Elimination_PTB_pause_alloc;

        typedef cs::TreiberStack< cds::gc::PTB, int
            ,cds::opt::memory_model<cds::opt::v::relaxed_ordering>
            ,cds::opt::back_off< cds::backoff::pause>
            ,cds::opt::allocator< std::allocator< bool * > >
            ,cds::opt::enable_elimination<true>
        > Elimination_PTB_pause_alloc_relaxed;
    }}

    TEST(Elimination_PTB)
    TEST_DYN(Elimination_PTB_dyn)
    TEST_DYN(Elimination_PTB_stat)
    TEST(Elimination_PTB_yield)
    TEST(Elimination_PTB_pause_alloc)

    TEST(Elimination_PTB_relaxed)
    TEST(Elimination_PTB_yield_relaxed)
    TEST(Elimination_PTB_pause_alloc_relaxed)

}
