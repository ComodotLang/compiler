cmake_minimum_required(VERSION 3.14)
project(comodotc)

set(CMAKE_CXX_STANDARD 17)

add_library(project_options INTERFACE)  
target_compile_features(project_options INTERFACE cxx_std_17)

find_package(LLVM REQUIRED CONFIG)
message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

add_subdirectory(src/utilities)

add_executable(comodotc 
    src/cli/main.cpp 
)

llvm_map_components_to_libnames(llvm_libs support core irreader mcjit native)

target_include_directories(comodotc PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_include_directories(comodotc PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})                                      
target_link_libraries(comodotc PRIVATE project_options)
target_link_libraries(comodotc PRIVATE utilities)
target_link_libraries(comodotc ${REQ_LLVM_LIBRARIES})
target_compile_definitions(comodotc PRIVATE ${LLVM_DEFINITIONS})