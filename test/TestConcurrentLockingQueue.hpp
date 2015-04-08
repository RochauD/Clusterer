#ifndef TEST_CLUSTERER_COMMON_CONCURRENT_LOCKING_QUEUE_HPP
#define TEST_CLUSTERER_COMMON_CONCURRENT_LOCKING_QUEUE_HPP

// standard headers

// external headers
#include <cppunit/TestCase.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestRunner.h>
#include <cppunit/TestFixture.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/ui/text/TextTestRunner.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
// internal headers
#include "../include/ConcurrentLockingQueue.hpp"

using namespace CppUnit;
using namespace std;
using namespace clc;

class TestConcurrentLockingQueue : public CppUnit::TestFixture
{
        CPPUNIT_TEST_SUITE(TestConcurrentLockingQueue);
        CPPUNIT_TEST(testIsEmptyReturnsTrueOnEmptyQueue);
        CPPUNIT_TEST(testIsEmptyReturnsFalseOnNonEmptyQueue);
        CPPUNIT_TEST(testPopByReturnValueWorks);
        CPPUNIT_TEST(testPopByReturnValueWithMoveOnlyObjectWorks);
        CPPUNIT_TEST(testPopByReferenceWorks);
        CPPUNIT_TEST(testPopByReferenceWithMoveOnlyObjectWorks);
        CPPUNIT_TEST(testPopByPointerWorks);
        CPPUNIT_TEST(testPopByPointerWithMoveOnlyObjectWorks);
        CPPUNIT_TEST(testPopNonWaitingByReferenceWorks);
        CPPUNIT_TEST(testPopNonWaitingByReferenceWithMoveOnlyObjectWorks);
        CPPUNIT_TEST(testPopNonWaitingByReferenceOnEmptyQueueReturnsFalse);
        CPPUNIT_TEST(testPopNonWaitingByPointerWorks);
        CPPUNIT_TEST(testPopNonWaitingByPointerWithMoveOnlyObjectWorks);
        CPPUNIT_TEST(testPopNonWaitingByPointerOnEmptyQueueReturnsFalse);
        CPPUNIT_TEST(testConcurrentLockingQueueExhibitsCorrectBehaviour);
        CPPUNIT_TEST(testConcurrentLockingQueueExhibitsCorrectBehaviourInMultiProducerSetting);
        CPPUNIT_TEST(testConcurrentLockingQueueExhibitsCorrectBehaviourInMultiConsumerSetting);
        CPPUNIT_TEST_SUITE_END();

    public:
        void setUp(void);
        void tearDown(void);

    protected:
        void testIsEmptyReturnsTrueOnEmptyQueue(void);
        void testIsEmptyReturnsFalseOnNonEmptyQueue(void);
        void testPopByReturnValueWorks(void);
        void testPopByReturnValueWithMoveOnlyObjectWorks(void);
        void testPopByReferenceWorks(void);
        void testPopByReferenceWithMoveOnlyObjectWorks(void);
        void testPopByPointerWorks(void);
        void testPopByPointerWithMoveOnlyObjectWorks(void);
        void testPopNonWaitingByReferenceWorks(void);
        void testPopNonWaitingByReferenceWithMoveOnlyObjectWorks(void);
        void testPopNonWaitingByReferenceOnEmptyQueueReturnsFalse(void);
        void testPopNonWaitingByPointerWorks(void);
        void testPopNonWaitingByPointerWithMoveOnlyObjectWorks(void);
        void testPopNonWaitingByPointerOnEmptyQueueReturnsFalse(void);
        void testConcurrentLockingQueueExhibitsCorrectBehaviour(void);
        void testConcurrentLockingQueueExhibitsCorrectBehaviourInMultiProducerSetting(void);
        void testConcurrentLockingQueueExhibitsCorrectBehaviourInMultiConsumerSetting(void);
    private:

};

#endif
