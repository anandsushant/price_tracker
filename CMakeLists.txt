cmake_minimum_required(VERSION 3.10)

# Project name
project(price_tracker)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include header directory
include_directories(inc)

# Collect source files
file(GLOB SOURCES 
        "src/*.cpp"
        "src/listener/*.cpp"
        "src/tracker/*.cpp")

# Create executable
add_executable(pt ${SOURCES})
add_executable(send "misc/sender.cpp")