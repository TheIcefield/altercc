cmake_minimum_required(VERSION 3.18)

set(PROJECT_NAME altercc)

project(
    ${PROJECT_NAME}
    VERSION 1.0
    LANGUAGES CXX
)

add_subdirectory(external)
add_subdirectory(altercc)
add_subdirectory(tests)
