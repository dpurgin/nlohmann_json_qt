cmake_minimum_required(VERSION 3.8)

project(nlohmann_json_qt LANGUAGES CXX)

option(JSON_QT_BUILD_TESTS "Build tests for nlohmann_json_qt" ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED 11)

add_library(nlohmann_json_qt INTERFACE)

find_package(Qt5Core REQUIRED)

target_include_directories(nlohmann_json_qt INTERFACE include)
target_link_libraries(nlohmann_json_qt INTERFACE Qt5::Core)
target_sources(nlohmann_json_qt INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include/nlohmann/json-qt.hpp)

if (JSON_QT_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
