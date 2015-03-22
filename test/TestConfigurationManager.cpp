#include "TestConfigurationManager.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION( TestConfigurationManager );

void TestConfigurationManager::setUp(void){
    
    testConfManager=new ConfigurationManager();
    CPPUNIT_ASSERT((testConfManager->getMinIterationsCount())==10);
    CPPUNIT_ASSERT((testConfManager->getMaxIterationsCount())==1000);
    CPPUNIT_ASSERT((testConfManager->getMinFitness())==100.0);
    CPPUNIT_ASSERT((testConfManager->getMaxFitness())==1000.0);
    CPPUNIT_ASSERT((testConfManager->getPhaseSwitchFitnessValue())==50.0);
    CPPUNIT_ASSERT((testConfManager->getPhaseSwitchIterationValue())==700);
    CPPUNIT_ASSERT((testConfManager->getPredictedClusterCount())==10);
    CPPUNIT_ASSERT((testConfManager->getThreadCount())==2);
    
}

void TestConfigurationManager::tearDown(void){
    delete testConfManager;
}

void TestConfigurationManager::testLoadClusteringParams(void){
    
    
    //write to a file
    std::ofstream file("TestFile1.txt");
    file<<"minIterations"<<" = "<<"1"<<endl;
    file<<"maxIterations"<<" = "<<"1000"<<endl;
    file<<"minFitness"<<" = "<<"10.9"<<endl;
    file<<"maxFitness"<<" = "<<"100.9"<<endl;
    file<<"phaseSwitchFitnessValue"<<" = "<<"13"<<endl;
    file<<"phaseSwitchIterationValue"<<" = "<<"16"<<endl;
    file<<"predictedClusterCount"<<" = "<<"100"<<endl;
    file<<"threadCount"<<" = "<<"12"<<endl;
    
    testConfManager->loadClusteringParams("TestFile1.txt");
    //check if the parameters were loaded correctly.
    CPPUNIT_ASSERT((testConfManager->getMinIterationsCount())==1);
    CPPUNIT_ASSERT((testConfManager->getMaxIterationsCount())==1000);
    CPPUNIT_ASSERT((testConfManager->getMinFitness())==10.9);
    CPPUNIT_ASSERT((testConfManager->getMaxFitness())==100.9);
    CPPUNIT_ASSERT((testConfManager->getPhaseSwitchFitnessValue())==13);
    CPPUNIT_ASSERT((testConfManager->getPhaseSwitchIterationValue())==16);
    CPPUNIT_ASSERT((testConfManager->getPredictedClusterCount())==100);
    CPPUNIT_ASSERT((testConfManager->getThreadCount())==12);;
    file.close();
}

void TestConfigurationManager::testSaveClusteringParams(void){
    
    
    testConfManager->saveClusteringParams("TestFile2.txt");
    
    //load parameters from saved file using readConfiguration method
    std::ifstream file("TestFile2.txt");
    ConfigurationReaderWriter configReaderWriter("TestFile2.txt");
    std::unordered_map<std::string, std::string> parameterMap = configReaderWriter.readConfiguration();
    file.close();
    
    CPPUNIT_ASSERT(parameterMap["maxIterations"]==(to_string(testConfManager->getMaxIterationsCount())));
    CPPUNIT_ASSERT(parameterMap["minIterations"]==(to_string(testConfManager->getMinIterationsCount())));
    CPPUNIT_ASSERT(parameterMap["minFitness"]==(to_string(testConfManager->getMinFitness())));
    CPPUNIT_ASSERT(parameterMap["maxFitness"]==(to_string(testConfManager->getMaxFitness())));
    CPPUNIT_ASSERT(parameterMap["phaseSwitchFitnessValue"]==(to_string(testConfManager->getPhaseSwitchFitnessValue())));
    CPPUNIT_ASSERT(parameterMap["phaseSwitchIterationValue"]==(to_string(testConfManager->getPhaseSwitchIterationValue())));
    CPPUNIT_ASSERT(parameterMap["predictedClusterCount"]==(to_string(testConfManager->getPredictedClusterCount())));
    CPPUNIT_ASSERT(parameterMap["threadCount"]==(to_string(testConfManager->getThreadCount())));
}

void TestConfigurationManager::testGetSetMethods(void){
    
    //create a dummy ClusteringParams
    /* No standard way to compare structs was found
    ClusteringParams myClusteringParams;
    myClusteringParams.minIterations=11;
    myClusteringParams.maxIterations=12;
    myClusteringParams.minFitness=12.3;
    myClusteringParams.maxFitness=13.1;
    myClusteringParams.phaseSwitchFitnessValue=12.1;
    myClusteringParams.phaseSwitchIterationValue=5;
    myClusteringParams.predictedClusterCount=1;
    myClusteringParams.threadCount=10;
    
    
    testConfManager->SetClusteringParams(myClusteringParams);
    CPPUNIT_ASSERT(myClusteringParams==(testConfManager->GetClusteringParams()));
    */
    
    testConfManager->setMinIterationsCount(15);
    CPPUNIT_ASSERT(15==(testConfManager->getMinIterationsCount()));
    
    testConfManager->setMaxIterationsCount(16);
    CPPUNIT_ASSERT(16==(testConfManager->getMaxIterationsCount()));
    
    testConfManager->setMinFitness(16.5);
    CPPUNIT_ASSERT(16.5==(testConfManager->getMinFitness()));
    
    testConfManager->setMaxFitness(15.4);
    CPPUNIT_ASSERT(15.4==(testConfManager->getMaxFitness()));
    
    testConfManager->setPhaseSwitchFitnessValue(15.7);
    CPPUNIT_ASSERT(15.7==(testConfManager->getPhaseSwitchFitnessValue()));
    
    testConfManager->setPhaseSwitchIterationValue(18);
    CPPUNIT_ASSERT(18==(testConfManager->getPhaseSwitchIterationValue()));
    
    testConfManager->setPredictedClusterCount(19);
    CPPUNIT_ASSERT(19==(testConfManager->getPredictedClusterCount()));
    
    testConfManager->setThreadCount(20);
    CPPUNIT_ASSERT(20==(testConfManager->getThreadCount()));
    
}