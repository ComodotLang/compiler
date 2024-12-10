add_library(logger_manager LoggerManager.cpp LoggerManager.h)

target_include_directories(logger_manager PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
