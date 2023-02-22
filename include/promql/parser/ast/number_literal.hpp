#pragma once

#include "expr.hpp"

namespace promql::parser::ast {

struct NumberLiteral : public Expr {
    float value;

    explicit NumberLiteral(float value) : value{value} {}

    // TODO correctly format float in case the value is round
    [[nodiscard]] std::string String() const override { return std::to_string(value); }
};

} // promql::parser::ast