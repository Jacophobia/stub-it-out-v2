#pragma once

#include "../Project/method.h"
#include "../Project/class.h"
#include "../Project/function.h"

#include <string>

class to_file_strategy
{
public:
    to_file_strategy() = default;
    virtual ~to_file_strategy() = default;
    to_file_strategy(const to_file_strategy &rhs) = default;
    to_file_strategy(to_file_strategy &&rhs) noexcept = default;
    to_file_strategy & operator=(const to_file_strategy &rhs) = default;
    to_file_strategy & operator=(to_file_strategy &&rhs) noexcept = default;

    typedef std::pair<std::string, std::string> file; // filepath : file_content
    virtual auto to_file(class_prototype* p_class) -> file = 0;
    virtual auto to_file(method_prototype* p_method) -> file = 0;
    virtual auto to_file(function_prototype* p_function) -> file = 0;
};
