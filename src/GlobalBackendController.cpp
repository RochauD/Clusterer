/**
* @file GlobalBackendController.cpp
*/

#include "../include/GlobalBackendController.hpp"

namespace clusterer
{
namespace backend
{

ClusteringService* GlobalBackendController::instance()
{
    if (backendController.load() == nullptr)
    {
        std::lock_guard<std::mutex> lock(mutex);
        if (backendController.load() == nullptr)
        {
            backendController = new ClusteringService;
        }
    }
    return backendController;
}

std::atomic<ClusteringService*> GlobalBackendController::backendController { nullptr };
std::mutex GlobalBackendController::mutex;

}
}
