//$$CDS-header$$

#ifndef __CDSUNIT_QUEUE_DEFS_H
#define __CDSUNIT_QUEUE_DEFS_H

// MoirQueue
#define CDSUNIT_DECLARE_MoirQueue( ITEM_TYPE ) \
    TEST_CASE( MoirQueue_HP, ITEM_TYPE ) \
    TEST_CASE( MoirQueue_HP_michaelAlloc, ITEM_TYPE ) \
    TEST_CASE( MoirQueue_HP_seqcst, ITEM_TYPE ) \
    TEST_CASE( MoirQueue_HP_ic, ITEM_TYPE ) \
    TEST_CASE( MoirQueue_HP_stat, ITEM_TYPE ) \
    TEST_CASE( MoirQueue_HRC, ITEM_TYPE ) \
    TEST_CASE( MoirQueue_HRC_michaelAlloc, ITEM_TYPE ) \
    TEST_CASE( MoirQueue_HRC_seqcst, ITEM_TYPE ) \
    TEST_CASE( MoirQueue_HRC_ic, ITEM_TYPE ) \
    TEST_CASE( MoirQueue_HRC_stat, ITEM_TYPE ) \
    TEST_CASE( MoirQueue_PTB, ITEM_TYPE ) \
    TEST_CASE( MoirQueue_PTB_michaelAlloc, ITEM_TYPE ) \
    TEST_CASE( MoirQueue_PTB_seqcst, ITEM_TYPE ) \
    TEST_CASE( MoirQueue_PTB_ic, ITEM_TYPE ) \
    TEST_CASE( MoirQueue_PTB_stat, ITEM_TYPE )

#define CDSUNIT_TEST_MoirQueue \
    CPPUNIT_TEST(MoirQueue_HP) \
    CPPUNIT_TEST(MoirQueue_HP_michaelAlloc) \
    CPPUNIT_TEST(MoirQueue_HP_seqcst) \
    CPPUNIT_TEST(MoirQueue_HP_ic) \
    CPPUNIT_TEST(MoirQueue_HP_stat) \
    CPPUNIT_TEST(MoirQueue_HRC) \
    CPPUNIT_TEST(MoirQueue_HRC_michaelAlloc) \
    CPPUNIT_TEST(MoirQueue_HRC_seqcst) \
    CPPUNIT_TEST(MoirQueue_HRC_ic) \
    CPPUNIT_TEST(MoirQueue_HRC_stat) \
    CPPUNIT_TEST(MoirQueue_PTB) \
    CPPUNIT_TEST(MoirQueue_PTB_michaelAlloc) \
    CPPUNIT_TEST(MoirQueue_PTB_seqcst) \
    CPPUNIT_TEST(MoirQueue_PTB_ic) \
    CPPUNIT_TEST(MoirQueue_PTB_stat)

// MSQueue
#define CDSUNIT_DECLARE_MSQueue( ITEM_TYPE ) \
    TEST_CASE( MSQueue_HP, ITEM_TYPE  ) \
    TEST_CASE( MSQueue_HP_michaelAlloc, ITEM_TYPE  ) \
    TEST_CASE( MSQueue_HP_seqcst, ITEM_TYPE  ) \
    TEST_CASE( MSQueue_HP_ic, ITEM_TYPE  ) \
    TEST_CASE( MSQueue_HP_stat, ITEM_TYPE  ) \
    TEST_CASE( MSQueue_HRC, ITEM_TYPE ) \
    TEST_CASE( MSQueue_HRC_michaelAlloc, ITEM_TYPE ) \
    TEST_CASE( MSQueue_HRC_seqcst, ITEM_TYPE ) \
    TEST_CASE( MSQueue_HRC_ic, ITEM_TYPE ) \
    TEST_CASE( MSQueue_HRC_stat, ITEM_TYPE ) \
    TEST_CASE( MSQueue_PTB, ITEM_TYPE ) \
    TEST_CASE( MSQueue_PTB_michaelAlloc, ITEM_TYPE ) \
    TEST_CASE( MSQueue_PTB_seqcst, ITEM_TYPE ) \
    TEST_CASE( MSQueue_PTB_ic, ITEM_TYPE ) \
    TEST_CASE( MSQueue_PTB_stat, ITEM_TYPE )

