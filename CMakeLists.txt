cmake_minimum_required(VERSION 2.8)

#########################
# Project Specification #
#########################

project(BlueClusterer)

# TODO CHANGE ENGINE TO PROJECT NAME
# Set version
set(ENGINE_VERSION_MAJOR "0")
set(ENGINE_VERSION_MINOR "0")
set(ENGINE_VERSION_PATCH "0")
set(ENGINE_VERSION_EXTRA "")
set(ENGINE_VERSION "${ENGINE_VERSION_MAJOR}.${ENGINE_VERSION_MINOR}")
set(ENGINE_VERSION_FULL "${ENGINE_VERSION}.${ENGINE_VERSION_PATCH}${ENGINE_VERSION_EXTRA}")

#################
# Safety Checks #
#################

# Avoid in-source builds
if (BlueClusterer_SOURCE_DIR STREQUAL BlueClusterer_BINARY_DIR)
    message(FATAL_ERROR "Warning: In-source build! I am not going to let you be stupid!")
endif()

#####################
# Compiler Settings #
#####################

if( WIN32 )
    message("Windows detected.")
else()
    message("Linux detected.")
    # Set C++11
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

    # Enable all warnings
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
    message ("cxx Flags: " ${CMAKE_CXX_FLAGS})
endif()

################
# Dependencies #
################

# Boost
set(Boost_USE_MULTITHREADED ON)
FIND_PACKAGE(Boost)
if(Boost_FOUND)
    include_directories(${INCLUDE_DIRECTORIES} ${Boost_INCLUDE_DIRS})
endif()

# CPP UNIT
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules/")
FIND_PACKAGE(CPPUNIT REQUIRED)

#########################
# Directories #
#########################

set(CLUSTER_SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)
set(CLUSTER_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)

#########
# Files #
#########

set(CLUSTER_SOURCES_CPP 
        ${CLUSTER_SOURCE_DIR}/ConfigurationManager.cpp
        ${CLUSTER_SOURCE_DIR}/ConfigurationReaderWriter.cpp
    )
set(CLUSTER_SOURCES_H 
        ${CLUSTER_INCLUDE_DIR}/ClusteringParams.hpp
        ${CLUSTER_INCLUDE_DIR}/ConfigurationManager.hpp
        ${CLUSTER_INCLUDE_DIR}/ConfigurationReaderWriter.hpp
    )
set(CLUSTER_SOURCES 
        ${CLUSTER_SOURCES_CPP}
        ${CLUSTER_SOURCES_H}   
    )

######################
# Output Directories #
######################

set(COMMON_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/bin")
set(COMMON_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/libs")

#############
# Libraries #
#############

add_library(backend ${CLUSTER_SOURCES})

LINK_DIRECTORIES(${LINK_DIRECTORIES} ${Boost_LIBRARY_DIRS})
 
##############
# Executable #
##############

ADD_EXECUTABLE(BlueClusterer main.cpp)
target_link_libraries(BlueClusterer backend)
