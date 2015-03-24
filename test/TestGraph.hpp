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

#include "../include/Graph.hpp"
//#include "../include/AbstractGraph.hpp"

using namespace CppUnit;
using namespace std;

class TestGraph : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(TestGraph);
    CPPUNIT_TEST(testGetMethods);
    CPPUNIT_TEST(testAddMethods);
    CPPUNIT_TEST_SUITE_END();
    
public:
    void setUp(void);
    void tearDown(void);
  
protected:
    void testGetMethods(void);
    void testAddMethods(void);

private:
	common::types::Graph* testg;
	//static const int NO_V = 50;
};

#endif
