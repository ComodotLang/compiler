add_subdirectory(color_formatter)
add_subdirectory(default_formatter)
add_subdirectory(interface)

add_library(log_formatter INTERFACE
)

target_link_libraries(log_formatter INTERFACE
    color_formatter
    default_formatter
     interface
)

target_include_directories(log_formatter INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
