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

inline spdlog::level::level_enum set_log_level(int level)
{
    auto log_level = spdlog::level::debug;
    switch (level) {
        case 1:
            log_level = spdlog::level::info;
            break;
        case 2:
            log_level = spdlog::level::warn;
            break;
        case 3:
            log_level = spdlog::level::err;
            break;
        default:
            log_level = spdlog::level::debug;
            break;
    }
    return log_level;
}

inline double difftime(TimePoint e_time, TimePoint s_time)
{
    return (double)(std::chrono::duration_cast<Unit>(e_time - s_time)).count() / 1000000000.0;
}