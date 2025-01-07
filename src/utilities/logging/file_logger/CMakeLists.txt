add_library(file_logger file_logger.cpp file_logger.h)

target_include_directories(file_logger PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
