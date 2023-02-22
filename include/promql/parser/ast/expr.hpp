#pragma once

#include <string>
#include <functional>

namespace promql::parser::ast {

struct PosRange {
  std::size_t start;
  std::size_t end;
};

struct Expr {
  [[nodiscard]] virtual std::string String() const = 0;

  [[nodiscard]] virtual PosRange PositionRange() const {
      return pos_range;
  };

  virtual ~Expr() = default;

  PosRange pos_range;
};

}; // namespace promql::parser::ast
