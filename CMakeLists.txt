cmake_minimum_required(VERSION 2.8)

##################
# CMAKE settings #
##################

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

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
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
else()
    message("-- Linux/UNIX detected")
    # Set C++11
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

    # Enable all warnings
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
endif()
message ("-- cxx Flags: " ${CMAKE_CXX_FLAGS})
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
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")
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
        ${CLUSTER_SOURCE_DIR}/AbstractGraph.cpp
        ${CLUSTER_SOURCE_DIR}/ClusterEncoder.cpp
        ${CLUSTER_SOURCE_DIR}/Vertex.cpp
        ${CLUSTER_SOURCE_DIR}/IntegerVectorEncoder.cpp
        ${CLUSTER_SOURCE_DIR}/Parcelable.cpp
        ${CLUSTER_SOURCE_DIR}/Person.cpp
        ${CLUSTER_SOURCE_DIR}/GeneticStrategy.cpp
        ${CLUSTER_SOURCE_DIR}/TwoPhaseStrategy.cpp
        ${CLUSTER_SOURCE_DIR}/JSONGraphReader.cpp
        ${CLUSTER_SOURCE_DIR}/ErrorLogger.cpp
        ${CLUSTER_SOURCE_DIR}/FlagParser.cpp
        ${CLUSTER_SOURCE_DIR}/GeneticGui.cpp
        ${CLUSTER_SOURCE_DIR}/SocialClusteringService.cpp
    )

# header files
set(CLUSTER_SOURCES_H 
        ${CLUSTER_INCLUDE_DIR}/ClusteringParams.hpp
        ${CLUSTER_INCLUDE_DIR}/ConfigurationManager.hpp
        ${CLUSTER_INCLUDE_DIR}/ConfigurationReaderWriter.hpp
        ${CLUSTER_INCLUDE_DIR}/AbstractGraph.hpp
        ${CLUSTER_INCLUDE_DIR}/ClusterEncoder.hpp
        ${CLUSTER_INCLUDE_DIR}/FitnessAnalyzer.hpp
        ${CLUSTER_INCLUDE_DIR}/Vertex.hpp
        ${CLUSTER_INCLUDE_DIR}/IntegerVectorEncoder.hpp
        ${CLUSTER_INCLUDE_DIR}/CrossoverEngine.hpp
        ${CLUSTER_INCLUDE_DIR}/MutationEngine.hpp
        ${CLUSTER_INCLUDE_DIR}/Parcelable.hpp
        ${CLUSTER_INCLUDE_DIR}/Person.hpp
        ${CLUSTER_INCLUDE_DIR}/PersonDb.hpp
        ${CLUSTER_INCLUDE_DIR}/ExplorationMutation.hpp
        ${CLUSTER_INCLUDE_DIR}/ExplorationCrossover.hpp
        ${CLUSTER_INCLUDE_DIR}/RefinementMutationEngine.hpp
        ${CLUSTER_INCLUDE_DIR}/compiler_defs.hpp
        ${CLUSTER_INCLUDE_DIR}/GeneticStrategy.hpp
        ${CLUSTER_INCLUDE_DIR}/TwoPhaseStrategy.hpp
        ${CLUSTER_INCLUDE_DIR}/GraphReader.hpp
        ${CLUSTER_INCLUDE_DIR}/JSONGraphReader.hpp
        ${CLUSTER_INCLUDE_DIR}/ErrorLogger.hpp
        ${CLUSTER_INCLUDE_DIR}/FlagParser.hpp
        ${CLUSTER_INCLUDE_DIR}/MQAnalyzer.hpp
        ${CLUSTER_INCLUDE_DIR}/PerformanceAnalyzer.hpp
        ${CLUSTER_INCLUDE_DIR}/GeneticGui.hpp
        ${CLUSTER_INCLUDE_DIR}/SocialClusteringService.hpp
    )
# combined
set(CLUSTER_SOURCES 
        ${CLUSTER_SOURCES_CPP}
        ${CLUSTER_SOURCES_H}   
    )

# test files
# give the base name of your test class. Assume the base name of your test class is foo.
# Then you need to create the files: Testfoo.cpp Testfoo.hpp TestMainFoo.cpp 
set(CLUSTER_TEST_FILENAMES
        ConfigurationManager
        ConfigurationReaderWriter
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
enable_testing()

FOREACH(test ${CLUSTER_TEST_FILENAMES})
    set(TEST_NAME Test${test})
    set(CLUSTER_TEST_SOURCES
            ${CLUSTER_TEST_DIR}/Test${test}.cpp
            ${CLUSTER_TEST_DIR}/Test${test}.hpp
        )
    set(CLUSTER_TEST_DRIVER
            ${CLUSTER_TEST_DIR}/TestMain${test}.cpp
        )

    # add test executable
    include_directories(${INCLUDE_DIRECTORIES} ${CLUSTER_SOURCES_H})
    add_executable(${TEST_NAME} ${CLUSTER_TEST_DRIVER} ${CLUSTER_TEST_SOURCES})
    target_link_libraries(${TEST_NAME} backend)
    # add library
    target_link_libraries(${TEST_NAME} debug ${CPPUNIT_DEBUG_LIBRARY})
    target_link_libraries(${TEST_NAME} optimized ${CPPUNIT_LIBRARY})

    # add tests to test solution folder for IDEs
    set_target_properties(${TEST_NAME} PROPERTIES FOLDER testing)

    ADD_TEST(${TEST_NAME} ${TEST_NAME} ${TEST_NAME})
ENDFOREACH(test)

