#pragma once

#include "to_file_strategy.h"

class cplusplus_template final : public to_file_strategy
{
public:
    cplusplus_template() = default;
    ~cplusplus_template() override = default;

    cplusplus_template(const cplusplus_template &rhs) = default;
    cplusplus_template(cplusplus_template &&rhs) noexcept;
    cplusplus_template & operator=(const cplusplus_template &rhs);
    cplusplus_template & operator=(cplusplus_template &&rhs) noexcept;
protected:
    auto to_file(class_prototype *p_class) -> file override;
    auto to_file(function_prototype *p_function) -> file override;
    
    auto get_class_string(
        const std::string& class_name,
        const std::string& parent_name,
        const std::string& variables,
        const std::string& methods
    ) -> std::string override;
    auto get_variable_strings(variable_iter begin, const variable_iter& end) -> std::string override;
    auto get_parameter_strings(variable_iter begin, const variable_iter& end) -> std::string override;
    auto get_method_strings(method_iter begin, const method_iter& end) -> std::string override;
};
