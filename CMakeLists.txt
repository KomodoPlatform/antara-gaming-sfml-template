if (${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message(FATAL_ERROR "Prevented in-tree build. Please create a build directory outside of the source code and call cmake from there")
endif ()

cmake_minimum_required(VERSION 3.14)

set(CMAKE_CXX_STANDARD 17)

file(STRINGS "VERSION.md" VERSION_NB)

project(my_game_project VERSION ${VERSION_NB} DESCRIPTION "my_game_description" LANGUAGES CXX)

if (NOT "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    message(FATAL_ERROR "Only Clang is supported (minimum LLVM 8.0)")
endif ()

##! conf
if (${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    set(LINUX TRUE)
endif ()

include(FetchContent)

set(USE_SFML_ANTARA_WRAPPER ON CACHE BOOL "Override option" FORCE)

FetchContent_Declare(
        antara-gaming-sdk
        URL https://github.com/KomodoPlatform/antara-gaming-sdk/archive/master.zip
)

FetchContent_MakeAvailable(antara-gaming-sdk)

download_app_image()
add_subdirectory(${PROJECT_NAME})
