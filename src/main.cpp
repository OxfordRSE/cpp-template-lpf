#include <chrono>
#include <functional>
#include <iostream>
#include <optional>
#include <random>

#include <CLI/CLI.hpp>
#include <spdlog/spdlog.h>

// This file will be generated automatically when you run the CMake configuration step.
// It creates a namespace called `cpp_template_lpf`.
// You can modify the source template at `configured_files/config.hpp.in`.
#include <internal_use_only/config.hpp>

#include "low_pass_filter.hpp"

void write_test_file(const size_t n, const std::string &filename)
{
  std::ofstream writer(filename, std::ios::out | std::ios::binary);
  if (!writer) { throw std::system_error(errno, std::system_category(), fmt::format("Failed to open {}", filename)); }

  const unsigned seed = static_cast<unsigned>(std::chrono::system_clock::now().time_since_epoch().count());
  std::default_random_engine generator(seed);
  std::uniform_real_distribution<double> distribution(0.0, 1.0);

  std::vector<double> data(n);
  std::generate(std::begin(data), std::end(data), [&]() { return distribution(generator); });

  // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
  auto *const buffer = reinterpret_cast<char *>(data.data()); // cppcheck-suppress invalidPointerCast
  writer.write(buffer, static_cast<std::streamsize>(data.size() * sizeof(double)));
  writer.close();
}


// NOLINTNEXTLINE(bugprone-exception-escape)
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

    const std::string data_filename = "test_in.dat";
    const std::string processed_data_filename = "test_out.dat";

    // write out some random data for testing
    write_test_file(config.input_data_size, data_filename);

    // setup reader and writer
    std::ifstream reader(data_filename, std::ios::out | std::ios::binary);
    if (!reader) {
      throw std::system_error(errno, std::system_category(), fmt::format("Failed to open {}", data_filename));
    }

    std::ofstream writer(processed_data_filename, std::ios::out | std::ios::binary);
    if (!writer) {
      throw std::system_error(errno, std::system_category(), fmt::format("Failed to open {}", processed_data_filename));
    }

    spdlog::info("Started data analysis");
    cpp_template_lpf::low_pass_filter(reader, writer, config);
    spdlog::info("Finished data analysis");

    reader.close();
    writer.close();
  } catch (const std::exception &e) {
    spdlog::error("Unhandled exception in main: {}", e.what());
  }
}
