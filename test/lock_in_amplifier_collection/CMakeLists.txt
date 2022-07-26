add_executable(lock_in_amplifier_collection_test
        test.cpp
        )

# include the configured test header
target_include_directories(lock_in_amplifier_collection_test PRIVATE ${PROJECT_SOURCE_DIR}/include
        PUBLIC "${PROJECT_BINARY_DIR}/test")

target_link_libraries(lock_in_amplifier_collection_test
        PUBLIC
        readers_and_writers
        low_pass_filter
        lock_in_amplifier
        nlohmann_json::nlohmann_json
        Catch2::Catch2WithMain)

#catch2 CTest integration
catch_discover_tests(lock_in_amplifier_collection_test)