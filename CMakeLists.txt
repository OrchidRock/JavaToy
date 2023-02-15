cmake_minimum_required(VERSION 3.5.1)

project(JavaToy)

add_subdirectory(lexer)
add_subdirectory(parser)
add_subdirectory(symbols)
add_subdirectory(inter)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PUBLIC lexer parser inter symbols)
