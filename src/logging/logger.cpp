#include <filesystem>
#include <iostream>

#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/spdlog.h"

#include "logging/logger.hpp"
#include "utils/common.hpp"

namespace logging {

// initialize static instance logger
std::shared_ptr<spdlog::logger> Logger::logger_sm = nullptr;

void Logger::init(const std::string& logfile,
    spdlog::level::level_enum level) {

  try {
    auto file_sink = 
      std::make_shared<spdlog::sinks::basic_file_sink_mt>(logfile, false);

    logger_sm = std::make_shared<spdlog::logger>("FastLspLogger", file_sink);
    logger_sm -> set_level(level);
    logger_sm -> set_pattern("%Y-%m-%d %H:%M:%S.%f %l PID %P TID %t %s:%# %! %v");

    spdlog::register_logger(logger_sm);

    LOG_INFO("Logger initialized");
  } catch (const spdlog::spdlog_ex& ex) {
    throw std::runtime_error {
      std::string {"Logger initialization failed: "} + ex.what()
    };
  }
}

void init() {
  /// initialize the logger inside the user home directory
  const std::filesystem::path home = cmn::GetHomeDirectory();
  if (home.empty()) {
    std::cerr << "Home directory not found. Cannot initialize logger." << std::endl;
    std::exit(EXIT_FAILURE);
  }

  const std::filesystem::path logfile = std::filesystem::path(cmn::FAST_LSP_DIR) /
    std::filesystem::path(cmn::FAST_LSP_LOG_FILE);

  try {
    Logger::init(home / logfile, spdlog::level::info);
  } catch (const std::exception& ex) {
    std::cerr << "Falied to initialize logging due to: " << ex.what() << std::endl;
  } catch (...) {
    std::cerr << "Falied to initialize logging. Unknown error occurred." << std::endl;
    std::exit(EXIT_FAILURE);  
  }
}

} // namespace logging ends

