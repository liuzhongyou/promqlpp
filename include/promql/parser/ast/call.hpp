#pragma once

#include "promql/functions.hpp"
#include "promql/parser/ast/expr.hpp"

namespace promql::parser::ast {

struct Call : public Expr {
  promql::functions::Function const &func;
  std::vector<std::unique_ptr<Expr>> arguments;

  explicit Call(promql::functions::Function const &func, std::vector<std::unique_ptr<Expr>> arguments)
      : func{func}
      , arguments{std::move(arguments)} {
  }

  [[nodiscard]] std::string String() const override {
    auto s = func.name;
    s += "(";
    if (!arguments.empty()) {
      for (std::size_t i = 0; i < arguments.size() - 1; i++) {
        s += arguments[i]->String();
        s += ", ";
      }
      s += arguments[arguments.size() - 1]->String();
    }
    s += ")";
    return s;
  }
};

} // namespace promql::parser::ast
