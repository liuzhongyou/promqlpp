#include <fmt/format.h>

#include "promql/parser/parser.hpp"
#include "promql/parser/lex.hpp"

int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv) {
    /*
    {
            auto evalStmt = promql::EvalStmt{
                    promql::parse(q), 0, 100, 100, 100,
            };

            // fmt::print("{}\n", *evalStmt.expr);
    }
    */

    /*
    {
        using namespace promql::parser::ast;
        const auto expr = std::make_unique<StringLiteral>("deadbeef");

        fmt::print("{}\n", expr->String());
    }
*/
    /*
  {
      using namespace promql::parser::ast;

      std::vector<std::unique_ptr<Expr>> arguments;
      arguments.push_back(std::make_unique<NumberLiteral>(0.5));
      arguments.push_back(std::make_unique<BinaryExpr>(
             ItemType::ADD,
             std::make_unique<ParenExpr>(std::make_unique<BinaryExpr>(
                     ItemType::ADD,
                     std::make_unique<ParenExpr>(std::make_unique<NumberLiteral>(5)),
                     std::make_unique<ParenExpr>(std::make_unique<VectorSelector>("sysdig_cpu_container_cpu_used")))),
             std::make_unique<ParenExpr>(std::make_unique<NumberLiteral>(5))));

       auto expr = std::make_unique<Call>(
           promql::functions::functions.at("abs"), std::move(arguments)
       );
    fmt::print("{}\n", expr->String());
  }

{
  using namespace promql::parser::ast;
  auto evalStmt = EvalStmt{
      std::make_unique<BinaryExpr>(
          ItemType::LAND,
          std::make_unique<ParenExpr>(std::make_unique<BinaryExpr>(
              ItemType::ADD,
              std::make_unique<ParenExpr>(std::make_unique<NumberLiteral>(5)),
              std::make_unique<ParenExpr>(
                  std::make_unique<NumberLiteral>(5)))),
          std::make_unique<ParenExpr>(std::make_unique<NumberLiteral>(5))),
      Time::Time::Now(),
      Time::Time::Now(),
      Time::Duration(100),
      Time::Duration(100),
  };

  fmt::print("{}\n", evalStmt.expr->String());
}

    {
        auto lexer = promql::parser::Lexer{R"("non ending string"")"};
        while (auto tok = lexer.next()) {
            fmt::print("{}\n", tok->value);
        }
    }
*/

    {
        auto parser = promql::parser::Parser{argv[1]};
        if (const auto ast = parser.parse()) {
            fmt::print("{}\n", ast.value()->String());
        }
    }

  return 0;
}
