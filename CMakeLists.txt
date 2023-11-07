cmake_minimum_required(VERSION 3.15.0)
project(lab6 VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

add_executable(lab6 main.cpp)

add_library(
    lexer

    lexer.cpp
    lexer.hpp
)

add_library(
    token

    token.cpp
    token.hpp
)

add_library(
    parser

    parser.cpp
    parser.hpp
)

add_library(
    interpreter

    interpreter.cpp
    interpreter.hpp
)

add_library(
    node

    node.hpp
    node.cpp
)

target_compile_features(lab6 PRIVATE cxx_std_20)
target_compile_features(lexer PRIVATE cxx_std_20)
target_compile_features(token PRIVATE cxx_std_20)
target_compile_features(parser PRIVATE cxx_std_20)
target_compile_features(interpreter PRIVATE cxx_std_20)
target_compile_features(node PRIVATE cxx_std_20)

target_link_libraries(lab6 PRIVATE lexer)
target_link_libraries(lab6 PRIVATE token)
target_link_libraries(lab6 PRIVATE parser)
target_link_libraries(lab6 PRIVATE interpreter)
target_link_libraries(lab6 PRIVATE node)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
