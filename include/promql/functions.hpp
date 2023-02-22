#pragma once

#include <string>
#include <unordered_map>
#include <vector>

namespace promql::functions {

struct Function {
    enum class ValueType {
        NONE,
        VECTOR,
        SCALAR,
        MATRIX,
        STRING,
    };

    const std::string name;
    const std::vector<ValueType> arg_types;
    const ValueType return_type;

    const std::unordered_map<ValueType, std::string_view> &return_type_key = []() {
        static const std::unordered_map<ValueType, std::string_view> map{{
            {ValueType::NONE, "none"},
            {ValueType::VECTOR, "vector"},
            {ValueType::SCALAR, "scalar"},
            {ValueType::MATRIX, "matrix"},
            {ValueType::STRING, "string"},
        }};
        return map;
    }();
};

static const std::unordered_map<std::string, Function> functions {
        {"abs", Function{
            .name = "abs",
            .arg_types = {Function::ValueType::VECTOR},
            .return_type = Function::ValueType::VECTOR,
        }}
};

}; // namespace promql::functions

