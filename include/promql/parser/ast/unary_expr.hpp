#pragma once

#include "promql/parser/ast/expr.hpp"
#include "promql/parser/ast/item_type.hpp"

#include <memory>

namespace promql::parser::ast {

struct UnaryExpr : public Expr {
  ItemType operation;
  std::unique_ptr<Expr> expr;

  explicit UnaryExpr(ItemType operation, std::unique_ptr<Expr> &&expr)
      : operation{operation}
      , expr{std::move(expr)} {
  }

  [[nodiscard]] std::string String() const override {
    return item_type_key.at(operation) + expr->String();
  }
};

} // namespace promql::parser::ast
