#ifndef LOGGING_LOGGER_HPP
#define LOGGING_LOGGER_HPP

#include <string>

#include "spdlog/common.h"
#include "spdlog/logger.h"

namespace logging {

class Logger {
public:
  static void init(const std::string &logfile,
      spdlog::level::level_enum level = spdlog::level::info);

  template<typename... Args>
  static inline void write(
      const spdlog::source_loc& loc,
      spdlog::level::level_enum level,
      fmt::format_string<Args...> fmt,
      Args&&... args) {

      logger_sm -> log(loc, level, fmt, std::forward<Args>(args)...);
  }

private:
  static std::shared_ptr<spdlog::logger> logger_sm;
};

/// initialize logging for the application
/// need to be called before calling any logging macro
void init();

} // namespace logging ends


#define LOG_DEBUG(...) \
  logging::Logger::write(spdlog::source_loc{__FILE__, __LINE__, SPDLOG_FUNCTION}, spdlog::level::debug, __VA_ARGS__)

#define LOG_INFO(...) \
  logging::Logger::write(spdlog::source_loc{__FILE__, __LINE__, SPDLOG_FUNCTION}, spdlog::level::info, __VA_ARGS__)

#define LOG_WARN(...) \
  logging::Logger::write(spdlog::source_loc{__FILE__, __LINE__, SPDLOG_FUNCTION}, spdlog::level::warn, __VA_ARGS__)

#define LOG_ERR(...) \
  logging::Logger::write(spdlog::source_loc{__FILE__, __LINE__, SPDLOG_FUNCTION}, spdlog::level::err, __VA_ARGS__)

#define LOG_CRIT(...) \
  logging::Logger::write(spdlog::source_loc{__FILE__, __LINE__, SPDLOG_FUNCTION}, spdlog::level::critical, __VA_ARGS__)

#endif
