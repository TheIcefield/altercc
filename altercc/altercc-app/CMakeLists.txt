set(target_name altercc)

add_executable(${target_name} altercc/main.cpp)

target_link_libraries(${target_name} altercc-lib)
