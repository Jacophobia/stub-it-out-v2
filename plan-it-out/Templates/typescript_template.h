#pragma once

#include "to_file_strategy.h"

class typescript_template : public to_file_strategy
{
protected:
    auto to_file(class_prototype *p_class) -> file override;
    auto to_file(function_prototype *p_function) -> file override;
    auto get_class_string(const std::string &class_name, const std::string &parent_name,
        const std::string &variables, const std::string &methods) -> std::string override;
    auto get_variable_strings(variable_iter begin, const variable_iter &end) -> std::string override;
    auto get_parameter_strings(variable_iter begin, const variable_iter &end) -> std::string override;
    auto get_method_strings(method_iter begin, const method_iter &end) -> std::string override;
};
