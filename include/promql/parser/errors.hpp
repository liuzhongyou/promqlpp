#pragma once

#include "promql/parser/token.hpp"

#include <exception>
#include <string>
#include <utility>

namespace promql::parser {

struct parse_error : public std::exception {
  const std::string query;
  const Token::Position position;
  const std::string err =
      "expected token at col " + std::to_string(position.col) + " and row " + std::to_string(position.row);

  explicit parse_error(std::string query, Token::Position position)
      : query{std::move(query)}
      , position{position} {
  }

  [[nodiscard]] const char *what() const noexcept override {
    return err.c_str();
  }

  /*
  [[nodiscard]] std::string debug() const {
      std::size_t cur = 0;

      for (auto i = 0; i < position.row; i++) {
          cur = query.find('\n', cur + 1);
      }

      auto end = query.find('\n', cur + 1);
      if (end == std::string::npos) {
          std::cout << query << " " << query.size() << std::endl;
          end = query.size();
      }

      auto s = std::string{query.cbegin() + cur, query.cbegin() + end};

      s += "\n";
      for (auto i = 0; i < position.col - 1; i++) {
          s += " ";
      }
      s += "^";

      return s;
  }
  */
};

} // namespace promql::parser