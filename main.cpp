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
    bool flag = true;
    clc::ConcurrentLockingQueue<std::pair<IntegerVectorEncoding, double>>* queue;
    int option;
    while (running)
    {
        std::cout << "1) Load Configuration from file.\n";
        std::cout << "2) Save Configuration to file.\n";
        std::cout << "3) Load Graph from file.\n";
        std::cout << "4) Load Zachary data set.\n";
        std::cout << "5) Run Algorithm.\n";
        std::cout << "6) Run Algorithm(reset population).\n";
        std::cout << "7) Exit.\n";
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
                        std::cout << "\tLoading configuration parameters failed." << std::endl;
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
                    queue = service.getOutQueue();
                    std::thread t([=]
                    {
                        while (flag)
                        {
                            auto res = queue->pop();
                            std::cout << "Current fitness: " << res.second << std::endl;
                            std::cout << "Encoding: " << std::endl;
                            for (auto& e : res.first.getEncoding())
                            {
                                std::cout << e << " ";
                            }
                            std::cout << std::endl;
                        }
                    });
                    if (service.runAlgorithm(false))
                    {
                        std::cout << "\tAlgorithm run was succesful." << std::endl;
                        flag = false;
                        queue->push(std::make_pair(IntegerVectorEncoding(), 0.0));
                    }
                    else
                    {
                        std::cout << "\tAlgorithm run failed." << std::endl;
                        flag = false;
                        queue->push(std::make_pair(IntegerVectorEncoding(), 0.0));
                    }
                    t.join();
                }
                break;
            case 6:
                {
                    if (service.runAlgorithm(true))
                    {
                        std::cout << "\tAlgorithm run was succesful." << std::endl;
                    }
                    else
                    {
                        std::cout << "\tAlgorithm run failed." << std::endl;
                    }
                }
                break;
            case 7:
                {
                    running = false;
                }
                break;
            default:
                std::cout << "Please use a valid option, between 1 and 7!" << std::endl;
                break;
        }
        std::cout << "\n\n";
    }

    return 0;
}
