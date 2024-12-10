cmake_minimum_required(VERSION 3.14)

add_library(utilities INTERFACE)

add_subdirectory(logging)

target_include_directories(utilities INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(utilities INTERFACE logging)
