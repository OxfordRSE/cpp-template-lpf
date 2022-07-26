add_library(lock_in_amplifier LockInAmplifier.cpp LockInAmplifierCollection.cpp)

target_link_libraries(lock_in_amplifier low_pass_filter)

#may need to find a better way to include low_pass_filter directory
target_include_directories(lock_in_amplifier INTERFACE  ${CMAKE_CURRENT_SOURCE_DIR})