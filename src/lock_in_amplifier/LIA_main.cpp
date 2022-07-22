#include <functional>
#include <iostream>
#include <optional>

#include <CLI/CLI.hpp>
#include <spdlog/spdlog.h>

// This file will be generated automatically when you run the CMake configuration step.
// It creates a namespace called `cpp_template_lpf`.
// You can modify the source template at `configured_files/config.hpp.in`.
#include <internal_use_only/config.hpp>

#include "low_pass_filter.hpp"

int main(int argc, const char **argv)
{
  try {
    CLI::App app{ fmt::format(
      "{} version {}", cpp_template_lpf::cmake::project_name, cpp_template_lpf::cmake::project_version) };

    bool show_version = false;
    app.add_flag("--version", show_version, "Show version information");

    CLI11_PARSE(app, argc, argv);

    if (show_version) {
      fmt::print("{}\n", cpp_template_lpf::cmake::project_version);
      return EXIT_SUCCESS;
    }

    cpp_template_lpf::LpfConfig config;

    const std::string data_filename = "../test_data/risingAmplitudeSine.bin";
    const std::string processed_data_filename = "../test_data/liaOutput.bin";

    // setup reader and writer
    std::ifstream reader(data_filename, std::ios::out | std::ios::binary);
    if (!reader) {
      throw std::system_error(errno, std::system_category(), fmt::format("Failed to open {}", data_filename));
    }

    std::ofstream writer(processed_data_filename, std::ios::out | std::ios::binary);
    if (!writer) {
      throw std::system_error(errno, std::system_category(), fmt::format("Failed to open {}", processed_data_filename));
    }

    spdlog::info("Started lock-in amplification analysis");
    cpp_template_lpf::low_pass_filter(reader, writer, config);
    spdlog::info("Finished data analysis");

    reader.close();
    writer.close();
  } catch (const std::exception &e) {
    spdlog::error("Unhandled exception in main: {}", e.what());
  }
}
