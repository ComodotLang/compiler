add_library(default_formatter DefaultFormatter.cpp DefaultFormatter.h)

target_include_directories(default_formatter PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
