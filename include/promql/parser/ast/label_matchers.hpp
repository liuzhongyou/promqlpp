#pragma once

#include <string>
#include <unordered_map>

namespace promql::parser::ast {

struct LabelMatchers {
  enum class Type {
    MatchEqual,
    MatchNotEqual,
    MatchRegexp,
    MatchNotRegexp,
  };

  // TODO(mirco): support regexp matching with hyperscan
  Type type;
  std::string name;
  std::string value;

  [[nodiscard]] std::string String() const {
    auto type_to_str = [](Type type) {
      static const std::unordered_map<Type, std::string> map{{
          {Type::MatchEqual, "="},
          {Type::MatchNotEqual, "!="},
          {Type::MatchRegexp, "=~"},
          {Type::MatchNotRegexp, "!~"},
      }};

      return map.at(type);
    };

    return name + type_to_str(type) + value;
  }
};

} // namespace promql::parser::ast
