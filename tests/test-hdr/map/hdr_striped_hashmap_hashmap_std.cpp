//$$CDS-header$$

#include "map/hdr_striped_map.h"
#include <cds/container/striped_map/std_hash_map.h>
#include <cds/container/striped_map.h>
#include <cds/lock/spinlock.h>

#if !((CDS_COMPILER == CDS_COMPILER_MSVC || (CDS_COMPILER == CDS_COMPILER_INTEL && CDS_OS_INTERFACE == CDS_OSI_WINDOWS)) && _MSC_VER < 1600)

namespace map {

    namespace {
        typedef std::unordered_map< StripedMapHdrTest::key_type, StripedMapHdrTest::value_type > map_t;

        struct my_copy_policy {
            typedef map_t::iterator iterator;

            void operator()( map_t& m, iterator itInsert, iterator itWhat )
            {
                m.insert( std::make_pair(itWhat->first, itWhat->second ) );
            }
        };
    }

    void StripedMapHdrTest::Striped_hashmap()
    {
        CPPUNIT_MESSAGE( "cmp");
        typedef cc::StripedMap< map_t
            , co::hash< hash_int >
            , co::compare< cmp >
            ,co::mutex_policy< cc::striped_set::striping<> >
        >   map_cmp;
        test_striped< map_cmp >();

        CPPUNIT_MESSAGE( "less");
        typedef cc::StripedMap< map_t
            , co::hash< hash_int >
            , co::less< less >
        >   map_less;
        test_striped< map_less >();

        CPPUNIT_MESSAGE( "cmpmix");
        typedef cc::StripedMap< map_t
            , co::hash< hash_int >
            , co::compare< cmp >
            , co::less< less >
        >   map_cmpmix;
        test_striped< map_cmpmix >();

        // Spinlock as lock policy
        CPPUNIT_MESSAGE( "spinlock");
        typedef cc::StripedMap< map_t
            , co::hash< hash_int >
            , co::less< less >
            ,co::mutex_policy< cc::striped_set::striping<cds::lock::Spin> >
        >   map_spin;
        test_striped< map_spin >();

        // Resizing policy
        CPPUNIT_MESSAGE( "load_factor_resizing<0>(1024)");
        {
            typedef cc::StripedMap< map_t
                , co::hash< hash_int >
                , co::less< less >
                , co::resizing_policy< cc::striped_set::load_factor_resizing<0> >
            >   map_less_resizing_lf;
            map_less_resizing_lf m(30, cc::striped_set::load_factor_resizing<0>(1024));
            test_striped_with(m);
        }

        CPPUNIT_MESSAGE( "load_factor_resizing<256>");
        typedef cc::StripedMap< map_t
            , co::hash< hash_int >
            , co::less< less >
            , co::resizing_policy< cc::striped_set::load_factor_resizing<256> >
        >   map_less_resizing_lf16;
        test_striped< map_less_resizing_lf16 >();

        CPPUNIT_MESSAGE( "single_bucket_size_threshold<0>(1024)");
        {
            typedef cc::StripedMap< map_t
                , co::hash< hash_int >
                , co::compare< cmp >
                , co::resizing_policy< cc::striped_set::single_bucket_size_threshold<0> >
            >   map_less_resizing_sbt;
            map_less_resizing_sbt m(30, cc::striped_set::single_bucket_size_threshold<0>(1024));
            test_striped_with(m);
        }

        CPPUNIT_MESSAGE( "single_bucket_size_threshold<256>");
        typedef cc::StripedMap< map_t
            , co::hash< hash_int >
            , co::less< less >
            , co::resizing_policy< cc::striped_set::single_bucket_size_threshold<256> >
        >   map_less_resizing_sbt16;
        test_striped< map_less_resizing_sbt16 >();

        // Copy policy
        CPPUNIT_MESSAGE( "load_factor_resizing<256>, copy_item");
        typedef cc::StripedMap< map_t
            , co::hash< hash_int >
            , co::less< less >
            , co::resizing_policy< cc::striped_set::load_factor_resizing<256> >
            , co::copy_policy< cc::striped_set::copy_item >
        >   set_copy_item;
        test_striped< set_copy_item >();

        CPPUNIT_MESSAGE( "load_factor_resizing<256>, swap_item");
        typedef cc::StripedMap< map_t
            , co::hash< hash_int >
            , co::less< less >
            , co::resizing_policy< cc::striped_set::load_factor_resizing<256> >
            , co::copy_policy< cc::striped_set::swap_item >
        >   set_swap_item;
        test_striped< set_swap_item >();

        CPPUNIT_MESSAGE( "load_factor_resizing<256>, move_item");
        typedef cc::StripedMap< map_t
            , co::hash< hash_int >
            , co::less< less >
            , co::resizing_policy< cc::striped_set::load_factor_resizing<256> >
            , co::copy_policy< cc::striped_set::move_item >
        >   set_move_item;
        test_striped< set_move_item >();

        CPPUNIT_MESSAGE( "load_factor_resizing<256>, special copy_policy");
        typedef cc::StripedMap< map_t
            , co::hash< hash_int >
            , co::less< less >
            , co::resizing_policy< cc::striped_set::load_factor_resizing<256> >
            , co::copy_policy< my_copy_policy >
        >   set_special_copy_item;
        test_striped< set_special_copy_item >();
    }

}   // namespace map

#endif // #if !(CDS_COMPILER == CDS_COMPILER_MSVC && CDS_COMPILER_VERSION < 1600)
