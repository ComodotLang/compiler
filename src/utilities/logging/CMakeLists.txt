add_subdirectory(console_logger)
add_subdirectory(file_logger)
add_subdirectory(log_formatter)
add_subdirectory(logger_manager)

add_library(logging INTERFACE
)

target_link_libraries(logging INTERFACE
     console_logger
     file_logger
     log_formatter
     logger_manager
)

target_include_directories(logging INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
