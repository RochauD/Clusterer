cmake_minimum_required(VERSION 2.8)

##################
# CMAKE settings #
##################

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

#########################
# Project Specification #
#########################

project(Clusterer)

# set library version
set(CLUSTERER_LIB_VERSION_MAJOR "1")
set(CLUSTERER_LIB_VERSION_MINOR "0")
set(CLUSTERER_LIB_VERSION_PATCH "0")
set(CLUSTERER_LIB_VERSION_EXTRA "0")
set(CLUSTERER_LIB_VERSION "${CLUSTERER_LIB_VERSION_MAJOR}.${CLUSTERER_LIB_VERSION_MINOR}")
set(CLUSTERER_LIB_VERSION_FULL "${CLUSTERER_LIB_VERSION}.${CLUSTERER_LIB_VERSION_PATCH}.${CLUSTERER_LIB_VERSION_EXTRA}")
# add library version macro definitions
add_definitions(/DCLUSTERER_LIB_VERSION="${CLUSTERER_LIB_VERSION}")
add_definitions(/DCLUSTERER_LIB_VERSION_FULL="${CLUSTERER_LIB_VERSION_FULL}")

# set executable version
set(CLUSTERER_VERSION_MAJOR "1")
set(CLUSTERER_VERSION_MINOR "0")
set(CLUSTERER_VERSION_PATCH "0")
set(CLUSTERER_VERSION_EXTRA "0")
set(CLUSTERER_VERSION "${CLUSTERER_VERSION_MAJOR}.${CLUSTERER_VERSION_MINOR}")
set(CLUSTERER_VERSION_FULL "${CLUSTERER_VERSION}.${CLUSTERER_VERSION_PATCH}.${CLUSTERER_VERSION_EXTRA}")
# add executable version macro definitions
add_definitions(/DCLUSTERER_VERSION="${CLUSTERER_VERSION}")
add_definitions(/DCLUSTERER_VERSION_FULL="${CLUSTERER_VERSION_FULL}")

#################
# Safety Checks #
#################

# Avoid in-source builds
if ("${PROJECT_SOURCE_DIR}" STREQUAL "${PROJECT_BINARY_DIR}")
    message(FATAL_ERROR "Warning: In-source build! Aborting. Call cmake .. from a build folder.")
endif()

message(${CMAKE_CURRENT_BINARY_DIR})

#####################
# Compiler Settings #
#####################

message("Setting compiler settings:")
if( WIN32 )
    message("-- Windows detected")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")

    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /O2")
elseif( APPLE )
    message("-- OSX detected")
    # Set C++11
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -larmadillo")

    # Enable all warnings
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")
else()
    message("-- Linux detected")
    # Set C++11
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

    # Enable all warnings
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")

endif()
message("-- cxx Flags: " ${CMAKE_CXX_FLAGS})
message("-- Finished setting compiler settings.")
message("\n")

###################
# Linker settings #
###################

message("Setting linker settings:")
if( WIN32 )
    message("-- Windows detected -- setting corresponding linker settings")
elseif( APPLE )
    message("-- OSX detected -- setting corresponding linker settings")
else()
    message("-- Linux detected -- setting corresponding linker settings")
endif()
message("-- Finished setting linker settings.")
message("\n")

################
# Dependencies #
################

# CPP UNIT
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")
FIND_PACKAGE(CppUnit REQUIRED)
if(CPPUNIT_FOUND)
    message("-- CppUnit include directories added")
    include_directories(${INCLUDE_DIRECTORIES} ${CPPUNIT_INCLUDE_DIR})
endif()
message("\n")

# Eigen
if(WIN32)
    include_directories($ENV{EIGEN_ROOT})
    message("-- Added Eigen to include directories.")
    message($ENV{EIGEN_ROOT})
else()
    set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")
    FIND_PACKAGE(Eigen3 REQUIRED)
    if(EIGEN3_FOUND)
        message("-- Eigen found and include directories added")
        include_directories(${EIGEN3_INCLUDE_DIRS})
    else()
        message(FATAL_ERROR "Could not find Eigen")
    endif()
endif()

