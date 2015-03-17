#include "TestConfigurationReaderWriter.hpp"

void setUp(void){
  cTestObj=new ConfigurationReaderWriter("TestFile.txt",'%'," = ");
  CPPUNIT_ASSERT_EQUAL(cTestObj->fullPathName,"TestFile.txt");
  CPPUNIT_ASSERT_EQUAL(cTestObj->commentCharacter,'%');
  CPPUNIT_ASSERT_EQUAL(cTestObj->seperatorString," = ");
}

void tearDown(void){
  delete cTestObj;
}

void testReadConfiguration(void){
  
  //create a dummy parameter map
  std::unordered_map<std::string, std::string> testParm;
  testParm["minIteration"]="10.00";
  testParm["maxIteration"]="100.00";
  
  //write to a file
  std::ofstream file(cTestObj->fullPathName);
  file<<"minIteration"<<" = "<<"10.00"<<'\n';
  file<<"maxIteration"<<" = "<<"100.00"<<'\n';
  file.close();
  CPPUNIT_ASSERT_EQUAL(testParm,cTestObj->readConfiguration());
  
}

void testWriteConfiguration(void){
  //create dummy parameter map
  unordered_map<string, string> testParm1;
  unordered_map<string, string> testParm2;
  string keyWord;
  string valueWord;
  string seperatorWord;
  
  testParm1["minIteration"]="10.00";
  testParm1["maxIteration"]="100.00";
  
  cTestObj->writeConfiguration(testParm1);
  
  std::ifstream file("TestFile.txt");
  file>>keyWord;
  file>>seperatorWord;
  file>>valueWord;
  testParm2[keyWord]=valueWord;
  file>>keyWord;
  file>>seperatorWord;
  file>>valueWord;
  testParm2[keyWord]=valueWord;
  
  CPPUNIT_ASSERT_EQUAL(testParm1,testParm2);
}