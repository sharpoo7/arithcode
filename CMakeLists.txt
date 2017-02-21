cmake_minimum_required(VERSION 2.8)
project(ArithmeticCoding)
set(CPACK_PACKAGE_VERSION_MAJOR 0)
set(CPACK_PACKAGE_VERSION_MINOR 0)
set(CPACK_PACKAGE_VERSION_PATCH 0b)

set(CPACK_PACKAGE_DESCRIPTION_SUMMARY 
  "Arithmetic coding in C"
    )

# Check C++11
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
if(COMPILER_SUPPORTS_CXX11)
   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
   add_definitions(-DCOMPILEDWITHC11)
   message(STATUS "Using flag -std=c++11.")
else()
   message(FATAL_ERROR "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

set(CMAKE_BUILD_TYPE "Debug")
if (NOT CMAKE_BUILD_TYPE STREQUAL "Debug")
    message("-- No build type specified; defaulting to CMAKE_BUILD_TYPE=Release.")
    add_definitions(-O3)
endif(NOT CMAKE_BUILD_TYPE STREQUAL "Debug")

include_directories(src)
include_directories(.)

###############################################################################
#  Targets
###############################################################################

file(GLOB SOURCES src/*.h src/*.c)
add_executable(example app/main.cc ${SOURCES})

###############################################################################
#  Testing
###############################################################################

set(GTEST_ROOT ../thirdparty/gtest CACHE PATH "The root directory of the gtest install prefix")
find_package(gtest)
if(GTEST_FOUND)
  enable_testing()
  include_directories(${GTEST_INCLUDE_DIRS})
  file(GLOB TEST_SOURCES test/*.cc)
  add_executable(alltests 
    ${TEST_SOURCES}
    ${SOURCES}
    )
  target_link_libraries(alltests ${GTEST_BOTH_LIBRARIES})
  add_test(AllTests alltests)
endif()

###############################################################################
#  Documentation
###############################################################################

find_package(Doxygen)
if(DOXYGEN_FOUND)
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/doc/Doxyfile.in
                 ${CMAKE_CURRENT_BINARY_DIR}/doc/Doxyfile
                 @ONLY
                 )
  add_custom_target(apidocs
    ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/doc/Doxyfile
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT           "Generating API Docs"
    VERBATIM
    )
endif()
