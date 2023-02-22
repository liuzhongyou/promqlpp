#pragma once

#include <string>

namespace Time {

class Duration {
  std::int64_t d;

  static constexpr std::int64_t nanosecond_ = 1;
  static constexpr std::int64_t microsecond_ = 1000 * nanosecond_;
  static constexpr std::int64_t millisecond_ = 1000 * microsecond_;
  static constexpr std::int64_t second_ = 1000 * millisecond_;
  static constexpr std::int64_t minute_ = 60 * second_;
  static constexpr std::int64_t hour_ = 60 * minute_;

  static constexpr void fmtFrac(char *buf, int &w, std::int64_t &v, int prec) {
    auto print = false;
    for (int i = 0; i < prec; i++) {
      auto digit = v % 10;
      print = print || digit != 0;
      if (print) {
        w--;
        buf[w] = digit + '0';
      }
      v /= 10;
    }
    if (print) {
      w--;
      buf[w] = '.';
    }
  }

  static constexpr void fmtInt(char *buf, int &w, std::int64_t v) {
    if (v == 0) {
      w--;
      buf[w] = '0';
    } else {
      while (v > 0) {
        w--;
        buf[w] = (v % 10) + '0';
        v /= 10;
      }
    }
  }

  public:
  constexpr explicit Duration(std::int64_t d)
      : d{d} {
  }

  // String returns a string representing the duration in the form "72h3m0.5s".
  // Leading zero units are omitted. As a special case, durations less than one
  // second format use a smaller unit (milli-, micro-, or nanoseconds) to ensure
  // that the leading digit is non-zero. The zero duration formats as 0s.
  [[nodiscard]] std::string String() const {
    char buf[32];

    auto w = 32;
    auto u = d;
    auto neg = d < 0;

    if (neg) {
      u = -u;
    }

    if (u < second_) {
      auto prec = 0;

      w--;
      buf[w] = 's';
      w--;
      if (u == 0) {
        return "0s";
      } else if (u < microsecond_) {
        prec = 0;
        buf[w] = 'n';
      } else if (u < millisecond_) {
        prec = 3;
        w--;
        buf[w] = static_cast<char>(0xC2);
        buf[w + 1] = static_cast<char>(0xB5);
      } else {
        prec = 6;
        buf[w] = 'm';
      }
      fmtFrac(buf, w, u, prec);
      fmtInt(buf, w, u);
    } else {
      w--;
      buf[w] = 's';

      fmtFrac(buf, w, u, 9);
      fmtInt(buf, w, u % 60);
      u /= 60;

      if (u > 0) {
        w--;
        buf[w] = 'm';
        fmtInt(buf, w, u % 60);
        u /= 60;

        if (u > 0) {
          w--;
          buf[w] = 'h';
          fmtInt(buf, w, u);
        }
      }
    }

    if (neg) {
      w--;
      buf[w] = '-';
    }

    return {buf + w, buf + 32};
  }

  [[nodiscard]] constexpr std::int64_t Nanoseconds() const {
    return d;
  }

  [[nodiscard]] constexpr std::int64_t Microseconds() const {
    return d / 1e3;
  }

  [[nodiscard]] constexpr std::int64_t Milliseconds() const {
    return d / 1e6;
  }

  [[nodiscard]] constexpr float Seconds() const {
    auto sec = d / second_;
    auto nsec = d % second_;
    return sec + nsec / 1e9;
  }

  [[nodiscard]] constexpr float Minutes() const {
    auto min = d / minute_;
    auto nsec = d % minute_;
    return min + nsec / (60 * 1e9);
  }

  [[nodiscard]] constexpr float Hours() const {
    auto hour = d / hour_;
    auto nsec = d % hour_;
    return hour + nsec / (60 * 60 * 1e9);
  }
};

constexpr Duration operator*(std::int64_t lhs, const Duration &rhs) {
  return Duration(lhs * rhs.Nanoseconds());
}

constexpr Duration operator*(const Duration &lhs, std::int64_t rhs) {
  return Duration(lhs.Nanoseconds() * rhs);
}

static constexpr Duration Nanosecond = Duration(1);
static constexpr Duration Microsecond = 1000 * Nanosecond;
static constexpr Duration Millisecond = 1000 * Microsecond;
static constexpr Duration Second = 1000 * Millisecond;
static constexpr Duration Minute = 60 * Second;
static constexpr Duration Hour = 60 * Minute;

}; // namespace Time
