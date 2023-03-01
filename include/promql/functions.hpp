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
  const bool variadic;
  const ValueType return_type;
};

static const std::unordered_map<std::string_view, Function> functions{
    {"abs",
     Function{
         .name = "abs",
         .arg_types = {Function::ValueType::VECTOR},
         .return_type = Function::ValueType::VECTOR,
     }},
    {"absent",
     Function{
         .name = "absent",
         .arg_types = {Function::ValueType::VECTOR},
         .return_type = Function::ValueType::VECTOR,
     }},
    {"absent_over_time",
     Function{
         .name = "absent_over_time",
         .arg_types = {Function::ValueType::MATRIX},
         .return_type = Function::ValueType::VECTOR,
     }},
    {"acos",
     Function{
         .name = "acos",
         .arg_types = {Function::ValueType::VECTOR},
         .return_type = Function::ValueType::VECTOR,
     }},
    {"acosh",
     Function{
         .name = "acosh",
         .arg_types = {Function::ValueType::VECTOR},
         .return_type = Function::ValueType::VECTOR,
     }},
    {"asin",
     Function{
         .name = "asin",
         .arg_types = {Function::ValueType::VECTOR},
         .return_type = Function::ValueType::VECTOR,
     }},
    {"asinh",
     Function{
         .name = "asinh",
         .arg_types = {Function::ValueType::VECTOR},
         .return_type = Function::ValueType::VECTOR,
     }},
    {"atan",
     Function{
         .name = "atan",
         .arg_types = {Function::ValueType::VECTOR},
         .return_type = Function::ValueType::VECTOR,
     }},
    {"atanh",
     Function{
         .name = "atanh",
         .arg_types = {Function::ValueType::VECTOR},
         .return_type = Function::ValueType::VECTOR,
     }},
    {"avg_over_time",
     Function{
         .name = "avg_over_time",
         .arg_types = {Function::ValueType::MATRIX},
         .return_type = Function::ValueType::VECTOR,
     }},
    {"ceil",
     Function{
         .name = "ceil",
         .arg_types = {Function::ValueType::VECTOR},
         .return_type = Function::ValueType::VECTOR,
     }},
    {"changes",
     Function{
         .name = "changes",
         .arg_types = {Function::ValueType::MATRIX},
         .return_type = Function::ValueType::VECTOR,
     }},
    {"clamp",
     Function{
         .name = "clamp",
         .arg_types = {Function::ValueType::VECTOR, Function::ValueType::SCALAR, Function::ValueType::SCALAR},
         .return_type = Function::ValueType::VECTOR,
     }},
    {"clamp_max",
     Function{
         .name = "clamp_max",
         .arg_types = {Function::ValueType::VECTOR, Function::ValueType::SCALAR},
         .return_type = Function::ValueType::VECTOR,
     }},
    {"clamp_min",
     Function{
         .name = "clamp_min",
         .arg_types = {Function::ValueType::VECTOR, Function::ValueType::SCALAR},
         .return_type = Function::ValueType::VECTOR,
     }},
    {"cos",
     Function{
         .name = "cos",
         .arg_types = {Function::ValueType::VECTOR},
         .return_type = Function::ValueType::VECTOR,
     }},
    {"cosh",
     Function{
         .name = "cosh",
         .arg_types = {Function::ValueType::VECTOR},
         .return_type = Function::ValueType::VECTOR,
     }},
    {"count_over_time",
     Function{
         .name = "count_over_time",
         .arg_types = {Function::ValueType::MATRIX},
         .return_type = Function::ValueType::VECTOR,
     }},
    {"days_in_month",
     Function{
         .name = "days_in_month",
         .arg_types = {Function::ValueType::VECTOR},
         .variadic = true,
         .return_type = Function::ValueType::VECTOR,
     }},
    {"day_of_month",
     Function{
         .name = "day_of_month",
         .arg_types = {Function::ValueType::VECTOR},
         .variadic = true,
         .return_type = Function::ValueType::VECTOR,
     }},
    {"day_of_week",
     Function{
         .name = "day_of_week",
         .arg_types = {Function::ValueType::VECTOR},
         .variadic = true,
         .return_type = Function::ValueType::VECTOR,
     }},
    {"day_of_year",
     Function{
         .name = "day_of_year",
         .arg_types = {Function::ValueType::VECTOR},
         .variadic = true,
         .return_type = Function::ValueType::VECTOR,
     }},
    {"deg",
     Function{
         .name = "deg",
         .arg_types = {Function::ValueType::VECTOR},
         .return_type = Function::ValueType::VECTOR,
     }},
    {"delta",
     Function{
         .name = "delta",
         .arg_types = {Function::ValueType::MATRIX},
         .return_type = Function::ValueType::VECTOR,
     }},
    {"deriv",
     Function{
         .name = "deriv",
         .arg_types = {Function::ValueType::MATRIX},
         .return_type = Function::ValueType::VECTOR,
     }},
    {"exp",
     Function{
         .name = "exp",
         .arg_types = {Function::ValueType::VECTOR},
         .return_type = Function::ValueType::VECTOR,
     }},
    {"floor",
     Function{
         .name = "floor",
         .arg_types = {Function::ValueType::VECTOR},
         .return_type = Function::ValueType::VECTOR,
     }},
    {"histogram_count",
     Function{
         .name = "histogram_count",
         .arg_types = {Function::ValueType::VECTOR},
         .return_type = Function::ValueType::VECTOR,
     }},
    {"histogram_sum",
     Function{
         .name = "histogram_sum",
         .arg_types = {Function::ValueType::VECTOR},
         .return_type = Function::ValueType::VECTOR,
     }},
    {"histogram_fraction",
     Function{
         .name = "histogram_fraction",
         .arg_types = {Function::ValueType::SCALAR, Function::ValueType::SCALAR, Function::ValueType::VECTOR},
         .return_type = Function::ValueType::VECTOR,
     }},
    {"histogram_quantile",
     Function{
         .name = "histogram_quantile",
         .arg_types = {Function::ValueType::SCALAR, Function::ValueType::VECTOR},
         .return_type = Function::ValueType::VECTOR,
     }},
    {"holt_winters",
     Function{
         .name = "holt_winters",
         .arg_types = {Function::ValueType::MATRIX, Function::ValueType::SCALAR, Function::ValueType::SCALAR},
         .return_type = Function::ValueType::VECTOR,
     }},
    {"hour",
     Function{
         .name = "hour",
         .arg_types = {Function::ValueType::VECTOR},
         .variadic = true,
         .return_type = Function::ValueType::VECTOR,
     }},
    {"idelta",
     Function{
         .name = "idelta",
         .arg_types = {Function::ValueType::MATRIX},
         .return_type = Function::ValueType::VECTOR,
     }},
    {"increase",
     Function{
         .name = "increase",
         .arg_types = {Function::ValueType::MATRIX},
         .return_type = Function::ValueType::VECTOR,
     }},
    {"irate",
     Function{
         .name = "irate",
         .arg_types = {Function::ValueType::MATRIX},
         .return_type = Function::ValueType::VECTOR,
     }},
    {"label_replace",
     Function{
         .name = "label_replace",
         .arg_types = {Function::ValueType::VECTOR,
                       Function::ValueType::STRING,
                       Function::ValueType::STRING,
                       Function::ValueType::STRING,
                       Function::ValueType::STRING},
         .return_type = Function::ValueType::VECTOR,
     }},
    {"label_join", Function{
       .name = "label_join",
       .arg_types = {Function::ValueType::VECTOR,
                     Function::ValueType::STRING,
                     Function::ValueType::STRING,
                     Function::ValueType::STRING},
       .variadic = true, // -1
       .return_type = Function::ValueType::VECTOR,
     }},
    {"last_over_time",
     Function{
         .name = "last_over_time",
         .arg_types = {Function::ValueType::MATRIX},
         .return_type = Function::ValueType::VECTOR,
     }},
    {"ln",
     Function{
         .name = "ln",
         .arg_types = {Function::ValueType::VECTOR},
         .return_type = Function::ValueType::VECTOR,
     }},
    {"log10",
     Function{
         .name = "log10",
         .arg_types = {Function::ValueType::VECTOR},
         .return_type = Function::ValueType::VECTOR,
     }},
    {"log2",
     Function{
         .name = "log2",
         .arg_types = {Function::ValueType::VECTOR},
         .return_type = Function::ValueType::VECTOR,
     }},
    {"max_over_time",
     Function{
         .name = "max_over_time",
         .arg_types = {Function::ValueType::MATRIX},
         .return_type = Function::ValueType::VECTOR,
     }},
    {"min_over_time",
     Function{
         .name = "min_over_time",
         .arg_types = {Function::ValueType::MATRIX},
         .return_type = Function::ValueType::VECTOR,
     }},
    {"minute",
     Function{
         .name = "minute",
         .arg_types = {Function::ValueType::VECTOR},
         .variadic = true,
         .return_type = Function::ValueType::VECTOR,
     }},
    {"month",
     Function{
         .name = "month",
         .arg_types = {Function::ValueType::VECTOR},
         .variadic = true,
         .return_type = Function::ValueType::VECTOR,
     }},
    {"pi",
     Function{
         .name = "pi",
         .arg_types = {},
         .return_type = Function::ValueType::SCALAR,
     }},
    {"predict_linear",
     Function{
         .name = "predict_linear",
         .arg_types = {Function::ValueType::MATRIX, Function::ValueType::SCALAR},
         .return_type = Function::ValueType::VECTOR,
     }},
    {"present_over_time",
     Function{
         .name = "present_over_time",
         .arg_types = {Function::ValueType::MATRIX},
         .return_type = Function::ValueType::VECTOR,
     }},
    {"quantile_over_time",
     Function{
         .name = "quantile_over_time",
         .arg_types = {Function::ValueType::SCALAR, Function::ValueType::MATRIX},
         .return_type = Function::ValueType::VECTOR,
     }},
    {"rad",
     Function{
         .name = "rad",
         .arg_types = {Function::ValueType::VECTOR},
         .return_type = Function::ValueType::VECTOR,
     }},
    {"rate",
     Function{
         .name = "rate",
         .arg_types = {Function::ValueType::MATRIX},
         .return_type = Function::ValueType::VECTOR,
     }},
    {"resets",
     Function{
         .name = "resets",
         .arg_types = {Function::ValueType::MATRIX},
         .return_type = Function::ValueType::VECTOR,
     }},
    {"round",
     Function{
         .name = "round",
         .arg_types = {Function::ValueType::VECTOR, Function::ValueType::SCALAR},
         .variadic = true,
         .return_type = Function::ValueType::VECTOR,
     }},
    {"SCALAR",
     Function{
         .name = "SCALAR",
         .arg_types = {Function::ValueType::VECTOR},
         .return_type = Function::ValueType::SCALAR,
     }},
    {"sgn",
     Function{
         .name = "sgn",
         .arg_types = {Function::ValueType::VECTOR},
         .return_type = Function::ValueType::VECTOR,
     }},
    {"sin",
     Function{
         .name = "sin",
         .arg_types = {Function::ValueType::VECTOR},
         .return_type = Function::ValueType::VECTOR,
     }},
    {"sinh",
     Function{
         .name = "sinh",
         .arg_types = {Function::ValueType::VECTOR},
         .return_type = Function::ValueType::VECTOR,
     }},
    {"sort",
     Function{
         .name = "sort",
         .arg_types = {Function::ValueType::VECTOR},
         .return_type = Function::ValueType::VECTOR,
     }},
    {"sort_desc",
     Function{
         .name = "sort_desc",
         .arg_types = {Function::ValueType::VECTOR},
         .return_type = Function::ValueType::VECTOR,
     }},
    {"sqrt",
     Function{
         .name = "sqrt",
         .arg_types = {Function::ValueType::VECTOR},
         .return_type = Function::ValueType::VECTOR,
     }},
    {"stddev_over_time",
     Function{
         .name = "stddev_over_time",
         .arg_types = {Function::ValueType::MATRIX},
         .return_type = Function::ValueType::VECTOR,
     }},
    {"stdvar_over_time",
     Function{
         .name = "stdvar_over_time",
         .arg_types = {Function::ValueType::MATRIX},
         .return_type = Function::ValueType::VECTOR,
     }},
    {"sum_over_time",
     Function{
         .name = "sum_over_time",
         .arg_types = {Function::ValueType::MATRIX},
         .return_type = Function::ValueType::VECTOR,
     }},
    {"tan",
     Function{
         .name = "tan",
         .arg_types = {Function::ValueType::VECTOR},
         .return_type = Function::ValueType::VECTOR,
     }},
    {"tanh",
     Function{
         .name = "tanh",
         .arg_types = {Function::ValueType::VECTOR},
         .return_type = Function::ValueType::VECTOR,
     }},
    {"time",
     Function{
         .name = "time",
         .arg_types = {},
         .return_type = Function::ValueType::SCALAR,
     }},
    {"timestamp",
     Function{
         .name = "timestamp",
         .arg_types = {Function::ValueType::VECTOR},
         .return_type = Function::ValueType::VECTOR,
     }},
    {"vector",
     Function{
         .name = "VECTOR",
         .arg_types = {Function::ValueType::SCALAR},
         .return_type = Function::ValueType::VECTOR,
     }},
    {"year",
     Function{
         .name = "year",
         .arg_types = {Function::ValueType::VECTOR},
         .variadic = true,
         .return_type = Function::ValueType::VECTOR,
     }},
};

} // namespace promql::functions
