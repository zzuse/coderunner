#pragma once
#include "spdlog/async.h"
#include "spdlog/fmt/ostr.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/spdlog.h"
#include <chrono>

typedef std::chrono::high_resolution_clock Clock;
typedef std::chrono::nanoseconds Unit;
typedef std::chrono::time_point<std::chrono::system_clock> TimePoint;

inline void set_log_config(int level)
{
    spdlog::init_thread_pool(8192, 1);
    auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("run.log", true);
    spdlog::level::level_enum spd_log_level = spdlog::level::level_enum::info;
    switch (level) {
        case 0:
            spd_log_level = spdlog::level::level_enum::debug;
            break;
        case 1:
            spd_log_level = spdlog::level::level_enum::info;
            break;
        case 2:
            spd_log_level = spdlog::level::level_enum::warn;
            break;
        default:
            break;
    }
    console_sink->set_level(spdlog::level::level_enum::warn);
    file_sink->set_level(spd_log_level);

    std::vector<spdlog::sink_ptr> sinks{console_sink, file_sink};
    auto logger = std::make_shared<spdlog::async_logger>("leet", sinks.begin(), sinks.end(), spdlog::thread_pool(),
                                                         spdlog::async_overflow_policy::block);
    spdlog::register_logger(logger);
    spdlog::set_default_logger(logger);
    spdlog::flush_every(std::chrono::seconds(3));
    spdlog::set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%n] [%^%l%$] [%t] %v");
}

inline double difftime(TimePoint e_time, TimePoint s_time)
{
    return (double)(std::chrono::duration_cast<Unit>(e_time - s_time)).count() / 1000000000.0;
}