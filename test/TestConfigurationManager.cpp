#include "TestConfigurationManager.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION( TestConfigurationManager );

void TestConfigurationManager::setUp(void){
    
    testConfManager=new ConfigurationManager();
    CPPUNIT_ASSERT((testConfManager->GetMinIterationsCount())==10);
    CPPUNIT_ASSERT((testConfManager->GetMaxIterationsCount())==1000);
    CPPUNIT_ASSERT((testConfManager->GetMinFitness())==100.0);
    CPPUNIT_ASSERT((testConfManager->GetMaxFitness())==1000.0);
    CPPUNIT_ASSERT((testConfManager->GetPhaseSwitchFitnessValue())==50.0);
    CPPUNIT_ASSERT((testConfManager->GetPhaseSwitchIterationValue())==700);
    CPPUNIT_ASSERT((testConfManager->GetPredictedClusterCount())==10);
    CPPUNIT_ASSERT((testConfManager->GetThreadCount())==2);
    
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
    
    testConfManager->LoadClusteringParams("TestFile1.txt");
    //check if the parameters were loaded correctly.
    CPPUNIT_ASSERT((testConfManager->GetMinIterationsCount())==1);
    CPPUNIT_ASSERT((testConfManager->GetMaxIterationsCount())==1000);
    CPPUNIT_ASSERT((testConfManager->GetMinFitness())==10.9);
    CPPUNIT_ASSERT((testConfManager->GetMaxFitness())==100.9);
    CPPUNIT_ASSERT((testConfManager->GetPhaseSwitchFitnessValue())==13);
    CPPUNIT_ASSERT((testConfManager->GetPhaseSwitchIterationValue())==16);
    CPPUNIT_ASSERT((testConfManager->GetPredictedClusterCount())==100);
    CPPUNIT_ASSERT((testConfManager->GetThreadCount())==12);;
    file.close();
}

void TestConfigurationManager::testSaveClusteringParams(void){
    
    
    testConfManager->SaveClusteringParams("TestFile2.txt");
    
    //load parameters from saved file using readConfiguration method
    std::ifstream file("TestFile2.txt");
    ConfigurationReaderWriter configReaderWriter("TestFile2.txt");
    std::unordered_map<std::string, std::string> parameterMap = configReaderWriter.readConfiguration();
    file.close();
    
    CPPUNIT_ASSERT(parameterMap["maxIterations"]==(to_string(testConfManager->GetMaxIterationsCount())));
    CPPUNIT_ASSERT(parameterMap["minIterations"]==(to_string(testConfManager->GetMinIterationsCount())));
    CPPUNIT_ASSERT(parameterMap["minFitness"]==(to_string(testConfManager->GetMinFitness())));
    CPPUNIT_ASSERT(parameterMap["maxFitness"]==(to_string(testConfManager->GetMaxFitness())));
    CPPUNIT_ASSERT(parameterMap["phaseSwitchFitnessValue"]==(to_string(testConfManager->GetPhaseSwitchFitnessValue())));
    CPPUNIT_ASSERT(parameterMap["phaseSwitchIterationValue"]==(to_string(testConfManager->GetPhaseSwitchIterationValue())));
    CPPUNIT_ASSERT(parameterMap["predictedClusterCount"]==(to_string(testConfManager->GetPredictedClusterCount())));
    CPPUNIT_ASSERT(parameterMap["threadCount"]==(to_string(testConfManager->GetThreadCount())));
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
    
    testConfManager->SetMinIterationsCount(15);
    CPPUNIT_ASSERT(15==(testConfManager->GetMinIterationsCount()));
    
    testConfManager->SetMaxIterationsCount(16);
    CPPUNIT_ASSERT(16==(testConfManager->GetMaxIterationsCount()));
    
    testConfManager->SetMinFitness(16.5);
    CPPUNIT_ASSERT(16.5==(testConfManager->GetMinFitness()));
    
    testConfManager->SetMaxFitness(15.4);
    CPPUNIT_ASSERT(15.4==(testConfManager->GetMaxFitness()));
    
    testConfManager->SetPhaseSwitchFitnessValue(15.7);
    CPPUNIT_ASSERT(15.7==(testConfManager->GetPhaseSwitchFitnessValue()));
    
    testConfManager->SetPhaseSwitchIterationValue(18);
    CPPUNIT_ASSERT(18==(testConfManager->GetPhaseSwitchIterationValue()));
    
    testConfManager->SetPredictedClusterCount(19);
    CPPUNIT_ASSERT(19==(testConfManager->GetPredictedClusterCount()));
    
    testConfManager->SetThreadCount(20);
    CPPUNIT_ASSERT(20==(testConfManager->GetThreadCount()));
    
}