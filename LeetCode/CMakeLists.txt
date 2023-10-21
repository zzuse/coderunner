cmake_minimum_required(VERSION 3.5.1)
project(leet_code_test)

set(PROJECT_VERSION_MAJOR 0)
set(PROJECT_VERSION_MINOR 0)
set(PROJECT_VERSION_PATCH 1)

set(PROJECT_VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}")


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_THREAD_PREFER_PTHREAD ON)
set(THREADS_PREFER_PTHREAD_FLAG ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unknown-pragmas")

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

##################Debug############################
set(CMAKE_BUILD_TYPE "Debug" )
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -Wall -g -ggdb")

##################Release############################
#set( CMAKE_BUILD_TYPE "Release" )
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC  -lgomp -fno-lto -O3  -Wall")

##################MACROS#############################
##################MACROS#############################

SET(PRJ_HEADER_PATH include)

include_directories(${PRJ_HEADER_PATH})

add_subdirectory(utils)
# add_subdirectory(profiler)
# add_subdirectory(common)
add_subdirectory(framework)
# add_subdirectory(problems)
