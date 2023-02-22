#pragma once

#include "promql/parser/ast/expr.hpp"

namespace promql::parser::ast {

struct StringLiteral : public Expr {
  std::string value;

  explicit StringLiteral(std::string value)
      : value{std::move(value)} {
  }

  [[nodiscard]] std::string String() const override {
    return value;
  }
};

} // namespace promql::parser::ast
