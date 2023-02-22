#pragma once

#include "promql/parser/ast.hpp"
#include "promql/parser/errors.hpp"
#include "promql/parser/lex.hpp"

#include <exception>
#include <memory>

namespace promql::parser {

struct Parser {
  std::string s;

  Lexer lexer{s};

  std::optional<Token> current;

  std::optional<Token> accept(Token::Kind kind) {
    if (auto token = lexer.peek(); token && token->kind == kind) {
      current = lexer.next();
      return current;
    }

    return std::nullopt;
  }

  std::optional<Token> accept(Token::Kind kind, auto &&func) {
    if (const auto token = lexer.peek(); token && token->kind == kind && func(token.value())) {
      current = lexer.next();
      return current;
    }

    return std::nullopt;
  }

  Token expect(Token::Kind kind) {
    if (auto token = accept(kind)) {
      return token.value();
    }

    throw parse_error{s, current->position};
  }

  using node_type = std::optional<std::unique_ptr<ast::Expr>>;

  node_type parseAggregateExpr() {
    static const auto isAggregateModifier = [](const Token &token) {
      return token.value == "by" || token.value == "without";
    };

    bool without;
    std::vector<std::string> grouping;
    ast::ItemType op = [this]() {
      static const std::unordered_map<std::string_view, ast::ItemType> map{{
          {"sum", ast::ItemType::SUM},
          {"avg", ast::ItemType::AVG},
          {"count", ast::ItemType::COUNT},
          {"min", ast::ItemType::MIN},
          {"max", ast::ItemType::MAX},
          {"group", ast::ItemType::GROUP},
          {"stddev", ast::ItemType::STDDEV},
          {"stdvar", ast::ItemType::STDVAR},
          {"topk", ast::ItemType::TOPK},
          {"bottomk", ast::ItemType::BOTTOMK},
          {"count_values", ast::ItemType::COUNT_VALUES},
          {"quantile", ast::ItemType::QUANTILE},
      }};

      return map.at(current->value);
    }();


    if (accept(Token::Kind::IDENTIFIER, isAggregateModifier)) {
      without = current->value == "without";

      expect(Token::Kind::RIGHT_PAREN);
      do {
        grouping.emplace_back(expect(Token::Kind::IDENTIFIER).value);
      } while (accept(Token::Kind::COMMA));
      expect(Token::Kind::LEFT_PAREN);

      if (auto expressions = parseExpressions()) {
        // TODO(mirco): check aggregate type
        auto params = std::move(expressions.value()[0]).value();
        auto expr = std::move(expressions.value()[1]).value();
        return std::make_unique<ast::AggreagteExpr>(op, std::move(params), std::move(expr), std::move(grouping), without);
      }

      return std::nullopt;
    } else if (auto expressions = parseExpressions()) {
        if (accept(Token::Kind::IDENTIFIER, isAggregateModifier)) {
          without = current->value == "without";

          expect(Token::Kind::RIGHT_PAREN);
          do {
            grouping.emplace_back(expect(Token::Kind::IDENTIFIER).value);
          } while (accept(Token::Kind::COMMA));
          expect(Token::Kind::LEFT_PAREN);
        }

        auto params = std::move(expressions.value()[0]).value();
        auto expr = std::move(expressions.value()[1]).value();
        return std::make_unique<ast::AggreagteExpr>(op, std::move(params), std::move(expr), std::move(grouping), without);
      }

      return std::nullopt;
  }

  node_type parseExpression() {
    std::optional<std::unique_ptr<ast::Expr>> node = std::nullopt;

    if (accept(Token::Kind::RIGHT_PAREN)) {
      node = parseParenExpr();
    } else if (accept(Token::Kind::IDENTIFIER, [](const Token &token) {
                 return token.value == "sum"
                     || token.value == "avg"
                     || token.value == "count"
                     || token.value == "min"
                     || token.value == "max"
                     || token.value == "group"
                     || token.value == "stddev"
                     || token.value == "stdvar"
                     || token.value == "topk"
                     || token.value == "bottomk"
                     || token.value == "count_values"
                     || token.value == "quantile";
               })) {
      node = parseAggregateExpr();
    }

    /*
    else if (auto expr = parseAggregateExpr()) {
        return std::make_unique<ast::AggreagteExpr>(std::move(expr.value));
    }
     */

    if (!node) {
      expect(Token::Kind::IDENTIFIER);
      node = std::make_unique<ast::VectorSelector>("on shit on shit");
    }

    if (accept(Token::Kind::AT)) {
      std::cout << "at" << std::endl;
      if (auto token = accept(Token::Kind::IDENTIFIER,
                              [](const Token &token) { return token.value == "start" || token.value == "end"; })) {
        std::cout << "start or end" << std::endl;
        node = std::make_unique<ast::VectorSelector>("shit");
        expect(Token::Kind::RIGHT_PAREN);
        expect(Token::Kind::LEFT_PAREN);
      }
    }

    return node;
    expect(Token::Kind::IDENTIFIER);
    return std::make_unique<ast::VectorSelector>("shit");
    return std::nullopt;
  }

  node_type parseParenExpr() {
    if (auto expr = parseExpression()) {
      expect(Token::Kind::LEFT_PAREN);
      return std::make_unique<ast::ParenExpr>(std::move(expr.value()));
    }

    return std::nullopt;
  }

  std::optional<std::vector<std::optional<std::unique_ptr<ast::Expr>>>> parseExpressions() {
    std::vector<std::optional<std::unique_ptr<ast::Expr>>> expressions;
    expect(Token::Kind::RIGHT_PAREN);
    do {
      expressions.emplace_back(parseExpression());
    } while (accept(Token::Kind::COMMA));
    expect(Token::Kind::LEFT_PAREN);
    return expressions;
  };

  node_type parse() {
    return parseExpression();
  }
};

} // namespace promql::parser