cmake_minimum_required(VERSION 2.6)
 
Project(BlueClusterer)
 
set(Boost_USE_MULTITHREADED ON)
FIND_PACKAGE(Boost 1.38 COMPONENTS required)

set(srcFolder ${PROJECT_SOURCE_DIR}/src)
add_library(backend ${srcFolder}/AbstractGraph.cpp ${srcFolder}/ClusterEncoder.cpp)


include_directories(${PROJECT_SOURCE_DIR}/include)
INCLUDE_DIRECTORIES(${INCLUDE_DIRECTORIES} ${Boost_INCLUDE_DIRS})
LINK_DIRECTORIES(${LINK_DIRECTORIES} ${Boost_LIBRARY_DIRS})
 
ADD_EXECUTABLE(BlueClusterer main.cpp)
target_link_libraries(BlueClusterer)