# Armadillo
if(UNIX)
    FIND_PACKAGE(Armadillo REQUIRED)
    if(ARMADILLO_FOUND)
       message("-- Armadillo found and include directories added")
    else()
       message(FATAL_ERROR "Could not find Armadillo")
    endif()
       include_directories(${ARMADILLO_INCLUDE_DIRS})

    set(ARMADILLO_LIBS ${ARMADILLO_LIBRARIES})
    if(NOT ARMADILLO_LIBS)
       message(FATAL_ERROR "-- Could not find Armadillo libraries")
    else()
       message(STATUS "Armadillo lib: " ${ARMADILLO_LIBS})
    endif()
endif()

# Qt
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC OFF)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
FIND_PACKAGE(Qt4 REQUIRED)
if (Qt4_FOUND)
    message("-- Qt found and include directories added")
    include_directories(${INCLUDE_DIRECTORIES} ${QT_INCLUDE_DIR})
    INCLUDE(${QT_USE_FILE})
else()
    message(FATAL_ERROR "Could not find Qt4")
endif()


# Qwt
FIND_PATH(QWT_INCLUDE_DIR NAMES qwt.h PATHS
  /usr/include
  /usr/local/include
  /usr/local/lib/qwt.framework/Versions/Current
  "$ENV{LIB_DIR}/include" 
  "$ENV{INCLUDE}" 
  "$ENV{QWT_ROOT}/src" 
  "$ENV{QWT_ROOT}" 
  PATH_SUFFIXES qwt-qt4 qwt
  )

FIND_LIBRARY(QWT_LIBRARY NAMES qwt qwtd qwt5 qwt-qt4 qwt5-qt4 PATHS 
  /usr/lib
  /usr/local/lib
  /usr/local/lib/qwt.framework/Versions/Current
  "$ENV{LIB_DIR}/lib" 
  "$ENV{LIB}/lib" 
  "$ENV{QWT_ROOT}/lib" 
  "$ENV{QWT_ROOT}" 
  )

IF (QWT_INCLUDE_DIR AND QWT_LIBRARY)
  SET(QWT_FOUND TRUE)
ENDIF (QWT_INCLUDE_DIR AND QWT_LIBRARY)

IF (QWT_FOUND)
  IF (NOT QWT_FIND_QUIETLY)
    MESSAGE(STATUS "Found QWT: ${QWT_LIBRARY}")
  ENDIF (NOT QWT_FIND_QUIETLY)
ELSE (QWT_FOUND)
  IF (QWT_FIND_REQUIRED)
    MESSAGE(FATAL_ERROR "Could not find QWT")
  ENDIF (QWT_FIND_REQUIRED)
ENDIF (QWT_FOUND)

set ( QWT_INCLUDE_DIRS ${QWT_INCLUDE_DIR} )
include_directories(${QWT_INCLUDE_DIRS})
set ( QWT_LIBRARIES ${QWT_LIBRARY} )

###############
# Directories #
###############

