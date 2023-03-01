#pragma once

#include "promql/parser/ast/visitor.hpp"

#include <functional>
#include <string>

namespace promql::parser::ast {

struct PosRange {
  std::size_t start;
  std::size_t end;
};

struct Expr {
  virtual ~Expr() = default;

  [[nodiscard]] virtual std::string String() const = 0;

  [[nodiscard]] virtual PosRange PositionRange() const {
    return pos_range;
  };

  PosRange pos_range;
};

}; // namespace promql::parser::ast
