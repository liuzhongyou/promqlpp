#pragma once

#include "promql/parser/ast/expr.hpp"
#include "promql/parser/ast/vector_selector.hpp"

namespace promql::parser::ast {

struct MatrixSelector : public Expr {
  std::unique_ptr<ast::VectorSelector> expr;
  Time::Duration range;

  explicit MatrixSelector(std::unique_ptr<ast::VectorSelector> expr, Time::Duration range)
      : expr(std::move(expr))
      , range{range} {
  }

  [[nodiscard]] std::string String() const override {
    return expr->String() + "[" + range.String() + "]";
  }
};

} // namespace promql::parser::ast
