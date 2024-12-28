cmake_minimum_required(VERSION 3.14)
project(comodotc)

set(CMAKE_CXX_STANDARD 17)

add_library(project_options INTERFACE)
target_compile_features(project_options INTERFACE cxx_std_17)

find_package(LLVM REQUIRED CONFIG)
if (NOT LLVM_FOUND)
    message(FATAL_ERROR "LLVM not found. Please ensure it is installed and accessible.")
endif()

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

llvm_map_components_to_libnames(llvm_libs support core irreader mcjit native)

add_subdirectory(src/utilities)

add_executable(comodotc 
    src/cli/main.cpp 
    src/codegen_llvm/module_generator.cpp
)

target_include_directories(comodotc PRIVATE ${LLVM_INCLUDE_DIRS})
target_compile_definitions(comodotc PRIVATE ${LLVM_DEFINITIONS})

target_link_libraries(comodotc PRIVATE project_options)
target_link_libraries(comodotc PRIVATE utilities)
target_link_libraries(comodotc PRIVATE ${llvm_libs})