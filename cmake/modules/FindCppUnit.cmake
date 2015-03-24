# - Find CppUnit
# http://root.cern.ch/viewvc/trunk/cint/reflex/cmake/modules/FindCppUnit.cmake
#
# This module finds an installed CppUnit package.
#
# It sets the following variables:
#  CPPUNIT_FOUND       - Set to false, or undefined, if CppUnit isn't found.
#  CPPUNIT_INCLUDE_DIR - The CppUnit include directory.
#  CPPUNIT_LIBRARY     - The CppUnit library to link against.

FIND_PATH(	CPPUNIT_INCLUDE_DIR NAMES cppunit/Test.h	HINTS $ENV{CPPUNIT_ROOT}	PATH_SUFFIXES include )

# With Win32, important to have both
IF(WIN32)
  FIND_LIBRARY(CPPUNIT_LIBRARY cppunit
               ${CPPUNIT_INCLUDE_DIR}/../lib
               /usr/local/lib
               /usr/lib)
  FIND_LIBRARY(CPPUNIT_DEBUG_LIBRARY cppunitd
               ${CPPUNIT_INCLUDE_DIR}/../lib
               /usr/local/lib
               /usr/lib)
ELSE(WIN32)
  # On unix system, debug and release have the same name
  FIND_LIBRARY(CPPUNIT_LIBRARY cppunit
               ${CPPUNIT_INCLUDE_DIR}/../lib
               /usr/local/lib
               /usr/lib)
  FIND_LIBRARY(CPPUNIT_DEBUG_LIBRARY cppunit
               ${CPPUNIT_INCLUDE_DIR}/../lib
               /usr/local/lib
               /usr/lib)
ENDIF(WIN32)

IF(CPPUNIT_INCLUDE_DIR AND CPPUNIT_LIBRARY)
    SET(CPPUNIT_FOUND TRUE)
    SET(CPPUNIT_LIBRARIES ${CPPUNIT_LIBRARY} ${CMAKE_DL_LIBS})
    SET(CPPUNIT_DEBUG_LIBRARIES ${CPPUNIT_DEBUG_LIBRARY} ${CMAKE_DL_LIBS})
ENDIF(CPPUNIT_INCLUDE_DIR AND CPPUNIT_LIBRARY)

IF (CPPUNIT_FOUND)
   # show which CppUnit was found only if not quiet
   IF (NOT CppUnit_FIND_QUIETLY)
      MESSAGE(STATUS "Found CppUnit: ${CPPUNIT_LIBRARY}")
   ENDIF (NOT CppUnit_FIND_QUIETLY)
ELSE (CPPUNIT_FOUND)
   # fatal error if CppUnit is required but not found
   IF (CppUnit_FIND_REQUIRED)
      MESSAGE(FATAL_ERROR "Could not find CppUnit")
   ENDIF (CppUnit_FIND_REQUIRED)
ENDIF (CPPUNIT_FOUND)
