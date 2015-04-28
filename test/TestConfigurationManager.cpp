#include "TestConfigurationManager.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(TestConfigurationManager);

void TestConfigurationManager::setUp(void)
{
    testConfManager=new ConfigurationManager();
    CPPUNIT_ASSERT(testConfManager->getLogFrequency() == 100);
    CPPUNIT_ASSERT(testConfManager->getExplorationMutationChance() == 0.05);
    CPPUNIT_ASSERT(testConfManager->getRefinementMutationChance() == 0.20);
    CPPUNIT_ASSERT(testConfManager->getCrossoverIterationCount() == 250);
    CPPUNIT_ASSERT(testConfManager->getMinPopulationSize() == 100);
    CPPUNIT_ASSERT(testConfManager->getMaxPopulationSize() == 500);
    CPPUNIT_ASSERT((testConfManager->getMinIterationsCount())==10000);
    CPPUNIT_ASSERT((testConfManager->getMaxIterationsCount())==100000);
    CPPUNIT_ASSERT((testConfManager->getMinFitness())==1.4);
    CPPUNIT_ASSERT((testConfManager->getMaxFitness())==1.7);
    CPPUNIT_ASSERT((testConfManager->getPhaseSwitchFitnessValue())==1.4);
    CPPUNIT_ASSERT((testConfManager->getPhaseSwitchIterationValue())==5000);
    CPPUNIT_ASSERT((testConfManager->getThreadCount())==4);
    CPPUNIT_ASSERT((testConfManager->getUniquePopulationSelection())==true);
    CPPUNIT_ASSERT((testConfManager->getMaxMinDensityClusterProbability())==0.5);
    CPPUNIT_ASSERT((testConfManager->getIterationUntilMissingImprovementCausesInterruption())==1000);
    CPPUNIT_ASSERT((testConfManager->getEnqueueFrequency())==100);
    CPPUNIT_ASSERT((testConfManager->getFitnessFunction())==0);
}

void TestConfigurationManager::tearDown(void)
{
    delete testConfManager;
}

void TestConfigurationManager::testLoadClusteringParams(void)
{
    //write to a file
    std::ofstream file("TestFile1.txt");
    file << "logFrequency = 1000" << endl;
    file << "explorationMutationChance = 0.15" << endl;
    file << "refinementMutationChance = 0.25" << endl;
    file << "crossoverIterationCount = 2500" << endl;
    file << "minPopulationSize" << " = " << "100" << endl;
    file << "maxPopulationSize" << " = " << "500" << endl;
    file << "minIterations"<<" = "<<"1" << endl;
    file << "maxIterations"<<" = "<<"1000" << endl;
    file << "minFitness"<<" = "<<"10.9" << endl;
    file << "maxFitness"<<" = "<<"100.9" << endl;
    file << "phaseSwitchFitnessValue"<<" = "<<"13" << endl;
    file << "phaseSwitchIterationValue"<<" = "<<"16" << endl;
    file << "predictedClusterCount"<<" = "<<"100" << endl;
    file << "threadCount"<<" = "<<"12" << endl;
    file << "uniquePopulationSelection"<<" = "<<"true" << endl;
    file << "maxMinDensityClusterProbability"<<" = "<<"0.11231" << endl;
    file << "enqueueFrequency"<<" = "<<"980089" << endl;
    file << "iterationUntilMissingImprovementCausesInterruption"<<" = "<<"12562" << endl;
    file << "fitnessFunction"<<" = "<<"1" << endl;
    testConfManager->loadClusteringParams("TestFile1.txt");
    //check if the parameters were loaded correctly.
    CPPUNIT_ASSERT(testConfManager->getLogFrequency() == 1000);
    CPPUNIT_ASSERT(testConfManager->getExplorationMutationChance() == 0.15);
    CPPUNIT_ASSERT(testConfManager->getRefinementMutationChance() == 0.25);
    CPPUNIT_ASSERT(testConfManager->getCrossoverIterationCount() == 2500);
    CPPUNIT_ASSERT(testConfManager->getMinPopulationSize() == 100);
    CPPUNIT_ASSERT(testConfManager->getMaxPopulationSize() == 500);
    CPPUNIT_ASSERT((testConfManager->getMinIterationsCount())==1);
    CPPUNIT_ASSERT((testConfManager->getMaxIterationsCount())==1000);
    CPPUNIT_ASSERT((testConfManager->getMinFitness())==10.9);
    CPPUNIT_ASSERT((testConfManager->getMaxFitness())==100.9);
    CPPUNIT_ASSERT((testConfManager->getPhaseSwitchFitnessValue())==13);
    CPPUNIT_ASSERT((testConfManager->getPhaseSwitchIterationValue())==16);
    CPPUNIT_ASSERT((testConfManager->getThreadCount())==12);
    CPPUNIT_ASSERT((testConfManager->getUniquePopulationSelection())==true);
    CPPUNIT_ASSERT((testConfManager->getMaxMinDensityClusterProbability())==0.11231);
    CPPUNIT_ASSERT((testConfManager->getIterationUntilMissingImprovementCausesInterruption())==12562);
    CPPUNIT_ASSERT((testConfManager->getEnqueueFrequency())==980089);
    CPPUNIT_ASSERT((testConfManager->getFitnessFunction())==1);
    file.close();
}

