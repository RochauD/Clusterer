#include <iostream>
#include "include/ClusteringService.hpp"
#include "include/GlobalFileLogger.hpp"
#include "include/ConcurrentLockingQueue.hpp"


using namespace clc;
using namespace clb;


int main()
{
    GlobalFileLogger::init();
    GlobalFileLogger::instance()->log(SeverityType::INFO, "Definition Exe Version: ", CLUSTERER_VERSION);
    GlobalFileLogger::instance()->log(SeverityType::INFO, "Definition Exe Version FUll: ", CLUSTERER_VERSION_FULL);
    GlobalFileLogger::instance()->log(SeverityType::INFO, "Definition Lib Version: ", CLUSTERER_LIB_VERSION);
    GlobalFileLogger::instance()->log(SeverityType::INFO, "Definition Lib Version FUll: ", CLUSTERER_LIB_VERSION_FULL);


    ClusteringService service;
    bool running = true;
    int option;
    while (running)
    {
        std::cout << "1) Load Configuration from file.\n";
        std::cout << "2) Save Configuration to file.\n";
        std::cout << "3) Load Graph from file.\n";
        std::cout << "4) Load Zachary data set.\n";
        std::cout << "5) Run Algorithm.\n";
        std::cout << "6) Run Algorithm(reset population).\n";
        std::cout << "7) Stop Algorithm.\n";
        std::cout << "8) Resume Algorithm.\n";
        std::cout << "9) Exit.\n";
        std::cout << std::flush;
        std::cin >> option;
        std::cin.get();
        switch (option)
        {
            case 1:
                {
                    std::string filename;
                    std::cout << "Provide a a filename: ";
                    std::getline(std::cin, filename);
                    if (service.loadConfiguration(filename))
                    {
                        std::cout << "\tLoaded configuration parameters succesfully." << std::endl;
                    }
                    else
                    {
                        std::cout << "\Loading configuration parameters failed." << std::endl;
                    }
                }
                break;
            case 2:
                {
                    std::string filename;
                    std::cout << "Provide a a filename: ";
                    std::getline(std::cin, filename);
                    if (service.saveConfiguration(filename))
                    {
                        std::cout << "\tSaved configuration parameters succesfully." << std::endl;
                    }
                    else
                    {
                        std::cout << "\tSaving configuration parameters failed." << std::endl;
                    }
                }
                break;
            case 3:
                {
                    std::string filename;
                    std::cout << "Provide a a filename: ";
                    std::getline(std::cin, filename);
                    if (service.loadGraphTypeVertexPairWeight(filename))
                    {
                        std::cout << "\tLoaded graph succesfully." << std::endl;
                    }
                    else
                    {
                        std::cout << "\tLoading graph failed." << std::endl;
                    }
                }
                break;
            case 4:
                {
                    std::string filename = "../test_files/out.ucidata-zachary";
                    if (service.loadGraphTypeVertexPairWeight(filename))
                    {
                        std::cout << "\tLoaded zachary graph succesfully." << std::endl;
                    }
                    else
                    {
                        std::cout << "\tLoading zachary graph failed." << std::endl;
                    }
                }
                break;
            case 5:
                {
                    if (service.runAlgorithm(false))
                    {
                        std::cout << "\Algorithm run was succesful." << std::endl;
                    }
                    else
                    {
                        std::cout << "\Algorithm run failed." << std::endl;
                    }
                }
                break;
            case 6:
                {
                    if (service.runAlgorithm(true))
                    {
                        std::cout << "\Algorithm run was succesful." << std::endl;
                    }
                    else
                    {
                        std::cout << "\Algorithm run failed." << std::endl;
                    }
                }
                break;
            case 7:
                {
                    service.stopAlgorithm();
                }
                break;
            case 8:
                {
                    service.resumeAlgorithm();
                }
                break;
            case 9:
                {
                    running = false;
                }
                break;
            default:
                break;
        }
        std::cout << "\n\n";
    }

    return 0;
}
