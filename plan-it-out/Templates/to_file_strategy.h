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
    typedef std::_Tree_iterator<std::_Tree_val<std::_Tree_simple_types<std::pair<const std::string, std::string>>>> variable_iter;
    typedef std::vector<method_prototype*>::iterator method_iter;
    typedef std::pair<std::string, std::string> file; // filepath : file_content
    
    virtual auto to_file(class_prototype* p_class) -> file = 0;
    virtual auto to_file(function_prototype* p_function) -> file = 0;
    
    virtual auto get_class_string(
        const std::string& class_name,
        const std::string& parent_name,
        const std::string& variables,
        const std::string& methods
    ) -> std::string = 0;
    virtual auto get_variable_strings(variable_iter begin, const variable_iter& end) -> std::string = 0;
    virtual auto get_parameter_strings(variable_iter begin, const variable_iter& end) -> std::string = 0;
    virtual auto get_method_strings(method_iter begin, const method_iter& end) -> std::string = 0;
};
