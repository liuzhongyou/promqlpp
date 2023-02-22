#pragma once

#include "promql/parser/ast/expr.hpp"
#include "promql/parser/ast/item_type.hpp"

#include <memory>

namespace promql::parser::ast {

struct AggreagteExpr : public Expr {
  ItemType op;
  std::unique_ptr<Expr> expr;
  std::unique_ptr<Expr> param;
  std::vector<std::string> grouping;
  bool without;

  explicit AggreagteExpr(ItemType op,
                         std::unique_ptr<Expr> &&expr,
                         std::unique_ptr<Expr> &&param,
                         std::vector<std::string> &&grouping,
                         bool without)
      : op{op}
      , expr{std::move(expr)}
      , param{std::move(param)}
      , grouping(std::move(grouping))
      , without{without} {
  }

  bool IsAggregatorWithParam() const {
    return op == ItemType::TOPK || op == ItemType::BOTTOMK || op == ItemType::COUNT_VALUES || op == ItemType::QUANTILE;
  }

  [[nodiscard]] std::string String() const override {
    std::string s;
    s += item_type_key.at(op);
    if (!grouping.empty()) {
      s += " ";
      if (without) {
        s += "without (";
        for (std::size_t i = 0; i < grouping.size() - 1; i++) {
          s += grouping[i];
          s += ", ";
        }
        s += grouping[grouping.size() - 1];
      } else {
        s += "by (";
        for (std::size_t i = 0; i < grouping.size() - 1; i++) {
          s += grouping[i];
          s += ", ";
        }
        s += grouping[grouping.size() - 1];
      }
      s += ")";
    }
    s += " (";
    if (IsAggregatorWithParam()) {
      s += param->String();
      s += ", ";
    }
    s += param->String();
    s += ")";
    return s;
  }

  [[nodiscard]] PosRange PositionRange() const override {
    return PosRange{0, 0};
  }
};

} // namespace promql::parser::ast