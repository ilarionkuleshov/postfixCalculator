project(stackLibTests)

set(SOURCES
    src/main.cpp
    src/tests.cpp
)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME}
    ${GTEST_LIBRARIES}
    lib::stackLib
)
