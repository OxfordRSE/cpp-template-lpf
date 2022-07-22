add_library(readers_and_writers
        BlockReader.cpp
        BlockWriter.cpp
        filterCoefficientReader.cpp
        )

target_include_directories(readers_and_writers INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})