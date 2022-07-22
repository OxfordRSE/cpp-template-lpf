add_library(low_pass_filter LowPassFilter.cpp )

target_include_directories(low_pass_filter INTERFACE  ${CMAKE_CURRENT_SOURCE_DIR})