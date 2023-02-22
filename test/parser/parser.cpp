#include "promql/parser/parser.hpp"

#include "promql/parser/ast.hpp"

#include <gtest/gtest.h>

// TODO(mirco): proper unit testing
TEST(Parser, Basic) {
  using namespace promql::parser::ast;

  std::vector<std::pair<std::string, std::unique_ptr<Expr>>> tc = {};

  promql::parser::Parser parser{"quantile by (a, b, c) (metric)"};
  ASSERT_NO_THROW(parser.parse());
}