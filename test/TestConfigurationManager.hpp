#ifndef TEST_BASIC_CONF_HPP
#define TEST_BASIC_CONF_HPP

#include <iostream>
#include <fstream>
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
///////////////////////////////////////////////////////
#include <typeinfo>

#include "../include/ConfigurationManager.hpp"
#include "../include/ClusteringParams.hpp"


using namespace CppUnit;
using namespace std;

class TestConfigurationManager:public CppUnit::TestFixture{
    CPPUNIT_TEST_SUITE(TestConfigurationManager);
    CPPUNIT_TEST(testGetSetMethods);
    CPPUNIT_TEST(testLoadClusteringParams);
    CPPUNIT_TEST(testSaveClusteringParams);
    CPPUNIT_TEST_SUITE_END();
    
public:
    void setUp(void);
    void tearDown(void);
  
protected:
    void testGetSetMethods(void);
    void testLoadClusteringParams(void);
    void testSaveClusteringParams(void);
  
private:
    ConfigurationManager *testConfManager;
};

#endif