#ifndef TEST_BACKEND_POPULATION_EXPORTER_HPP
#define TEST_BACKEND_POPULATION_EXPORTER_HPP

// standard headers
#include <typeinfo>
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
#include "../include/PopulationExporter.hpp"
#include "../include/IntegerVectorEncoding.hpp"
#include "../include/ClusterEncoding.hpp"

using namespace CppUnit;
using namespace std;
using namespace clb;

class TestPopulationExporter : public CppUnit::TestFixture
{
        CPPUNIT_TEST_SUITE(TestPopulationExporter);
        CPPUNIT_TEST(testWritePopulationToFile);
        CPPUNIT_TEST_SUITE_END();

    public:
        void setUp(void);
        void tearDown(void);

    protected:
        void testWritePopulationToFile(void);
    private:

};

#endif
