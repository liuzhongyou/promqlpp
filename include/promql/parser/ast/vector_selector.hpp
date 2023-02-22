#pragma once

#include "expr.hpp"

namespace promql::parser::ast {

struct VectorSelector : public Expr {
  std::string name;

  explicit VectorSelector(std::string name) : name{std::move(name)} {}

  [[nodiscard]] std::string String() const override { return name; }
  [[nodiscard]] PosRange PositionRange() const override { return pos_range; }
};

} // namespace promql::parser::ast
