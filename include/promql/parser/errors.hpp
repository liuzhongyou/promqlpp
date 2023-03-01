#pragma once

#include "promql/parser/token.hpp"

#include <exception>
#include <string>
#include <utility>

namespace promql::parser {

struct parse_error : public std::exception {
  const std::string query;
  const std::string message;
  const Token::Position position;
  const std::string err;

  explicit parse_error(std::string query, std::string message, Token::Position position)
      : query{std::move(query)}
      , message{std::move(message)}
      , position{position} {
  }

  explicit parse_error(std::string query, Token::Position position)
      : query{std::move(query)}
      , position{position}
      , err{"expected token at col " + std::to_string(position.col) + " and row " + std::to_string(position.row)} {
  }

  [[nodiscard]] const char *what() const noexcept override {
    if (!message.empty()) {
      return message.c_str();
    } else {
      return err.c_str();
    }
  }

  // TODO(mirco): pretty error messages, possibly genearte json that can be sent to the frontend for better visibility
    [[nodiscard]] std::string debug() const {
        std::size_t start = 0;

        for (auto i = 0; i < position.row; i++) {
            start = query.find('\n', start + 1);
        }

        auto end = query.find('\n', start + 1);
        if (end == std::string::npos) {
            end = query.size();
        }

        auto s = std::string{query.cbegin() + start, query.cbegin() + start + position.col + 1};
        s += "\033[1;31m";
        s += std::string{query.cbegin() + start + position.col + 1, query.cbegin() + start + position.col + (position.end - position.start) + 1};
        s += "\033[0m";
        s += std::string{ query.cbegin() + start + position.col + (position.end - position.start) + 1, query.cbegin() + end};

        s += "\n";
        for (auto i = 0; i < position.col + (position.end - position.start); i++) {
            s += " ";
        }
        s += "\033[1;31m^\033[0m";

        return s;
    }
};

} // namespace promql::parser
