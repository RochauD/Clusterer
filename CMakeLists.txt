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

message("Setting compiler settings:")
if( WIN32 )
    message("-- Windows detected")
else()
    message("-- Linux detected")
    # Set C++11
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

    # Enable all warnings
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
    message ("cxx Flags: " ${CMAKE_CXX_FLAGS})
endif()
message("-- Finished setting compiler settings.")
message("\n")

################
# Dependencies #
################

# Boost
set(Boost_USE_MULTITHREADED ON)
FIND_PACKAGE(Boost REQUIRED)
if(Boost_FOUND)
    message("-- Boost include directories added")
    include_directories(${INCLUDE_DIRECTORIES} ${Boost_INCLUDE_DIRS})
endif()

# CPP UNIT
FIND_PACKAGE(CppUnit REQUIRED)
if(CPPUNIT_FOUND)
    message("-- CppUnit include directories added")
    include_directories(${INCLUDE_DIRECTORIES} ${CPPUNIT_INCLUDE_DIR})
endif()
message("\n")

#########################
# Directories #
#########################

set(CLUSTER_SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)
set(CLUSTER_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(CLUSTER_TEST_DIR ${PROJECT_SOURCE_DIR}/test)

#########
# Files #
#########

# source files
set(CLUSTER_SOURCES_CPP 
        ${CLUSTER_SOURCE_DIR}/ConfigurationManager.cpp
        ${CLUSTER_SOURCE_DIR}/ConfigurationReaderWriter.cpp
    )

# header files
set(CLUSTER_SOURCES_H 
        ${CLUSTER_INCLUDE_DIR}/ClusteringParams.hpp
        ${CLUSTER_INCLUDE_DIR}/ConfigurationManager.hpp
        ${CLUSTER_INCLUDE_DIR}/ConfigurationReaderWriter.hpp
    )
# combined
set(CLUSTER_SOURCES 
        ${CLUSTER_SOURCES_CPP}
        ${CLUSTER_SOURCES_H}   
    )

# test files


######################
# Output Directories #
######################

set(COMMON_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/bin")
set(COMMON_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/libs")

#############
# Libraries #
#############

add_library(backend ${CLUSTER_SOURCES})
link_directories(${LINK_DIRECTORIES} ${Boost_LIBRARY_DIRS})
 
##############
# Executable #
##############

add_executable(BlueClusterer main.cpp)
target_link_libraries(BlueClusterer backend)

###########
# Testing #
###########

message("-- Configuring testing")
FILE(GLOB UnitTests_SRCS RELATIVE ${CLUSTER_TEST_DIR} "*Test.cpp" )
ADD_EXECUTABLE(UnitTester ${CLUSTER_TEST_DIR}/TestMain.cpp ${UnitTests_SRCS})

# add library
if(WIN32)
    target_link_libraries(UnitTester debug ${CPPUNIT_DEBUG_LIBRARY})
    target_link_libraries(UnitTester optimized ${CPPUNIT_LIBRARY})
else(WIN32)
    # Link to cpp unit
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lcppunit")
endif(WIN32)

FOREACH(test ${UnitTests_SRCS})
        GET_FILENAME_COMPONENT(TestName ${test} NAME_WE)
        ADD_TEST(${TestName} UnitTester ${TestName})
ENDFOREACH(test)