set(CLUSTER_SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)
set(CLUSTER_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(CLUSTER_TEST_DIR ${PROJECT_SOURCE_DIR}/test)

#########
# Files #
#########

# common files
# common source files
set(CLUSTER_SOURCES_COMMON_CPP 
        ${CLUSTER_SOURCE_DIR}/LoggerSeverityLevel.cpp
        ${CLUSTER_SOURCE_DIR}/LoggerSeverityType.cpp
        ${CLUSTER_SOURCE_DIR}/LoggingPolicy.cpp
        ${CLUSTER_SOURCE_DIR}/LoggingPolicyFile.cpp
        ${CLUSTER_SOURCE_DIR}/GlobalFileLogger.cpp
    )
# common header files
set(CLUSTER_SOURCES_COMMON_H 
        ${CLUSTER_INCLUDE_DIR}/ConcurrentLockingQueue.hpp
        ${CLUSTER_INCLUDE_DIR}/Logger.hpp
        ${CLUSTER_INCLUDE_DIR}/LoggerSeverityLevel.hpp
        ${CLUSTER_INCLUDE_DIR}/LoggerSeverityType.hpp
        ${CLUSTER_INCLUDE_DIR}/LoggerException.hpp
        ${CLUSTER_INCLUDE_DIR}/LoggerBufferEntry.hpp
        ${CLUSTER_INCLUDE_DIR}/LoggingPolicy.hpp
        ${CLUSTER_INCLUDE_DIR}/LoggingPolicyFile.hpp
        ${CLUSTER_INCLUDE_DIR}/GlobalFileLogger.hpp
    )
# common combined
set(CLUSTER_SOURCES_COMMON
        ${CLUSTER_SOURCES_COMMON_CPP}
        ${CLUSTER_SOURCES_COMMON_H}
    )
# common filters
source_group("Common\\Header Files" FILES ${CLUSTER_SOURCES_COMMON_H})
source_group("Common\\Source Files" FILES ${CLUSTER_SOURCES_COMMON_CPP})


# backend files
# backend source files
set(CLUSTER_SOURCES_BACKEND_CPP 
        ${CLUSTER_SOURCE_DIR}/ConfigurationManager.cpp
        ${CLUSTER_SOURCE_DIR}/ConfigurationReaderWriter.cpp
        ${CLUSTER_SOURCE_DIR}/AbstractGraph.cpp
        ${CLUSTER_SOURCE_DIR}/AbstractGraphReader.cpp
        ${CLUSTER_SOURCE_DIR}/ClusteringSolutionAnalyzer.cpp
        ${CLUSTER_SOURCE_DIR}/FitnessAnalyzer.cpp
        ${CLUSTER_SOURCE_DIR}/MQAnalyzer.cpp
        ${CLUSTER_SOURCE_DIR}/PerformanceAnalyzer.cpp   
        ${CLUSTER_SOURCE_DIR}/CoverageAnalyzer.cpp   
        ${CLUSTER_SOURCE_DIR}/ClusterEncoding.cpp
        ${CLUSTER_SOURCE_DIR}/Vertex.cpp
        ${CLUSTER_SOURCE_DIR}/IntegerVectorEncoding.cpp
        ${CLUSTER_SOURCE_DIR}/ClusteringService.cpp
        ${CLUSTER_SOURCE_DIR}/Graph.cpp
        ${CLUSTER_SOURCE_DIR}/GraphReader.cpp
        ${CLUSTER_SOURCE_DIR}/IntegerEncodingInitializer.cpp
        ${CLUSTER_SOURCE_DIR}/ExplorationMutation.cpp
        ${CLUSTER_SOURCE_DIR}/MutationEngine.cpp
        ${CLUSTER_SOURCE_DIR}/CrossoverEngine.cpp
        ${CLUSTER_SOURCE_DIR}/UniformCrossoverEngine.cpp
        ${CLUSTER_SOURCE_DIR}/MovieLensGraphReader.cpp
        ${CLUSTER_SOURCE_DIR}/ClusterwiseCrossoverEngine.cpp
        ${CLUSTER_SOURCE_DIR}/CombinedCrossoverEngine.cpp
        ${CLUSTER_SOURCE_DIR}/ExplorationJoin.cpp
        ${CLUSTER_SOURCE_DIR}/ExplorationSplit.cpp
        ${CLUSTER_SOURCE_DIR}/CombinedMutation.cpp
        ${CLUSTER_SOURCE_DIR}/GraphCoordinateTransformer.cpp      
        ${CLUSTER_SOURCE_DIR}/ClusterRefiner.cpp
        ${CLUSTER_SOURCE_DIR}/PopulationExporter.cpp
        ${CLUSTER_SOURCE_DIR}/GraphExporter.cpp
        ${CLUSTER_SOURCE_DIR}/PopulationImporter.cpp
        ${CLUSTER_SOURCE_DIR}/GlobalBackendController.cpp
        ${CLUSTER_SOURCE_DIR}/CombinedCrossoverEngine.cpp
    )
# backend header files
set(CLUSTER_SOURCES_BACKEND_H 
        ${CLUSTER_INCLUDE_DIR}/ClusteringParams.hpp
        ${CLUSTER_INCLUDE_DIR}/ConfigurationManager.hpp
        ${CLUSTER_INCLUDE_DIR}/ConfigurationReaderWriter.hpp
        ${CLUSTER_INCLUDE_DIR}/AbstractGraph.hpp
        ${CLUSTER_INCLUDE_DIR}/AbstractGraphReader.hpp
        ${CLUSTER_INCLUDE_DIR}/ClusterEncoding.hpp
        ${CLUSTER_INCLUDE_DIR}/ClusteringSolutionAnalyzer.hpp
        ${CLUSTER_INCLUDE_DIR}/FitnessAnalyzer.hpp
        ${CLUSTER_INCLUDE_DIR}/MQAnalyzer.hpp
        ${CLUSTER_INCLUDE_DIR}/PerformanceAnalyzer.hpp
        ${CLUSTER_INCLUDE_DIR}/CoverageAnalyzer.hpp        
        ${CLUSTER_INCLUDE_DIR}/Vertex.hpp
        ${CLUSTER_INCLUDE_DIR}/IntegerVectorEncoding.hpp
        ${CLUSTER_INCLUDE_DIR}/CrossoverEngine.hpp
        ${CLUSTER_INCLUDE_DIR}/MutationEngine.hpp
        ${CLUSTER_INCLUDE_DIR}/ExplorationMutation.hpp
        ${CLUSTER_INCLUDE_DIR}/RefinementMutationEngine.hpp
        ${CLUSTER_INCLUDE_DIR}/TwoPhaseStrategy.hpp
        ${CLUSTER_INCLUDE_DIR}/GraphReader.hpp
        ${CLUSTER_INCLUDE_DIR}/ClusteringService.hpp
        ${CLUSTER_INCLUDE_DIR}/Graph.hpp
        ${CLUSTER_INCLUDE_DIR}/GraphReader.hpp
        ${CLUSTER_INCLUDE_DIR}/IntegerEncodingInitializer.hpp
        ${CLUSTER_INCLUDE_DIR}/UniformCrossoverEngine.hpp
        ${CLUSTER_INCLUDE_DIR}/ClusterwiseCrossoverEngine.hpp
        ${CLUSTER_INCLUDE_DIR}/CombinedCrossoverEngine.hpp
        ${CLUSTER_INCLUDE_DIR}/ClusteringPopulationAnalyzer.hpp
        ${CLUSTER_INCLUDE_DIR}/MovieLensGraphReader.hpp
        ${CLUSTER_INCLUDE_DIR}/PopulationMutatorEngine.hpp
        ${CLUSTER_INCLUDE_DIR}/PopulationCrossoverEngine.hpp
        ${CLUSTER_INCLUDE_DIR}/Selector.hpp
        ${CLUSTER_INCLUDE_DIR}/ExplorationJoin.hpp
        ${CLUSTER_INCLUDE_DIR}/ExplorationSplit.hpp
        ${CLUSTER_INCLUDE_DIR}/CombinedMutation.hpp
        ${CLUSTER_INCLUDE_DIR}/ClusterRefiner.hpp
        ${CLUSTER_INCLUDE_DIR}/ClusteringPopulationRefiner.hpp
        ${CLUSTER_INCLUDE_DIR}/GraphCoordinateTransformer.hpp
        ${CLUSTER_INCLUDE_DIR}/ClusteringPopulationSelector.hpp
        ${CLUSTER_INCLUDE_DIR}/PopulationExporter.hpp
        ${CLUSTER_INCLUDE_DIR}/GraphExporter.hpp
        ${CLUSTER_INCLUDE_DIR}/PopulationImporter.hpp
        ${CLUSTER_INCLUDE_DIR}/GlobalBackendController.hpp
        ${CLUSTER_INCLUDE_DIR}/PopulationMember.hpp
        ${CLUSTER_INCLUDE_DIR}/CombinedCrossoverEngine.hpp
    )
# backend combined
set(CLUSTER_SOURCES_BACKEND
        ${CLUSTER_SOURCES_BACKEND_CPP}
        ${CLUSTER_SOURCES_BACKEND_H}
    )
# backend filters
source_group("Backend\\Header Files" FILES ${CLUSTER_SOURCES_BACKEND_H})
source_group("Backend\\Source Files" FILES ${CLUSTER_SOURCES_BACKEND_CPP})


# frontend files
# frontend source files
set(CLUSTER_SOURCES_FRONTEND_CPP
        ${CLUSTER_SOURCE_DIR}/MainWindow.cpp
        ${CLUSTER_SOURCE_DIR}/main.cpp
        ${CLUSTER_SOURCE_DIR}/SettingsDialog.cpp
        ${CLUSTER_SOURCE_DIR}/FrontendConfig.cpp
        ${CLUSTER_SOURCE_DIR}/GUINodePlotter.cpp
        ${CLUSTER_SOURCE_DIR}/GUIFitnessPlot.cpp
    )
# frontend header files
set(CLUSTER_SOURCES_FRONTEND_H 
        ${CLUSTER_INCLUDE_DIR}/GUINodePlotter.hpp
        ${CLUSTER_INCLUDE_DIR}/GUIFitnessPlot.hpp
        ${CLUSTER_INCLUDE_DIR}/MainWindow.h
        ${CLUSTER_INCLUDE_DIR}/SettingsDialog.h
        ${CLUSTER_INCLUDE_DIR}/FrontendConfig.h
    )
# moc header files
set(CLUSTER_SOURCES_MOC_H
        ${CLUSTER_SOURCES_FRONTEND_H}
)
# ui header files
qt4_wrap_ui(CLUSTER_SOURCES_UI_H
    ${CLUSTER_SOURCE_DIR}/SettingsDialog.ui
    ${CLUSTER_SOURCE_DIR}/MainWindow.ui
)

# frontend combined
set(CLUSTER_SOURCES_FRONTEND
        ${CLUSTER_SOURCES_FRONTEND_CPP}
        ${CLUSTER_SOURCES_FRONTEND_H}
        ${CLUSTER_SOURCES_UI_H}
    )



# frontend filters
source_group("Frontend\\Header Files" FILES ${CLUSTER_SOURCES_FRONTEND_H})
source_group("Frontend\\Source Files" FILES ${CLUSTER_SOURCES_FRONTEND_CPP})


# all files
# source files
set(CLUSTER_SOURCES_CPP 
        ${CLUSTER_SOURCES_COMMON_CPP}
        ${CLUSTER_SOURCES_BACKEND_CPP}
        #${CLUSTER_SOURCES_FRONTEND_CPP}
    )
# header files
set(CLUSTER_SOURCES_H 
        ${CLUSTER_SOURCES_COMMON_H}
        ${CLUSTER_SOURCES_BACKEND_H}
        #${CLUSTER_SOURCES_FRONTEND_H}
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
        GraphReader
        SocialClusteringService
        Vertex
        Graph
        IntegerVectorEncoding
        Logger
        LoggerBufferEntry
        LoggerSeverityType
        LoggerSeverityLevel
        ConcurrentLockingQueue
        CoverageAnalyzer
        MQAnalyzer
        PerformanceAnalyzer
        FitnessAnalyzer
        IntegerEncodingInitializer
        ExplorationMutation
        UniformCrossoverEngine
        ClusterwiseCrossoverEngine
        ClusteringPopulationAnalyzer
        Selector
        ClusterRefiner
        GraphCoordinateTransformer
    )

#############
# Libraries #
#############

###########################
# Boost shared dependency #
###########################
set(Boost_USE_STATIC_LIBS OFF) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF) 
FIND_PACKAGE(Boost COMPONENTS filesystem system REQUIRED)
if(Boost_FOUND)
    message("-- Boost include directories added")
    include_directories(${INCLUDE_DIRECTORIES} ${Boost_INCLUDE_DIRS})
