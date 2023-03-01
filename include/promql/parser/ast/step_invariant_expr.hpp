#pragma once

#include "promql/parser/ast/expr.hpp"

#include <memory>

namespace promql::parser::ast {

struct StepInvariantExpr : public Expr {
  std::unique_ptr<Expr> expr;

  explicit StepInvariantExpr(std::unique_ptr<Expr> &&expr)
      : expr{std::move(expr)} {
  }

  [[nodiscard]] std::string String() const override {
    return expr->String();
  }
};

} // namespace promql::parser::ast
