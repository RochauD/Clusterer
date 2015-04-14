#include "TestConfigurationReaderWriter.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(TestConfigurationReaderWriter);

void TestConfigurationReaderWriter::setUp(void)
{
    cTestObj=new ConfigurationReaderWriter("TestFile.txt",'%'," = ");
}

void TestConfigurationReaderWriter::tearDown(void)
{
    delete cTestObj;
}

void TestConfigurationReaderWriter::testReadConfiguration(void)
{
    //create a dummy parameter map
    std::unordered_map<std::string, std::string> testParm;
    testParm["minIteration"]="10";
    testParm["maxIteration"]="100";

    //write to a file
    std::ofstream file("TestFile.txt");
    file<<"minIteration"<<" = "<<"10"<<'\n';
    file<<"maxIteration"<<" = "<<"100"<<'\n';
    file.close();
    CPPUNIT_ASSERT(testParm == cTestObj->readConfiguration());
}

void TestConfigurationReaderWriter::testWriteConfiguration(void)
{
    //create dummy parameter map
    unordered_map<string, string> testParm1;
    unordered_map<string, string> testParm2;
    string keyWord;
    string valueWord;
    string seperatorWord;
    testParm1["minIteration"]="10";
    testParm1["maxIteration"]="100";

    cTestObj->writeConfiguration(testParm1);
    //write dummy parameter to file
    std::ifstream file("TestFile.txt");
    file>>keyWord;
    file>>seperatorWord;
    file>>valueWord;
    testParm2[keyWord]=valueWord;
    file>>keyWord;
    file>>seperatorWord;
    file>>valueWord;
    testParm2[keyWord]=valueWord;
    CPPUNIT_ASSERT(testParm1==testParm2);
}