endif()
link_directories(${LINK_DIRECTORIES} ${Boost_LIBRARY_DIRS})

# add shared library

add_library(clusterer-shared SHARED ${CLUSTER_SOURCES})
# link boost library
target_link_libraries(clusterer-shared ${Boost_LIBRARIES})
# set library name
set_target_properties(clusterer-shared PROPERTIES OUTPUT_NAME "clusterer")
if(WIN32)
    set_target_properties(clusterer-shared PROPERTIES DEBUG_POSTFIX -d)
endif()
# output directories
# for non dll systems
set_target_properties(clusterer-shared PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib/shared)
set_target_properties(clusterer-shared PROPERTIES LIBRARY_OUTPUT_DIRECTORY_DEBUG ${PROJECT_SOURCE_DIR}/lib/shared)
set_target_properties(clusterer-shared PROPERTIES LIBRARY_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/lib/shared)
# for dll systems
set_target_properties(clusterer-shared PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/shared/lib)
set_target_properties(clusterer-shared PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${PROJECT_SOURCE_DIR}/lib/shared)
set_target_properties(clusterer-shared PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/lib/shared)
set_target_properties(clusterer-shared PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/shared/lib)
set_target_properties(clusterer-shared PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG ${PROJECT_SOURCE_DIR}/lib/shared)
set_target_properties(clusterer-shared PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/lib/shared) 

