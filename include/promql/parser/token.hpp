#pragma once

#include <string_view>

namespace promql::parser {

struct Token {
    enum struct Kind : int {
        RIGHT_PAREN,
        LEFT_PAREN,

        RIGHT_BRACKET,
        LEFT_BRACKET,

        RIGHT_BRACE,
        LEFT_BRACE,

        COMMA,
        COLON,

        NEQ,
        NEQ_REGEX,

        EQL,
        EQL_REGEX,

        EQLC,

        LTE,
        LSS,

        GTE,
        GTR,

        MUL,
        DIV,
        MOD,
        ADD,
        SUB,
        POW,

        AT,

        IDENTIFIER,
        STRING,
        NUMBER,
        DURATION,

        COMMENT,
    };

    Kind kind;
    std::pair<int, int> position;
    std::string_view value;
};

} // namespace promql::parser