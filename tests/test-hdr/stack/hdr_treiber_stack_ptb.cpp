//$$CDS-header$$

#include "hdr_treiber_stack.h"
#include <cds/gc/ptb.h>
#include <cds/container/treiber_stack.h>

namespace stack {
#define TEST(X)     void TestStack::X() { test<defs::X>(); }
    namespace cs = cds::container;

    namespace defs { namespace {

        typedef cs::TreiberStack< cds::gc::PTB, int > Treiber_PTB;
        typedef cs::TreiberStack< cds::gc::PTB, int, cds::opt::memory_model<cds::opt::v::relaxed_ordering> > Treiber_PTB_relaxed;

        typedef cs::TreiberStack< cds::gc::PTB, int, cds::opt::back_off< cds::backoff::yield> > Treiber_PTB_yield;
        typedef cs::TreiberStack< cds::gc::PTB, int
            ,cds::opt::back_off< cds::backoff::yield>
            ,cds::opt::memory_model<cds::opt::v::relaxed_ordering>
        > Treiber_PTB_yield_relaxed;

        typedef cs::TreiberStack< cds::gc::PTB, int
            ,cds::opt::back_off< cds::backoff::pause>
            ,cds::opt::allocator< std::allocator< bool * > >
        > Treiber_PTB_pause_alloc;

        typedef cs::TreiberStack< cds::gc::PTB, int
            ,cds::opt::memory_model<cds::opt::v::relaxed_ordering>
            ,cds::opt::back_off< cds::backoff::pause>
            ,cds::opt::allocator< std::allocator< bool * > >
        > Treiber_PTB_pause_alloc_relaxed;
    }}

    TEST(Treiber_PTB)
    TEST(Treiber_PTB_yield)
    TEST(Treiber_PTB_pause_alloc)

    TEST(Treiber_PTB_relaxed)
    TEST(Treiber_PTB_yield_relaxed)
    TEST(Treiber_PTB_pause_alloc_relaxed)

}