###########################
# Boost static dependency #
###########################
set(Boost_USE_STATIC_LIBS ON) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF) 
FIND_PACKAGE(Boost COMPONENTS filesystem system REQUIRED)
if(Boost_FOUND)
    message("--Reload boost include directories")
    include_directories(${INCLUDE_DIRECTORIES} ${Boost_INCLUDE_DIRS})
endif()
link_directories(${LINK_DIRECTORIES} ${Boost_LIBRARY_DIRS})

# add static library

add_library(clusterer-static STATIC ${CLUSTER_SOURCES})
# link boost library
target_link_libraries(clusterer-static ${Boost_LIBRARIES})

# link armadillo
if(UNIX)
    target_link_libraries(clusterer-static ${ARMADILLO_LIBRARIES})
endif()

# set library name
set_target_properties(clusterer-static PROPERTIES OUTPUT_NAME "clusterer")
if(WIN32)
    set_target_properties(clusterer-static PROPERTIES DEBUG_POSTFIX -d)
endif()
# output directories 
set_target_properties(clusterer-static PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib/static)
set_target_properties(clusterer-static PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${PROJECT_SOURCE_DIR}/lib/static)
set_target_properties(clusterer-static PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/lib/static) 

##############
# Executable #
##############

add_executable(Clusterer ${CLUSTER_SOURCES_FRONTEND})
target_link_libraries(Clusterer ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY})

