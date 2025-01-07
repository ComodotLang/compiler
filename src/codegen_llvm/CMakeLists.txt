add_library(codegen_llvm module_generator.cpp codegen.cpp codegen.h)

target_include_directories(codegen_llvm PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})