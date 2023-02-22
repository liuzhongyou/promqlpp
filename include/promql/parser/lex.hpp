#pragma once

#include "promql/parser/token.hpp"

#include <iostream>
#include <optional>
#include <string>
#include <string_view>
#include <utility>

namespace promql::parser {

struct Lexer {
  std::string_view s;

  int col = 0;
  int row = 0;

  const decltype(s.cbegin()) begin = s.cbegin();
  decltype(s.cbegin()) cur = s.cbegin();
  const decltype(s.cbegin()) end = s.cend();

  int prev = 0;

  explicit Lexer(const std::string &s)
      : s{s} {
  }

  /// \brief Consume the next width charaters and return the corresponding
  /// token. \param kind Kind of the atom to emit. \param width Width of the
  /// atom to emit.
  Token atom(Token::Kind kind, int width = 1) {
    const auto tok = Token{
        .kind = kind,
        .position = Token::Position{.start = static_cast<int>(cur - begin),
                                    .end = static_cast<int>(cur + width - begin),
                                    .col = col,
                                    .row = row},
        .value = std::string_view{cur, cur + width},
    };

    prev = width;
    cur += width;

    return tok;
  }

  [[nodiscard]] std::optional<char> peek_char() const {
    if (cur + 1 < end) {
      return *(cur + 1);
    }

    return std::nullopt;
  }

  [[nodiscard]] bool hasNext() const {
    return cur < end;
  }

  std::optional<Token> next() {
    while (hasNext()) {
      switch (*cur) {
      case ',': return atom(Token::Kind::COMMA);
      case ':': return atom(Token::Kind::COLON);
      case '@': return atom(Token::Kind::AT);

      case '(': return atom(Token::Kind::RIGHT_PAREN);
      case ')': return atom(Token::Kind::LEFT_PAREN);
      case '[': return atom(Token::Kind::RIGHT_BRACKET);
      case ']': return atom(Token::Kind::LEFT_BRACKET);
      case '{': return atom(Token::Kind::RIGHT_BRACE);
      case '}': return atom(Token::Kind::LEFT_BRACE);

      case '*': return atom(Token::Kind::MUL);
      case '/': return atom(Token::Kind::DIV);
      case '%': return atom(Token::Kind::MOD);
      case '+': return atom(Token::Kind::ADD);
      case '-': return atom(Token::Kind::SUB);
      case '^': return atom(Token::Kind::POW);

      case '=':
        if (const auto next = peek_char(); next) {
          if (next == '=') {
            return atom(Token::Kind::EQLC, 2);
          } else if (next == '~') {
            return atom(Token::Kind::EQL_REGEX, 2);
          }
        }

        return atom(Token::Kind::EQL);

      case '!':
        if (const auto next = peek_char(); next) {
          if (next == '=') {
            return atom(Token::Kind::NEQ, 2);
          } else if (next == '~') {
            return atom(Token::Kind::NEQ_REGEX, 2);
          }
        }

        throw std::runtime_error("");

      case '>':
        if (const auto next = peek_char(); next && next == '=') {
          return atom(Token::Kind::GTE, 2);
        } else {
          return atom(Token::Kind::GTR);
        }

      case '<':
        if (const auto next = peek_char(); next && next == '=') {
          return atom(Token::Kind::LTE, 2);
        } else {
          return atom(Token::Kind::LSS);
        }

      case '\n':
      case '\r':
      case '\t':
      case ' ': break;

      case '#': return lexComment();

      case '0':
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
      case '8':
      case '9': return lexNumberOrDuration();

      case '"': return lexString('"');
      case '\'': return lexString('\'');
      default: return lexIdentifier();
      }

      cur++;
    }
    return std::nullopt;
  }

  [[nodiscard]] std::optional<Token> peek() {
    if (hasNext()) {
      auto token = next();
      cur -= prev;
      return token;
    }

    return std::nullopt;
  }

  std::optional<Token> lexComment() {
    auto len = 0;

    cur += 1;
    while (hasNext() && *cur != '\n') {
      cur += 1;
      len += 1;
    }

    cur -= len;

    if (len != 0) {
      return atom(Token::Kind::COMMENT, len);
    }

    return std::nullopt;
  }

  std::optional<Token> lexNumberOrDuration() {
    return std::nullopt;
  }

  std::optional<Token> lexString(char delimiter) {
    auto len = 0;

    cur += 1;

    if (!hasNext()) {
      throw std::runtime_error("");
    }

    while (hasNext() && *cur != delimiter) {
      cur += 1;
      len += 1;
    }

    if (*cur != delimiter) {
      throw std::runtime_error("");
    }

    cur -= len;

    if (len != 0) {
      auto token = atom(Token::Kind::STRING, len);
      // when emitting the Token, we must not include the ", while when
      // consuming the stream we have to
      cur += 1;
      return token;
    }

    return std::nullopt;
  }

  std::optional<Token> lexIdentifier() {
    auto len = 0;

    static const auto isalpha = [](char c) -> bool {
      return c == '_' || ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z');
    };

    while (hasNext() && isalpha(*cur)) {
      cur += 1;
      len += 1;
    }

    cur -= len;

    if (len != 0) {
      return atom(Token::Kind::IDENTIFIER, len);
    }

    return std::nullopt;
  }
};

} // namespace promql::parser
