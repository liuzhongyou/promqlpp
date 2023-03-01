#include "promql/parser/ast/visitor.hpp"
#include "promql/parser/parser.hpp"

#include <fmt/format.h>

int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv) {
  using promql::parser::Parser;

  try {
      auto parser = Parser{argv[1]};
      if (auto ast = parser.parse()) {
          fmt::print("{}\n", ast->String());
      }
  } catch (const promql::parser::parse_error &err) {
      fmt::print("{}\n", err.debug());
  }

  return 0;
}
