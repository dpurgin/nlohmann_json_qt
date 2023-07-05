cmake_minimum_required(VERSION 3.12)
include(FetchContent)

if (NOT TARGET nlohmann_json)
    FetchContent_Declare(json
        GIT_REPOSITORY https://github.com/nlohmann/json.git
        GIT_TAG v3.9.1
        GIT_SHALLOW TRUE
    )
    set(JSON_BuildTests OFF CACHE BOOL "")
    set(JSON_Install OFF CACHE BOOL "")
    FetchContent_MakeAvailable(json)
endif()

set(CMAKE_AUTOMOC TRUE)

find_package(Qt5 COMPONENTS Core Test REQUIRED)

add_executable(nlohmann_json_qt_test test.cpp)
add_test(NAME nlohmann_json_qt_test COMMAND nlohmann_json_qt_test)

target_link_libraries(nlohmann_json_qt_test
    PUBLIC
        Qt5::Core
        Qt5::Test
        nlohmann_json
        nlohmann_json_qt
)
