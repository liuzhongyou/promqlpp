#pragma once

#include "promql/parser/ast/expr.hpp"
#include "time/duration.hpp"

#include <memory>
#include <optional>

namespace promql::parser::ast {

struct VectorSelector : public Expr {
  std::string name;
  Time::Duration original_offset;
  Time::Duration offset;
  std::optional<std::uint64_t> timestamp;
  ItemType start_or_end;
  std::vector<LabelMatchers> label_matchers;

  explicit VectorSelector(std::string name)
      : name{std::move(name)}
      , original_offset{0}
      , offset{0}
      , timestamp{0}
      , start_or_end{}
      , label_matchers{} {
  }

  // TODO(mirco): optimize arguments
  explicit VectorSelector(std::string name,
                          Time::Duration original_offset,
                          Time::Duration offset,
                          std::optional<std::uint64_t> timestamp,
                          ItemType start_or_end,
                          std::vector<LabelMatchers> label_matchers)
      : name{std::move(name)}
      , original_offset{original_offset}
      , offset{offset}
      , timestamp{timestamp}
      , start_or_end{start_or_end}
      , label_matchers{std::move(label_matchers)} {
  }

  [[nodiscard]] std::string String() const override {
    std::string s = name;
    std::string labels;
    if (!label_matchers.empty()) {
      for (std::size_t i = 0; i < label_matchers.size() - 1; i++) {
        labels += label_matchers[i].String();
      }
      labels += label_matchers[label_matchers.size() - 1].String();
    }
    if (!labels.empty()) {
      s += "{";
      s += labels;
      s += "}";
    }
    if (original_offset) {
      s += " offset ";
      if (original_offset > Time::Duration(0)) {
        s += original_offset.String();
      } else {
        s += "-";
        s += original_offset.String();
      }
    }
    if (timestamp) {

    } else if (start_or_end == ItemType::START) {
      s += " @ start()";
    } else if (start_or_end == ItemType::END) {
      s += " @ end()";
    }
    return s;
  }
};

} // namespace promql::parser::ast