void TestConfigurationManager::testSaveClusteringParams(void)
{
    testConfManager->saveClusteringParams("TestFile2.txt");

    //load parameters from saved file using readConfiguration method
    std::ifstream file("TestFile2.txt");
    ConfigurationReaderWriter configReaderWriter("TestFile2.txt");
    std::unordered_map<std::string, std::string> parameterMap = configReaderWriter.readConfiguration();
    file.close();

    CPPUNIT_ASSERT(parameterMap["logFrequency"] == (to_string(testConfManager->getLogFrequency())));
    CPPUNIT_ASSERT(parameterMap["explorationMutationChance"] == (to_string(testConfManager->getExplorationMutationChance())));
    CPPUNIT_ASSERT(parameterMap["refinementMutationChance"] == (to_string(testConfManager->getRefinementMutationChance())));
    CPPUNIT_ASSERT(parameterMap["crossoverIterationCount"] == (to_string(testConfManager->getCrossoverIterationCount())));
    CPPUNIT_ASSERT(parameterMap["minPopulationSize"] == (to_string(testConfManager->getMinPopulationSize())));
    CPPUNIT_ASSERT(parameterMap["maxPopulationSize"] == (to_string(testConfManager->getMaxPopulationSize())));
    CPPUNIT_ASSERT(parameterMap["maxIterations"]==(to_string(testConfManager->getMaxIterationsCount())));
    CPPUNIT_ASSERT(parameterMap["minIterations"]==(to_string(testConfManager->getMinIterationsCount())));
    CPPUNIT_ASSERT(parameterMap["minFitness"]==(to_string(testConfManager->getMinFitness())));
    CPPUNIT_ASSERT(parameterMap["maxFitness"]==(to_string(testConfManager->getMaxFitness())));
    CPPUNIT_ASSERT(parameterMap["phaseSwitchFitnessValue"]==(to_string(testConfManager->getPhaseSwitchFitnessValue())));
    CPPUNIT_ASSERT(parameterMap["phaseSwitchIterationValue"]==(to_string(testConfManager->getPhaseSwitchIterationValue())));
    CPPUNIT_ASSERT(parameterMap["threadCount"]==(to_string(testConfManager->getThreadCount())));
    CPPUNIT_ASSERT(parameterMap["enqueueFrequency"]==(to_string(testConfManager->getEnqueueFrequency())));
    CPPUNIT_ASSERT(parameterMap["maxMinDensityClusterProbability"]==(to_string(testConfManager->getMaxMinDensityClusterProbability())));
    CPPUNIT_ASSERT(parameterMap["iterationUntilMissingImprovementCausesInterruption"]==(to_string(testConfManager->getIterationUntilMissingImprovementCausesInterruption())));
    std::string testBool;
    if(testConfManager->getUniquePopulationSelection()==true)
    {
	testBool="true";
    } else {
	testBool="false";
    }
    CPPUNIT_ASSERT(parameterMap["uniquePopulationSelection"]=="true");
    CPPUNIT_ASSERT(parameterMap["fitnessFunction"]==(to_string(testConfManager->getFitnessFunction())));
    
}

void TestConfigurationManager::testGetSetMethods(void)
{
    testConfManager->setLogFrequency(100);
    CPPUNIT_ASSERT(100 == (testConfManager->getLogFrequency()));

    testConfManager->setExplorationMutationChance(0.1);
    CPPUNIT_ASSERT(0.1 == (testConfManager->getExplorationMutationChance()));

    testConfManager->setRefinementMutationChance(0.25);
    CPPUNIT_ASSERT(0.25 == (testConfManager->getRefinementMutationChance()));

    testConfManager->setCrossoverIterationCount(250);
    CPPUNIT_ASSERT(250 == (testConfManager->getCrossoverIterationCount()));

    testConfManager->setMinPopulationSize(150);
    CPPUNIT_ASSERT(150 == (testConfManager->getMinPopulationSize()));

    testConfManager->setMaxPopulationSize(160);
    CPPUNIT_ASSERT(160 == (testConfManager->getMaxPopulationSize()));

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

    testConfManager->setThreadCount(20);
    CPPUNIT_ASSERT(20==(testConfManager->getThreadCount()));
    
    testConfManager->setUniquePopulationSelection(true);
    CPPUNIT_ASSERT(true==(testConfManager->getUniquePopulationSelection()));
    
    testConfManager->setMaxMinDensityClusterProbability(1.14);
    CPPUNIT_ASSERT(1.14==(testConfManager->getMaxMinDensityClusterProbability()));
    
    testConfManager->setIterationUntilMissingImprovementCausesInterruption(323121);
    CPPUNIT_ASSERT(323121==(testConfManager->getIterationUntilMissingImprovementCausesInterruption()));
    
    testConfManager->setEnqueueFrequency(108923);
    CPPUNIT_ASSERT(108923==(testConfManager->getEnqueueFrequency()));
    
    testConfManager->setFitnessFunction(2);
    CPPUNIT_ASSERT(2==(testConfManager->getFitnessFunction()));
}
