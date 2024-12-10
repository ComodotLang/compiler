add_library(console_logger ConsoleLogger.cpp ConsoleLogger.h)

target_include_directories(console_logger PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
