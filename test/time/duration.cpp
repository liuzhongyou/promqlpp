#include <gtest/gtest.h>

#include "time/time.hpp"

#include <vector>

TEST(TimeDuration, ToString) {
    const std::vector<std::pair<int, std::string>> tc = {{
        { 1234, "1.234µs" },
        { 12345, "12.345µs" },
        { 123456, "123.456µs" },
        { 1234567, "1.234567ms" },
        { 12345678, "12.345678ms" },
        { 123456789, "123.456789ms" },
        { 1234567890, "1.23456789s" },
    }};

    for (const auto& [i, e] : tc) {
        ASSERT_EQ(Time::Duration(i).String(), e);
    }
}