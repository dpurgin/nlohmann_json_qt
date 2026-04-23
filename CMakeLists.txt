cmake_minimum_required(VERSION 3.8)

if (DEFINED PROJECT_NAME)
    set(JSON_QT_STANDALONE OFF)
else()
    set(JSON_QT_STANDALONE ON)
endif()

project(nlohmann_json_qt LANGUAGES CXX)

option(JSON_QT_BUILD_TESTS "Build tests for nlohmann_json_qt" ${JSON_QT_STANDALONE})
set(JSON_QT_REQUIRED_QT_VERSION_MAJOR "auto" CACHE STRING "Required major version of Qt")
set_property(CACHE JSON_QT_REQUIRED_QT_VERSION_MAJOR PROPERTY STRINGS auto 5 6)

message(CHECK_START "Checking for Qt version ${JSON_QT_REQUIRED_QT_VERSION_MAJOR}...")

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)

if (NOT JSON_QT_REQUIRED_QT_VERSION_MAJOR STREQUAL "auto" AND
        NOT JSON_QT_REQUIRED_QT_VERSION_MAJOR STREQUAL QT_VERSION_MAJOR)
    message(FATAL_ERROR "Required Qt ${JSON_QT_REQUIRED_QT_VERSION_MAJOR} does not match found Qt version ${QT_VERSION_MAJOR}")
else()
    message(CHECK_PASS "Found Qt ${QT_VERSION_MAJOR}")
endif()

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED 11)

add_library(nlohmann_json_qt INTERFACE include/nlohmann/json-qt.hpp)

find_package(Qt${QT_VERSION_MAJOR}Core REQUIRED)

target_include_directories(nlohmann_json_qt INTERFACE include)
target_link_libraries(nlohmann_json_qt INTERFACE Qt${QT_VERSION_MAJOR}::Core)
target_sources(nlohmann_json_qt INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include/nlohmann/json-qt.hpp)

if (JSON_QT_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
