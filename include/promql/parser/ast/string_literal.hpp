#pragma once

#include "expr.hpp"

namespace promql::parser::ast {

struct StringLiteral : public Expr {
    std::string value;

    StringLiteral(std::string value) : value{std::move(value)} {}

    [[nodiscard]] std::string String() const override { return value; }
};

} // promql::parser::ast
