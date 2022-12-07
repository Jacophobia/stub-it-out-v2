#pragma once
#include "to_file_strategy.h"

class python3_template final : public to_file_strategy
{
public:
    python3_template() = default;
    ~python3_template() = default;

    python3_template(const python3_template &rhs) = default;
    python3_template(python3_template &&rhs) noexcept;
    python3_template & operator=(const python3_template &rhs);
    python3_template & operator=(python3_template &&rhs) noexcept;
protected:
    auto to_file(class_prototype *p_class) -> file override;
    auto to_file(function_prototype *p_function) -> file override;
};
