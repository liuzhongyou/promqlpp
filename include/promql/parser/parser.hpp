#pragma once

#include "lex.hpp"
#include "ast.hpp"

#include <memory>
#include <exception>

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

        throw std::runtime_error("expected token");
    }

    using node_type = std::optional<std::unique_ptr<ast::Expr>>;

    node_type parseAggregateExpr() {
        ast::ItemType op = [this]() {
            static const std::unordered_map<std::string_view, ast::ItemType> map{{
                { "avg", ast::ItemType::AVG },
            }};

            return map.at(current->value);
        }();
        std::unique_ptr<ast::Expr> params;
        std::vector<std::string> grouping;
        bool without = false;

        if (auto token = accept(Token::Kind::IDENTIFIER, [](const Token &token) {
            return token.value == "by"
                || token.value == "without";
        })) {
            if (token->value == "without") {
                without = true;
            }

            expect(Token::Kind::RIGHT_PAREN);
            do {
                grouping.emplace_back(expect(Token::Kind::IDENTIFIER).value);
            } while (accept(Token::Kind::COMMA));
            expect(Token::Kind::LEFT_PAREN);

            return std::make_unique<ast::AggreagteExpr>(op, std::make_unique<ast::VectorSelector>("Shit"), std::move(params), std::move(grouping), without);



            /*
            std::cout << "yep, aggreaget" << std::endl;

            if (accept(Token::Kind::IDENTIFIER), [](const Token &token) {
                return token.value == "by";
            }) {
                expect(Token::Kind::RIGHT_PAREN);
                do {
                    grouping.emplace_back(expect(Token::Kind::IDENTIFIER).value);
                } while (accept(Token::Kind::COMMA));
                expect(Token::Kind::LEFT_PAREN);
            }
            */
        }

        return std::nullopt;
    }

    node_type parseParenExpr() {
        if (auto expr = parseExpression()) {
            expect(Token::Kind::LEFT_PAREN);
            return std::make_unique<ast::ParenExpr>(std::move(expr.value()));
        }

        throw std::runtime_error("expected expression");
    }

    node_type parseExpression() {
        if (accept(Token::Kind::RIGHT_PAREN)) {
            return parseParenExpr();
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
            return parseAggregateExpr();
        }

        /*
        else if (auto expr = parseAggregateExpr()) {
            return std::make_unique<ast::AggreagteExpr>(std::move(expr.value));
        }
         */

        return std::nullopt;
    }

    node_type parse() {
        return parseExpression();
    }
};

} // namespace promql::parser