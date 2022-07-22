add_executable(block_reader_writer_test
        test.cpp
        )

# include the configured test header
target_include_directories(block_reader_writer_test PUBLIC "${PROJECT_BINARY_DIR}/test")

target_link_libraries(block_reader_writer_test PUBLIC readers_and_writers Catch2::Catch2WithMain)

catch_discover_tests(block_reader_writer_test)