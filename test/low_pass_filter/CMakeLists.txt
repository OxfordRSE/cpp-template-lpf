add_executable(low_pass_filter_test
        test.cpp
        )

# include the configured test header
target_include_directories(low_pass_filter_test PUBLIC "${PROJECT_BINARY_DIR}/test")

target_link_libraries(low_pass_filter_test PUBLIC readers_and_writers low_pass_filter Catch2::Catch2WithMain)

#catch2 CTest integration
catch_discover_tests(low_pass_filter_test)