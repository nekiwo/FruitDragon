cmake_minimum_required(VERSION 3.20.0)
set(CMAKE_CXX_STANDARD 20)
project(serverLib VERSION 1.0.0 LANGUAGES C CXX)
set(CMAKE_CXX_FLAGS "-g -Wall")

option(TEST "Build all tests." OFF)

# Directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include") 

# Code
file(GLOB_RECURSE sources src/*.cpp)
file(GLOB_RECURSE headers src/*.hpp)
include_directories(${CMAKE_SOURCE_DIR}/include)

# Check if FFmpeg is installed
execute_process(
    COMMAND bash -c "ffmpeg -version > /dev/null"
    ERROR_VARIABLE bashOut
)
if(NOT bashOut STREQUAL "")
    message(FATAL_ERROR "FFmpeg CLI tool not found.")
endif()

find_package(nlohmann_json CONFIG REQUIRED) # nlohmann/json linking
find_package(ZLIB) # TagLib linking
find_package(TagLib REQUIRED) # TagLib linking
find_package(Qt6 REQUIRED COMPONENTS Core Network) # Qt6 linking

# General library
add_library(serverLib ${sources} ${headers})
target_link_libraries(serverLib PRIVATE nlohmann_json::nlohmann_json Qt6::Core Qt6::Network TagLib::tag) #GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main tagreader

# Building examples
add_executable(fd_server ${CMAKE_SOURCE_DIR}/src/server.cpp)
add_executable(fd_daemon ${CMAKE_SOURCE_DIR}/src/daemon.cpp)
target_link_libraries(fd_server serverLib)
target_link_libraries(fd_daemon serverLib)

if (TEST)
    enable_testing()

    find_package(GTest CONFIG REQUIRED)

    include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

    file(GLOB_RECURSE test_sources ${CMAKE_SOURCE_DIR}/tests/*.cpp)
    foreach(test_source ${test_sources})
        get_filename_component(test_source_name ${test_source} NAME_WE)
        add_executable(${test_source_name} ${test_source})
        set_target_properties(${test_source_name} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/tests)
        target_link_libraries(${test_source_name} gtest gtest_main serverLib)
        add_test(${test_source_name} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/tests/${test_source_name})
    endforeach()

    file(REMOVE_RECURSE ${CMAKE_SOURCE_DIR}/tests/music/Cache)
endif()