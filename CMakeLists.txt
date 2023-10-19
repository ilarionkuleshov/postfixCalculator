cmake_minimum_required(VERSION 3.10)
project(postfixCalculator VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(SOURCES
    src/main.cpp
    src/postfixCalculator.cpp
)

add_executable(postfixCalculator ${SOURCES})

target_include_directories(postfixCalculator
    PRIVATE 
        ${PROJECT_SOURCE_DIR}/include
)
