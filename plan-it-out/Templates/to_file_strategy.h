#pragma once

#include "../Project/class.h"
#include "../Project/function.h"
#include "../Project/project.h"

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

    auto to_files(project* project) -> std::map<std::string, std::string>;

protected:
    typedef std::pair<std::string, std::string> file; // filepath : file_content
    virtual auto to_file(class_prototype* p_class) -> file = 0;
    virtual auto to_file(function_prototype* p_function) -> file = 0;
};
