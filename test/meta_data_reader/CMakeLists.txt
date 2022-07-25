add_executable(meta_data_reader_test
        test.cpp
        )

# include the configured test header
target_include_directories(meta_data_reader_test PUBLIC "${PROJECT_BINARY_DIR}/test")

target_link_libraries(meta_data_reader_test PUBLIC meta_data_reader Catch2::Catch2WithMain)

#catch2 CTest integration
catch_discover_tests(meta_data_reader_test)