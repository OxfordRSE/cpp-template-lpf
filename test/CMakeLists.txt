set(TEST_DATA_DIR "${CMAKE_SOURCE_DIR}/test_data")
configure_file(testConfig.hpp.in testConfig.hpp)

# Tests using Catch2-provided main
find_package(Catch2 REQUIRED)

#catch2 CTest integration
include(CTest)
include(Catch)

#TODO FIND out what PUBLIC and INTERFACE mean I think what I have is not-optimal

add_subdirectory(block_reader_writer)
add_subdirectory(low_pass_filter)
add_subdirectory(lock_in_amplifier)
add_subdirectory(lock_in_amplifier_collection)


