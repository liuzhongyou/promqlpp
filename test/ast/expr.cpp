#include "promql/parser/ast.hpp"

#include <gtest/gtest.h>
#include <memory>
#include <vector>

#define B(Op, Lhs, Rhs)  std::make_unique<BinaryExpr>(Op, Lhs, Rhs)
#define M(Vector, Range) std::make_unique<MatrixSelector>(Vector, Range)
#define V(Name)          std::make_unique<VectorSelector>(Name)

TEST(AstExprPrinter, Expressions) {
  using namespace promql::parser::ast;

  {
    const auto n = std::make_unique<StringLiteral>("deadbeef");
    ASSERT_EQ(n->String(), "deadbeef");
  }

  {
    const auto n = std::make_unique<NumberLiteral>(5);
    ASSERT_EQ(n->String(), "5.000000");
  }

  {
    const auto n =
        std::make_unique<BinaryExpr>(ItemType::ADD, std::make_unique<NumberLiteral>(5), std::make_unique<NumberLiteral>(4));

    ASSERT_EQ(n->String(), "5.000000 + 4.000000");
  }

  {
    const auto n = B(ItemType::ADD, V("foo"), V("bar"));

    ASSERT_EQ(n->String(), "foo + bar");
  }

  {
    const auto n = B(ItemType::ADD, M(V("deadbeef"), Time::Minute), M(V("deadbeef"), Time::Minute));

    ASSERT_EQ(n->String(), "deadbeef[1m0s] + deadbeef[1m0s]");
  }
}
