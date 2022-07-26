find_package(fmt CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(CLI11 CONFIG REQUIRED)

add_subdirectory(low_pass_filter)
add_subdirectory(readers_and_writers)
add_subdirectory(lock_in_amplifier)