#define CDSUNIT_TEST_MSQueue \
    CPPUNIT_TEST(MSQueue_HP) \
    CPPUNIT_TEST(MSQueue_HP_michaelAlloc) \
    CPPUNIT_TEST(MSQueue_HP_seqcst) \
    CPPUNIT_TEST(MSQueue_HP_ic) \
    CPPUNIT_TEST(MSQueue_HP_stat) \
    CPPUNIT_TEST(MSQueue_HRC) \
    CPPUNIT_TEST(MSQueue_HRC_michaelAlloc) \
    CPPUNIT_TEST(MSQueue_HRC_seqcst) \
    CPPUNIT_TEST(MSQueue_HRC_ic) \
    CPPUNIT_TEST(MSQueue_HRC_stat) \
    CPPUNIT_TEST(MSQueue_PTB) \
    CPPUNIT_TEST(MSQueue_PTB_michaelAlloc) \
    CPPUNIT_TEST(MSQueue_PTB_seqcst) \
    CPPUNIT_TEST(MSQueue_PTB_ic) \
    CPPUNIT_TEST(MSQueue_PTB_stat)


// OptimisticQueue
#define CDSUNIT_DECLARE_OptimisticQueue( ITEM_TYPE ) \
    TEST_CASE(OptimisticQueue_HP, ITEM_TYPE ) \
    TEST_CASE(OptimisticQueue_HP_michaelAlloc, ITEM_TYPE ) \
    TEST_CASE(OptimisticQueue_HP_seqcst, ITEM_TYPE ) \
    TEST_CASE(OptimisticQueue_HP_ic, ITEM_TYPE ) \
    TEST_CASE(OptimisticQueue_HP_stat, ITEM_TYPE ) \
    TEST_CASE(OptimisticQueue_PTB, ITEM_TYPE ) \
    TEST_CASE(OptimisticQueue_PTB_michaelAlloc, ITEM_TYPE ) \
    TEST_CASE(OptimisticQueue_PTB_seqcst, ITEM_TYPE ) \
    TEST_CASE(OptimisticQueue_PTB_ic, ITEM_TYPE ) \
    TEST_CASE(OptimisticQueue_PTB_stat, ITEM_TYPE )

#define CDSUNIT_TEST_OptimisticQueue \
    CPPUNIT_TEST(OptimisticQueue_HP) \
    CPPUNIT_TEST(OptimisticQueue_HP_michaelAlloc) \
    CPPUNIT_TEST(OptimisticQueue_HP_seqcst) \
    CPPUNIT_TEST(OptimisticQueue_HP_ic) \
    CPPUNIT_TEST(OptimisticQueue_HP_stat) \
    CPPUNIT_TEST(OptimisticQueue_PTB) \
    CPPUNIT_TEST(OptimisticQueue_PTB_michaelAlloc) \
    CPPUNIT_TEST(OptimisticQueue_PTB_seqcst) \
    CPPUNIT_TEST(OptimisticQueue_PTB_ic) \
    CPPUNIT_TEST(OptimisticQueue_PTB_stat)


// BasketQueue
#define CDSUNIT_DECLARE_BasketQueue( ITEM_TYPE ) \
    TEST_CASE( BasketQueue_HP, ITEM_TYPE  ) \
    TEST_CASE( BasketQueue_HP_michaelAlloc, ITEM_TYPE ) \
    TEST_CASE( BasketQueue_HP_seqcst, ITEM_TYPE  ) \
    TEST_CASE( BasketQueue_HP_ic, ITEM_TYPE  ) \
    TEST_CASE( BasketQueue_HP_stat, ITEM_TYPE  ) \
    TEST_CASE( BasketQueue_HRC, ITEM_TYPE ) \
    TEST_CASE( BasketQueue_HRC_michaelAlloc, ITEM_TYPE ) \
    TEST_CASE( BasketQueue_HRC_seqcst, ITEM_TYPE ) \
    TEST_CASE( BasketQueue_HRC_ic, ITEM_TYPE ) \
    TEST_CASE( BasketQueue_HRC_stat, ITEM_TYPE ) \
    TEST_CASE( BasketQueue_PTB, ITEM_TYPE ) \
    TEST_CASE( BasketQueue_PTB_michaelAlloc, ITEM_TYPE ) \
    TEST_CASE( BasketQueue_PTB_seqcst, ITEM_TYPE ) \
    TEST_CASE( BasketQueue_PTB_ic, ITEM_TYPE ) \
    TEST_CASE( BasketQueue_PTB_stat, ITEM_TYPE )

#define CDSUNIT_TEST_BasketQueue \
    CPPUNIT_TEST(BasketQueue_HP) \
    CPPUNIT_TEST(BasketQueue_HP_michaelAlloc) \
    CPPUNIT_TEST(BasketQueue_HP_seqcst) \
    CPPUNIT_TEST(BasketQueue_HP_ic) \
    CPPUNIT_TEST(BasketQueue_HP_stat) \
    CPPUNIT_TEST(BasketQueue_HRC) \
    CPPUNIT_TEST(BasketQueue_HRC_michaelAlloc) \
    CPPUNIT_TEST(BasketQueue_HRC_seqcst) \
    CPPUNIT_TEST(BasketQueue_HRC_ic) \
    CPPUNIT_TEST(BasketQueue_HRC_stat) \
    CPPUNIT_TEST(BasketQueue_PTB) \
    CPPUNIT_TEST(BasketQueue_PTB_michaelAlloc) \
    CPPUNIT_TEST(BasketQueue_PTB_seqcst) \
    CPPUNIT_TEST(BasketQueue_PTB_ic) \
    CPPUNIT_TEST(BasketQueue_PTB_stat)


