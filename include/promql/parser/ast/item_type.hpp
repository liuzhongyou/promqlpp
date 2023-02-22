#pragma once

#include <unordered_map>
#include <string>

namespace promql::parser::ast {

enum struct ItemType {
    // Operators.
    LAND,
    LOR,
    LUNLESS,
    ATAN2,

    // Aggregators.
    SUM,
    AVG,
    COUNT,
    MIN,
    MAX,
    GROUP,
    STDDEV,
    STDVAR,
    TOPK,
    BOTTOMK,
    COUNT_VALUES,
    QUANTILE,

    // Keywords
    OFFSET,
    BY,
    WITHOUT,
    ON,
    IGNORING,
    GROUP_LEFT,
    GROUP_RIGHT,
    BOOL,

    // Preprocessors.
    START,
    END,

    // Tokens.
    LEFT_PAREN,
    RIGHT_PAREN,
    LEFT_BRACE,
    RIGHT_BRACE,
    LEFT_BRACKET,
    RIGHT_BRACKET,
    COMMA,
    EQL,
    COLON,
    SEMICOLON,
    BLANK,
    TIMES,
    SPACE,

    // Operations.
    SUB,
    ADD,
    MUL,
    MOD,
    DIV,
    EQLC,
    NEQ,
    LTE,
    LSS,
    GTE,
    GTR,
    EQL_REGEX,
    NEQ_REGEX,
    POW,
};

static const std::unordered_map<ItemType, std::string> item_type_key{{
     // Operators.
     {ItemType::LAND, "and"},
     {ItemType::LOR, "or"},
     {ItemType::LUNLESS, "unless"},
     {ItemType::ATAN2, "atan2"},

     // Aggregators.
     {ItemType::SUM, "sum"},
     {ItemType::AVG, "avg"},
     {ItemType::COUNT, "count"},
     {ItemType::MIN, "min"},
     {ItemType::MAX, "max"},
     {ItemType::GROUP, "group"},
     {ItemType::STDDEV, "stddev"},
     {ItemType::STDVAR, "stdvar"},
     {ItemType::TOPK, "topk"},
     {ItemType::BOTTOMK, "bottomk"},
     {ItemType::COUNT_VALUES, "count_values"},
     {ItemType::QUANTILE, "quantile"},

     // Keywords.
     {ItemType::OFFSET, "offset"},
     {ItemType::BY, "by"},
     {ItemType::WITHOUT, "without"},
     {ItemType::ON, "on"},
     {ItemType::IGNORING, "ignoring"},
     {ItemType::GROUP_LEFT, "group_left"},
     {ItemType::GROUP_RIGHT, "group_right"},
     {ItemType::BOOL, "bool"},

     // Preprocessors.
     {ItemType::START, "start"},
     {ItemType::END, "end"},

     // Tokens.
     {ItemType::LEFT_PAREN, "("},
     {ItemType::RIGHT_PAREN, ")"},
     {ItemType::LEFT_BRACE, "{"},
     {ItemType::RIGHT_BRACE, "}"},
     {ItemType::LEFT_BRACKET, "["},
     {ItemType::RIGHT_BRACKET, "]"},
     {ItemType::COMMA, ","},
     {ItemType::EQL, "="},
     {ItemType::COLON, ":"},
     {ItemType::SEMICOLON, ";"},
     {ItemType::BLANK, "_"},
     {ItemType::TIMES, "x"},
     {ItemType::SPACE, " "},

     // Operations.
     {ItemType::SUB, "-"},
     {ItemType::ADD, "+"},
     {ItemType::MUL, "*"},
     {ItemType::MOD, "%"},
     {ItemType::DIV, "/"},
     {ItemType::EQLC, "=="},
     {ItemType::NEQ, "!="},
     {ItemType::LTE, "<="},
     {ItemType::LSS, "<"},
     {ItemType::GTE, ">="},
     {ItemType::GTR, ">"},
     {ItemType::EQL_REGEX, "=~"},
     {ItemType::NEQ_REGEX, "!~"},
     {ItemType::POW, "^"},
}};

}; // namespace promql::parser::ast