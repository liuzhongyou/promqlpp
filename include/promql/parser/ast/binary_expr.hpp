#pragma once

#include "promql/parser/ast/expr.hpp"
#include "promql/parser/ast/item_type.hpp"

#include <memory>

namespace promql::parser::ast {

struct BinaryExpr : public Expr {
  ItemType operation;
  std::unique_ptr<Expr> lhs, rhs;

  explicit BinaryExpr(ItemType operation, std::unique_ptr<Expr> &&lhs, std::unique_ptr<Expr> &&rhs)
      : operation{operation}
      , lhs{std::move(lhs)}
      , rhs{std::move(rhs)} {
  }

  [[nodiscard]] std::string String() const override {
    return lhs->String() + " " + item_type_key.at(operation) + " " + rhs->String();
  }

  [[nodiscard]] PosRange PositionRange() const override {
    return PosRange{
        lhs->pos_range.start,
        rhs->pos_range.end,
    };
  }
};

} // namespace promql::parser::ast
