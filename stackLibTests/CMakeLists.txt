project(stackLibTests)

set(SOURCES
    src/main.cpp
    src/tests.cpp
    src/testUtils.cpp
)
set(HEADERS include/testUtils.hpp)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_include_directories(${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(${PROJECT_NAME}
    ${GTEST_LIBRARIES}
    lib::stackLib
)
