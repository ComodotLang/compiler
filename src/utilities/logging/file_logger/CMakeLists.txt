add_library(file_logger FileLogger.cpp FileLogger.h)

target_include_directories(file_logger PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
