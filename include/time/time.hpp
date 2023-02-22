#pragma once

#include "duration.hpp"

#include <string>
#include <ctime>
#include <chrono>
#include <sys/time.h>

namespace Time {

class Time {
  std::uint64_t wall;
  std::int64_t ext;

  Time(std::uint64_t wall, std::int64_t ext) : wall{wall}, ext{ext} {}

public:
    static Time Now() {
        const auto now = std::chrono::high_resolution_clock::now().time_since_epoch();
        const auto wall = std::chrono::duration_cast<std::chrono::milliseconds>(now).count();
        const auto ext = std::chrono::duration_cast<std::chrono::nanoseconds>(now).count();
        return Time{static_cast<std::uint64_t>(wall), ext};
    }

    // TODO support nanosecond precision when parsing date
    static Time Parse(const std::string &s, const std::string &format = "%Y-%m-%dT%H:%M:%S") {
        std::tm tm = {};
        strptime(s.c_str(), format.c_str(), &tm);
        const auto tp = std::chrono::system_clock::from_time_t(std::mktime(&tm)).time_since_epoch();
        const auto wall = std::chrono::duration_cast<std::chrono::seconds>(tp).count();
        return Time{static_cast<std::uint64_t>(wall), 0};
    }

    std::string String() {
        static const auto bufsize = 31;
        static const auto tmpsize = 21;

        const std::timespec timespec = {
            .tv_sec = static_cast<__time_t>(wall),
            .tv_nsec = ext,
        };

        const auto tm = std::localtime(&timespec.tv_sec);

        char buf[bufsize];
        std::strftime(buf, tmpsize, "%Y-%m-%dT%H:%M:%S.", tm);
        // TODO truncate trailing 0s to guarantee parity with Go
        std::sprintf(buf + tmpsize -1, "%09luZ", timespec.tv_nsec);

        return {buf, buf + bufsize - 1};
    }
};

}; // namespace Time
