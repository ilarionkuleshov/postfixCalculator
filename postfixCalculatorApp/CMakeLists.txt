project(postfixCalculatorApp)

set(SOURCES
    src/main.cpp
    src/postfixCalculator.cpp
)
set(HEADERS include/postfixCalculator.hpp)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_include_directories(${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(${PROJECT_NAME} lib::stackLib)
