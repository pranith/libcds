//$$CDS-header$$

#include "hdr_intrusive_treiber_stack.h"
#include <cds/gc/ptb.h>
#include <cds/intrusive/treiber_stack.h>

namespace stack {

#define TEST(X)     void TestIntrusiveStack::X() { test<defs::X>(); }

    namespace defs {
        // PTB GC + base hook
        typedef cds::intrusive::TreiberStack< cds::gc::PTB,
            TestIntrusiveStack::base_hook_item<cds::gc::PTB>
            ,ci::opt::hook<
                ci::single_link::base_hook< ci::opt::gc<cds::gc::PTB> >
            >
        > Treiber_PTB_base;

        typedef cds::intrusive::TreiberStack< cds::gc::PTB,
            TestIntrusiveStack::base_hook_item<cds::gc::PTB>
            ,ci::opt::hook<
                ci::single_link::base_hook< ci::opt::gc<cds::gc::PTB> >
            >
            ,ci::opt::memory_model< ci::opt::v::relaxed_ordering >
        > Treiber_PTB_base_relaxed;

        // PTB GC + base hook + disposer
        typedef cds::intrusive::TreiberStack< cds::gc::PTB,
            TestIntrusiveStack::base_hook_item<cds::gc::PTB>
            ,ci::opt::hook<
                ci::single_link::base_hook< ci::opt::gc<cds::gc::PTB> >
            >
            ,ci::opt::disposer< TestIntrusiveStack::faked_disposer >
        > Treiber_PTB_base_disposer;

        typedef cds::intrusive::TreiberStack< cds::gc::PTB,
            TestIntrusiveStack::base_hook_item<cds::gc::PTB>
            ,ci::opt::hook<
                ci::single_link::base_hook< ci::opt::gc<cds::gc::PTB> >
            >
            ,ci::opt::disposer< TestIntrusiveStack::faked_disposer >
            ,ci::opt::memory_model< ci::opt::v::relaxed_ordering >
        > Treiber_PTB_base_disposer_relaxed;

        // PTB GC + member hook
        typedef cds::intrusive::TreiberStack< cds::gc::PTB,
            TestIntrusiveStack::member_hook_item<cds::gc::PTB>
            ,ci::opt::hook<
                ci::single_link::member_hook<
                    offsetof(TestIntrusiveStack::member_hook_item<cds::gc::PTB>, hMember),
                    ci::opt::gc<cds::gc::PTB>
                >
            >
        > Treiber_PTB_member;

        typedef cds::intrusive::TreiberStack< cds::gc::PTB,
            TestIntrusiveStack::member_hook_item<cds::gc::PTB>
            ,ci::opt::hook<
                ci::single_link::member_hook<
                    offsetof(TestIntrusiveStack::member_hook_item<cds::gc::PTB>, hMember),
                    ci::opt::gc<cds::gc::PTB>
                >
            >
            ,ci::opt::memory_model< ci::opt::v::relaxed_ordering >
        > Treiber_PTB_member_relaxed;

        // PTB GC + member hook + disposer
        typedef cds::intrusive::TreiberStack< cds::gc::PTB,
            TestIntrusiveStack::member_hook_item<cds::gc::PTB>
            ,ci::opt::hook<
                ci::single_link::member_hook<
                    offsetof(TestIntrusiveStack::member_hook_item<cds::gc::PTB>, hMember),
                    ci::opt::gc<cds::gc::PTB>
                >
            >
            ,ci::opt::disposer< TestIntrusiveStack::faked_disposer >
        > Treiber_PTB_member_disposer;

        typedef cds::intrusive::TreiberStack< cds::gc::PTB,
            TestIntrusiveStack::member_hook_item<cds::gc::PTB>
            ,ci::opt::hook<
                ci::single_link::member_hook<
                    offsetof(TestIntrusiveStack::member_hook_item<cds::gc::PTB>, hMember),
                    ci::opt::gc<cds::gc::PTB>
                >
            >
            ,ci::opt::disposer< TestIntrusiveStack::faked_disposer >
            ,ci::opt::memory_model< ci::opt::v::relaxed_ordering >
        > Treiber_PTB_member_disposer_relaxed;
    }

    TEST(Treiber_PTB_base)
    TEST(Treiber_PTB_base_disposer)
    TEST(Treiber_PTB_member)
    TEST(Treiber_PTB_member_disposer)

    TEST(Treiber_PTB_base_relaxed)
    TEST(Treiber_PTB_base_disposer_relaxed)
    TEST(Treiber_PTB_member_relaxed)
    TEST(Treiber_PTB_member_disposer_relaxed)

} // namespace stack

