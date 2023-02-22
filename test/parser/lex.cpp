#include <gtest/gtest.h>

#include "promql/parser/lex.hpp"

#include <vector>
#include <string>

TEST(Lexer, Tokenization) {
    using namespace promql::parser;

    std::vector<std::pair<std::string, std::vector<Token::Kind>>> tc = {{
        { "(())", {
            Token::Kind::RIGHT_PAREN,
            Token::Kind::RIGHT_PAREN,
            Token::Kind::LEFT_PAREN,
            Token::Kind::LEFT_PAREN,
        } },
        { "!~===~!=", {
            Token::Kind::NEQ_REGEX,
            Token::Kind::EQLC,
            Token::Kind::EQL_REGEX,
            Token::Kind::NEQ,
        } },
        { R"("foo"="bar")", {
            Token::Kind::STRING,
            Token::Kind::EQL,
            Token::Kind::STRING,
        } },
        { R"(# Comment)", {
            Token::Kind::COMMENT,
        } },
        { R"(a + b)", {
            Token::Kind::IDENTIFIER,
            Token::Kind::ADD,
            Token::Kind::IDENTIFIER,
        } },
        { R"(avg by (a, b)
               # Comment
               (foo + bar))", {
            Token::Kind::IDENTIFIER, Token::Kind::IDENTIFIER, Token::Kind::RIGHT_PAREN, Token::Kind::IDENTIFIER, Token::Kind::COMMA, Token::Kind::IDENTIFIER, Token::Kind::LEFT_PAREN,
            Token::Kind::COMMENT,
            Token::Kind::RIGHT_PAREN, Token::Kind::IDENTIFIER, Token::Kind::ADD, Token::Kind::IDENTIFIER, Token::Kind::LEFT_PAREN,
        } }
    }};

    for (const auto &[query, t] : tc) {
        Lexer lexer{query};

        std::vector<Token::Kind> tokens = {};
        while (auto tok = lexer.next()) {
            tokens.push_back(tok->kind);
        }

        ASSERT_EQ(tokens, t);
    }
}

TEST(Lexer, Errors) {
    using namespace promql::parser;

    std::vector<std::string> tc {
        R"("non ending string)",
        R"("non ending string"")",
        R"("non ending string", ")",
    };

    for (const auto query : tc) {
        Lexer lexer{query};
        ASSERT_ANY_THROW(while (auto tok = lexer.next()) {});
    }
}