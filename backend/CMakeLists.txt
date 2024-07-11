cmake_minimum_required(VERSION 3.20.0)
set(CMAKE_CXX_STANDARD 17)
project(serverLib VERSION 1.0.0 LANGUAGES C CXX)
set(CMAKE_CXX_FLAGS "-g -Wall")

option(TEST "Build all tests." OFF)

# Directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})

# Code
file(GLOB_RECURSE sources src/*.cpp)
file(GLOB_RECURSE headers src/*.hpp)
include_directories(${CMAKE_SOURCE_DIR}/include)

find_package(nlohmann_json CONFIG REQUIRED) # nlohmann/json linking
find_package(Qt6 REQUIRED COMPONENTS Core Network) # Qt6 linking

# General library
add_library(serverLib ${sources} ${headers})
target_link_libraries(serverLib PRIVATE nlohmann_json::nlohmann_json Qt6::Core Qt6::Network) #GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main 

# Building examples
add_executable(fd_server ${CMAKE_SOURCE_DIR}/src/server.cpp)
add_executable(fd_daemon ${CMAKE_SOURCE_DIR}/src/daemon.cpp)
target_link_libraries(fd_server serverLib)
target_link_libraries(fd_daemon serverLib)

if (TEST)
    enable_testing()

    find_package(GTest CONFIG REQUIRED)

    include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

    file(GLOB_RECURSE test_sources src/*.cpp)
    add_executable(serverTests ${test_sources})

    target_link_libraries(serverTests gtest gtest_main)

    add_test(all-tests serverTests)
endif()