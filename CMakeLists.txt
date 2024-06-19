cmake_minimum_required(VERSION 3.14)

project(CoxLang)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (WIN32)
    set(CMAKE_C_COMPILER "C:/MinGW/bin/gcc.exe")
    set(CMAKE_CXX_COMPILER "C:/MinGW/bin/g++.exe")
else()
    set(CMAKE_C_COMPILER "/usr/bin/gcc")
    set(CMAKE_CXX_COMPILER "/usr/bin/g++")
endif()

include(FetchContent)

FetchContent_Declare(
    fmt
    GIT_REPOSITORY https://github.com/fmtlib/fmt.git
    GIT_TAG 9.1.0
)

FetchContent_MakeAvailable(fmt)

include_directories(src)
file(GLOB SOURCES "src/*.cpp")

add_executable(CoxLang ${SOURCES})

target_link_libraries(CoxLang PRIVATE fmt::fmt)