#include <gtest/gtest.h>

#include "promql/parser/ast.hpp"

#include <vector>
#include <memory>

TEST(AstExprs, SimpleExpressions) {
    using namespace promql::parser::ast;

    {
        const auto n = std::make_unique<StringLiteral>("deadbeef");
        ASSERT_EQ(n->String(), "deadbeef");
    }

    {
        const auto n = std::make_unique<NumberLiteral>(5);
        ASSERT_EQ(n->String(), "5.000000");
    }
}

TEST(AstExprs, BinaryExpressions) {
    using namespace promql::parser::ast;

    {
        const auto n = std::make_unique<BinaryExpr>(
            ItemType::ADD,
            std::make_unique<NumberLiteral>(5),
            std::make_unique<NumberLiteral>(4)
        );

        ASSERT_EQ(n->String(), "5.000000 + 4.000000");
    }

    {
        const auto n = std::make_unique<BinaryExpr>(
                ItemType::ADD,
                std::make_unique<VectorSelector>("foo"),
                std::make_unique<VectorSelector>("bar")
        );

        ASSERT_EQ(n->String(), "foo + bar");
    }
}