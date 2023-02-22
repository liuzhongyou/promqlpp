#pragma once

#include "promql/parser/ast/expr.hpp"
#include "time/duration.hpp"
#include "time/time.hpp"

namespace promql::parser::ast {

struct EvalStmt {
  std::unique_ptr<Expr> expr;

  Time::Time start, End;
  Time::Duration interval;
  Time::Duration lookback_delta;

  [[nodiscard]] std::string String() const {
    return expr->String();
  }
};

} // namespace promql::parser::ast
