project(stackLib)

set(SOURCES src/stack.cpp)
set(HEADERS include/stack.hpp)

add_library(${PROJECT_NAME} ${SOURCES} ${HEADERS})
add_library(lib::stackLib ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/include
)
