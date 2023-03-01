#pragma once

#include "promql/parser/ast/expr.hpp"
#include "promql/parser/ast/item_type.hpp"
#include "time/duration.hpp"

#include <memory>
#include <optional>

namespace promql::parser::ast {

struct SubqueryExpr : public Expr {
  std::unique_ptr<Expr> expr;
  Time::Duration range;
  Time::Duration original_offset;
  Time::Duration offset;
  std::optional<std::uint64_t> timestamp;
  ItemType start_or_end;

  explicit SubqueryExpr(std::unique_ptr<Expr> expr,
                        Time::Duration range,
                        Time::Duration original_offset,
                        Time::Duration offset,
                        std::optional<std::uint64_t> timestamp,
                        ItemType start_or_end)
      : expr{std::move(expr)}
      , range{range}
      , original_offset{original_offset}
      , offset{offset}
      , timestamp{timestamp}
      , start_or_end{start_or_end} {
  }
};

} // namespace promql::parser::ast
