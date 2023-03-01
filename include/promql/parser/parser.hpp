#pragma once

#include "promql/parser/ast.hpp"
#include "promql/parser/errors.hpp"
#include "promql/parser/lex.hpp"

#include <cassert>
#include <exception>
#include <memory>

namespace promql::parser {

struct Parser {
  using node_type = std::unique_ptr<ast::Expr>;
  using nodes_type = std::vector<std::unique_ptr<ast::Expr>>;

  std::string s;

  Lexer lexer{s};

  std::optional<Token> current = std::nullopt;

  std::optional<Token> accept(Token::Kind kind) {
    if (auto token = lexer.peek(); token && token->kind == kind) {
      current = lexer.next();
      return current;
    }

    return std::nullopt;
  }

  void setAtModifierPreprocessor(std::unique_ptr<ast::Expr> &expr, ast::ItemType type) const {
    if (auto vectorSelector = dynamic_cast<ast::VectorSelector *>(expr.get())) {
      vectorSelector->start_or_end = type;
      return;
    }

    if (auto subquery = dynamic_cast<ast::SubqueryExpr *>(expr.get())) {
      subquery->start_or_end = type;
      return;
    }

    // TODO(mirco): this should be a syntactic error, not a parsing one
    throw parse_error{s, current->position};
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

    // TODO(mirco): propagate reason for parse error
    throw parse_error{s, current->position};
  }

  const std::unordered_map<std::string_view, ast::ItemType> &aggregations = []() {
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

    return map;
  }();

  // TODO(mirco): abstract things a bit further to reduce code duplication
  node_type parseAggregateExpr() {
    if (!accept(Token::Kind::IDENTIFIER, [this](const Token &token) { return aggregations.contains(token.value); })) {
      return nullptr;
    }

    static const auto parseAggregateModifier = [](const Token &token) {
      return token.value == "by" || token.value == "without";
    };

    ast::ItemType op;
    if (aggregations.contains(current->value)) {
      op = aggregations.at(current->value);
    }

    bool without;
    std::vector<std::string> grouping;

    if (accept(Token::Kind::IDENTIFIER, parseAggregateModifier)) {
      without = current->value == "without";

      expect(Token::Kind::RIGHT_PAREN);
      do {
        grouping.emplace_back(expect(Token::Kind::IDENTIFIER).value);
      } while (accept(Token::Kind::COMMA));
      expect(Token::Kind::LEFT_PAREN);

      if (auto expressions = parseExpressions(); !expressions.empty()) {
        if (ast::AggregateExpr::IsAggregatorWithParam(op)) {
          // TODO(mirco): assert expressions length properly
          if (expressions.size() != 2) {
            throw parse_error{s, "must be 2", current->position};
          }
          return std::make_unique<ast::AggregateExpr>(
              op, std::move(expressions[0]), std::move(expressions[1]), std::move(grouping), without);
        } else {
          if (expressions.size() != 1) {
            throw parse_error{s, "must be 1", current->position};
          }
          return std::make_unique<ast::AggregateExpr>(
              op, nullptr, std::move(expressions[0]), std::move(grouping), without);
        }
      }

      return nullptr;
    } else if (auto expressions = parseExpressions(); !expressions.empty()) {
      if (accept(Token::Kind::IDENTIFIER, parseAggregateModifier)) {
        without = current->value == "without";

        expect(Token::Kind::RIGHT_PAREN);
        do {
          grouping.emplace_back(expect(Token::Kind::IDENTIFIER).value);
        } while (accept(Token::Kind::COMMA));
        expect(Token::Kind::LEFT_PAREN);
      }

      if (ast::AggregateExpr::IsAggregatorWithParam(op)) {
        // TODO(mirco): assert expressions length properly
        if (expressions.size() != 2) {
          throw parse_error{s, "must be 2", current->position};
        }
        return std::make_unique<ast::AggregateExpr>(
            op, std::move(expressions[0]), std::move(expressions[1]), std::move(grouping), without);
      } else {
        if (expressions.size() != 1) {
          throw parse_error{s, "must be 1", current->position};
        }
        return std::make_unique<ast::AggregateExpr>(
            op, nullptr, std::move(expressions[0]), std::move(grouping), without);
      }
    }

    return nullptr;
  }

  node_type parseFuncExpression() {
    if (!accept(Token::Kind::IDENTIFIER,
                [](const Token &token) { return functions::functions.contains(token.value); })) {
      return nullptr;
    }

    auto func = current->value;
    if (auto args = parseExpressions(); !args.empty()) {
      return std::make_unique<ast::Call>(functions::functions.at(func), std::move(args));
    }

    return nullptr;
  }

  node_type parseExpression() {
    std::unique_ptr<ast::Expr> node = nullptr;

    if (auto expr = parseParenExpr()) {
      return expr;
    }

    if (auto expr = parseAggregateExpr()) {
      return expr;
    }

    if (auto expr = parseFuncExpression()) {
      return expr;
    }

    expect(Token::Kind::IDENTIFIER);
    node = std::make_unique<ast::VectorSelector>(std::string{current->value},
                                                 Time::Duration(0),
                                                 Time::Duration(0),
                                                 std::nullopt,
                                                 ast::ItemType::ADD,
                                                 std::vector<ast::LabelMatchers>{});
    if (accept(Token::Kind::AT)) {
      if (auto token = accept(Token::Kind::IDENTIFIER,
                              [](const Token &token) { return token.value == "start" || token.value == "end"; })) {
        setAtModifierPreprocessor(node, token->value == "start" ? ast::ItemType::START : ast::ItemType::END);
        node = std::make_unique<ast::StepInvariantExpr>(std::move(node));
        expect(Token::Kind::RIGHT_PAREN);
        expect(Token::Kind::LEFT_PAREN);
      }
    }

    return node;
  }

  node_type parseParenExpr() {
    if (accept(Token::Kind::RIGHT_PAREN)) {
      if (auto expr = parseExpression()) {
        expect(Token::Kind::LEFT_PAREN);
        return std::make_unique<ast::ParenExpr>(std::move(expr));
      }
    }

    return nullptr;
  }

  nodes_type parseExpressions() {
    nodes_type expressions;
    if (accept(Token::Kind::RIGHT_PAREN)) {
      do {
        expressions.emplace_back(parseExpression());
      } while (accept(Token::Kind::COMMA));
      expect(Token::Kind::LEFT_PAREN);
    }
    return expressions;
  };

  node_type parse() {
    return parseExpression();
  }
};

} // namespace promql::parser
