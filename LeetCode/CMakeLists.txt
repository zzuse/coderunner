cmake_minimum_required(VERSION 3.5.1)
project(leet_code_test)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unknown-pragmas")

set( EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin )
set( LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib )

##################Debug############################
set( CMAKE_BUILD_TYPE "Debug" )
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -Wall -g -ggdb")

##################Release############################
#set( CMAKE_BUILD_TYPE "Release" )
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC  -lgomp -fno-lto -O3  -Wall")

##################MACROS#############################
##################MACROS#############################

SET(PRJ_HEADER_PATH include utils/yaml utils/json/nlohmann utils/catch utils/file_op utils/argparse)

include_directories(${PRJ_HEADER_PATH})

set(THIRD_PARTY_LIBS
        -lleet_code
        libstdc++.a
        -lm
        )

add_subdirectory(utils)
# add_subdirectory(profiler)
# add_subdirectory(common)
# add_subdirectory(cases)
# add_subdirectory(framework)
# add_subdirectory(problems)