// FCQueue
#define CDSUNIT_DECLARE_FCQueue( ITEM_TYPE ) \
    TEST_CASE( FCQueue_deque, ITEM_TYPE ) \
    TEST_CASE( FCQueue_deque_elimination, ITEM_TYPE ) \
    TEST_CASE( FCQueue_deque_elimination_stat, ITEM_TYPE ) \
    TEST_CASE( FCQueue_list, ITEM_TYPE ) \
    TEST_CASE( FCQueue_list_elimination, ITEM_TYPE ) \
    TEST_CASE( FCQueue_list_elimination_stat, ITEM_TYPE )

#define CDSUNIT_TEST_FCQueue \
    CPPUNIT_TEST( FCQueue_deque) \
    CPPUNIT_TEST( FCQueue_deque_elimination) \
    CPPUNIT_TEST( FCQueue_deque_elimination_stat) \
    CPPUNIT_TEST( FCQueue_list) \
    CPPUNIT_TEST( FCQueue_list_elimination) \
    CPPUNIT_TEST( FCQueue_list_elimination_stat)


// FCDeque
#define CDSUNIT_DECLARE_FCDeque( ITEM_TYPE ) \
    TEST_CASE( FCDequeL_default, ITEM_TYPE ) \
    TEST_CASE( FCDequeL_mutex, ITEM_TYPE ) \
    TEST_CASE( FCDequeL_stat, ITEM_TYPE ) \
    TEST_CASE( FCDequeL_elimination, ITEM_TYPE ) \
    TEST_CASE( FCDequeL_elimination_stat, ITEM_TYPE ) \
    TEST_CASE( FCDequeL_boost, ITEM_TYPE ) \
    TEST_CASE( FCDequeL_boost_stat, ITEM_TYPE ) \
    TEST_CASE( FCDequeL_boost_elimination, ITEM_TYPE ) \
    TEST_CASE( FCDequeL_boost_elimination_stat, ITEM_TYPE ) \
    TEST_CASE( FCDequeR_default, ITEM_TYPE ) \
    TEST_CASE( FCDequeR_mutex, ITEM_TYPE ) \
    TEST_CASE( FCDequeR_stat, ITEM_TYPE ) \
    TEST_CASE( FCDequeR_elimination, ITEM_TYPE ) \
    TEST_CASE( FCDequeR_elimination_stat, ITEM_TYPE ) \
    TEST_CASE( FCDequeR_boost, ITEM_TYPE ) \
    TEST_CASE( FCDequeR_boost_stat, ITEM_TYPE ) \
    TEST_CASE( FCDequeR_boost_elimination, ITEM_TYPE ) \
    TEST_CASE( FCDequeR_boost_elimination_stat, ITEM_TYPE )

#define CDSUNIT_TEST_FCDeque \
    CPPUNIT_TEST( FCDequeL_default ) \
    CPPUNIT_TEST( FCDequeL_mutex ) \
    CPPUNIT_TEST( FCDequeL_stat ) \
    CPPUNIT_TEST( FCDequeL_elimination ) \
    CPPUNIT_TEST( FCDequeL_elimination_stat ) \
    CPPUNIT_TEST( FCDequeL_boost ) \
    CPPUNIT_TEST( FCDequeL_boost_stat ) \
    CPPUNIT_TEST( FCDequeL_boost_elimination ) \
    CPPUNIT_TEST( FCDequeL_boost_elimination_stat ) \
    CPPUNIT_TEST( FCDequeR_default ) \
    CPPUNIT_TEST( FCDequeR_mutex ) \
    CPPUNIT_TEST( FCDequeR_stat ) \
    CPPUNIT_TEST( FCDequeR_elimination ) \
    CPPUNIT_TEST( FCDequeR_elimination_stat ) \
    CPPUNIT_TEST( FCDequeR_boost ) \
    CPPUNIT_TEST( FCDequeR_boost_stat ) \
    CPPUNIT_TEST( FCDequeR_boost_elimination ) \
    CPPUNIT_TEST( FCDequeR_boost_elimination_stat )


