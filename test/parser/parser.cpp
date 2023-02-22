#include <gtest/gtest.h>

#include "promql/parser/ast.hpp"
#include "promql/parser/parser.hpp"

TEST(Parser, Basic) {
    using namespace promql::parser::ast;

    // std::vector<std::pair<std::string, std::unique_ptr<Expr>>> tc = {};

    promql::parser::Parser parser{"(())"};
    parser.parse();
}