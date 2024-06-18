cmake_minimum_required(VERSION 3.10)

project(CoxLang)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED 17)

include_directories(src)
file(GLOB SOURCES "src/*.cpp")

add_executable(CoxLang ${SOURCES})