# link clusterer library
if( WIN32 )
    target_link_libraries(Clusterer debug clusterer-static)
    target_link_libraries(Clusterer optimized clusterer-static)
    string(REGEX REPLACE "\\.lib" "" QWT_LIBRARIES_DEBUG ${QWT_LIBRARIES})
    target_link_libraries(Clusterer debug ${QWT_LIBRARIES_DEBUG}d.lib)
    target_link_libraries(Clusterer optimized ${QWT_LIBRARIES}) 
else()
    target_link_libraries(Clusterer clusterer-static)
    target_link_libraries(Clusterer pthread)
    target_link_libraries(Clusterer ${QWT_LIBRARIES})
endif()
# link boost library
target_link_libraries(Clusterer ${Boost_LIBRARIES})

# output directories
set_target_properties(Clusterer PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
set_target_properties(Clusterer PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG ${PROJECT_SOURCE_DIR}/bin/debug)
set_target_properties(Clusterer PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/bin/release)

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
    add_executable(${TEST_NAME} ${CLUSTER_TEST_DRIVER} ${CLUSTER_TEST_SOURCES})
    # link clusterer library
    if( WIN32 )
        target_link_libraries(${TEST_NAME} debug clusterer-static)
        target_link_libraries(${TEST_NAME} optimized clusterer-static)
    else()
        target_link_libraries(${TEST_NAME} clusterer-static)
        target_link_libraries(${TEST_NAME} pthread)
    endif()
    # link cpp unit library
    target_link_libraries(${TEST_NAME} debug ${CPPUNIT_DEBUG_LIBRARY})
    target_link_libraries(${TEST_NAME} optimized ${CPPUNIT_LIBRARY})
    # link boost library
    target_link_libraries(${TEST_NAME} ${Boost_LIBRARIES})

    # add tests to test solution folder for IDEs
    set_target_properties(${TEST_NAME} PROPERTIES FOLDER testing)

    # output directories
    set_target_properties(${TEST_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/testing)
    set_target_properties(${TEST_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG ${PROJECT_SOURCE_DIR}/testing/debug)
    set_target_properties(${TEST_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/testing/release)
    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME} --config $<CONFIGURATION> --exe $<TARGET_FILE:${TEST_NAME}>)
ENDFOREACH(test)

