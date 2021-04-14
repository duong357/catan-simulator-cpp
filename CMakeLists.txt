cmake_minimum_required(VERSION 3.17)
project(catanSimulator)

set(CMAKE_CXX_STANDARD 14)

file(GLOB src "*.h" "*.cpp")

add_executable(catanSimulator ${src})