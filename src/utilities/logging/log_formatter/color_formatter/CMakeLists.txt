add_library(color_formatter ColorFormatter.cpp ColorFormatter.h)

target_include_directories(color_formatter PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
