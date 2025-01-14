add_library(lexer lexer.cpp lexer.h)

target_include_directories(lexer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(lexer_test lexer_test.cpp)

target_link_libraries(lexer_test PRIVATE lexer gtest_main)

add_test(NAME lexer_test COMMAND lexer_test)