// RWQueue
#define CDSUNIT_DECLARE_RWQueue( ITEM_TYPE ) \
    TEST_CASE( RWQueue_Spin, ITEM_TYPE ) \
    TEST_CASE( RWQueue_Spin_ic, ITEM_TYPE ) \
    TEST_CASE( RWQueue_Spin_stat, ITEM_TYPE )

#define CDSUNIT_TEST_RWQueue \
    CPPUNIT_TEST(RWQueue_Spin) \
    CPPUNIT_TEST(RWQueue_Spin_ic) \
    CPPUNIT_TEST(RWQueue_Spin_stat)

// TsigasCycleQueue
#define CDSUNIT_DECLARE_TsigasCysleQueue( ITEM_TYPE ) \
    TEST_BOUNDED(TsigasCycleQueue_dyn, ITEM_TYPE) \
    TEST_BOUNDED(TsigasCycleQueue_dyn_michaelAlloc, ITEM_TYPE) \
    TEST_BOUNDED(TsigasCycleQueue_dyn_ic, ITEM_TYPE)

#define CDSUNIT_TEST_TsigasCysleQueue \
    CPPUNIT_TEST(TsigasCycleQueue_dyn) \
    CPPUNIT_TEST(TsigasCycleQueue_dyn_michaelAlloc) \
    CPPUNIT_TEST(TsigasCycleQueue_dyn_ic)


// VyukovMPMCCycleQueue
#define CDSUNIT_DECLARE_VyukovMPMCCycleQueue( ITEM_TYPE ) \
    TEST_BOUNDED(VyukovMPMCCycleQueue_dyn, ITEM_TYPE) \
    TEST_BOUNDED(VyukovMPMCCycleQueue_dyn_michaelAlloc, ITEM_TYPE) \
    TEST_BOUNDED(VyukovMPMCCycleQueue_dyn_ic, ITEM_TYPE)

#define CDSUNIT_TEST_VyukovMPMCCycleQueue \
    CPPUNIT_TEST(VyukovMPMCCycleQueue_dyn) \
    CPPUNIT_TEST(VyukovMPMCCycleQueue_dyn_michaelAlloc) \
    CPPUNIT_TEST(VyukovMPMCCycleQueue_dyn_ic)

// SegmentedQueue
#define CDSUNIT_DECLARE_SegmentedQueue( ITEM_TYPE ) \
    TEST_SEGMENTED( SegmentedQueue_HP_spin, ITEM_TYPE ) \
    TEST_SEGMENTED( SegmentedQueue_HP_spin_stat, ITEM_TYPE ) \
    TEST_SEGMENTED( SegmentedQueue_HP_mutex, ITEM_TYPE ) \
    TEST_SEGMENTED( SegmentedQueue_HP_mutex_stat, ITEM_TYPE ) \
    TEST_SEGMENTED( SegmentedQueue_PTB_spin, ITEM_TYPE ) \
    TEST_SEGMENTED( SegmentedQueue_PTB_spin_stat, ITEM_TYPE ) \
    TEST_SEGMENTED( SegmentedQueue_PTB_mutex, ITEM_TYPE ) \
    TEST_SEGMENTED( SegmentedQueue_PTB_mutex_stat, ITEM_TYPE )

#define CDSUNIT_TEST_SegmentedQueue \
    CPPUNIT_TEST( SegmentedQueue_HP_spin ) \
    CPPUNIT_TEST( SegmentedQueue_HP_spin_stat ) \
    CPPUNIT_TEST( SegmentedQueue_HP_mutex ) \
    CPPUNIT_TEST( SegmentedQueue_HP_mutex_stat ) \
    CPPUNIT_TEST( SegmentedQueue_PTB_spin ) \
    CPPUNIT_TEST( SegmentedQueue_PTB_spin_stat ) \
    CPPUNIT_TEST( SegmentedQueue_PTB_mutex ) \
    CPPUNIT_TEST( SegmentedQueue_PTB_mutex_stat )


// std::queue
#define CDSUNIT_DECLARE_StdQueue( ITEM_TYPE ) \
    TEST_CASE( StdQueue_deque_Spinlock, ITEM_TYPE ) \
    TEST_CASE( StdQueue_list_Spinlock, ITEM_TYPE ) \
    TEST_CASE( StdQueue_deque_BoostMutex, ITEM_TYPE ) \
    TEST_CASE( StdQueue_list_BoostMutex, ITEM_TYPE )

#define CDSUNIT_TEST_StdQueue \
    CPPUNIT_TEST(StdQueue_deque_Spinlock) \
    CPPUNIT_TEST(StdQueue_list_Spinlock) \
    CPPUNIT_TEST(StdQueue_deque_BoostMutex) \
    CPPUNIT_TEST(StdQueue_list_BoostMutex)


#endif // #ifndef __CDSUNIT_QUEUE_DEFS_H
