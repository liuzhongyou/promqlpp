#pragma once

#include "promql/parser/ast/expr.hpp"

namespace promql::parser::ast {

struct ParenExpr : public Expr {
  std::unique_ptr<Expr> expr;

  explicit ParenExpr(std::unique_ptr<Expr> &&expr)
      : expr{std::move(expr)} {
  }

  [[nodiscard]] std::string String() const override {
    return "(" + expr->String() + ")";
  }
};

} // namespace promql::parser::ast
