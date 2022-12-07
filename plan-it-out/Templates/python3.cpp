#include "python3.h"

#include <cassert>

python3_template::python3_template(python3_template &&rhs) noexcept
    : to_file_strategy(std::move(rhs)) {}

python3_template & python3_template::operator=(const python3_template &rhs) {
    if (this == &rhs)
        return *this;
    to_file_strategy::operator =(rhs);
    return *this;
}

python3_template & python3_template::operator=(python3_template &&rhs) noexcept {
    if (this == &rhs)
        return *this;
    to_file_strategy::operator =(std::move(rhs));
    return *this;
}

auto condense_string_list(const std::vector<std::string>& list) -> std::string
{
    std::string string;
    
    for (auto & val : list)
    {
        string.append(val); 
    }
    
    return string;
}

auto get_class_string(
    const std::string& class_name,
    const std::string& parent_name,
    const std::string& variables,
    const std::string& methods
) -> std::string
{
    std::string class_string;
    
    class_string.append(
        "class " + class_name + "(" + parent_name + "):\n"
        "    def __init__(self):\n" + 
        variables +
        "        pass\n\n" +
        methods
    );

    return class_string;
}

typedef std::_Tree_iterator<std::_Tree_val<std::_Tree_simple_types<std::pair<const std::string, std::string>>>> variable_iter;

auto get_variable_strings(variable_iter begin, const variable_iter& end) -> std::string
{
    std::string variable_strings;
    for (; begin != end; ++begin)
    {
        variable_strings.append(
            "        self." + begin->first + " = " + begin->second + "()\n"
        );
    }

    return variable_strings;
}

auto get_parameter_strings(variable_iter begin, const variable_iter& end, bool function = false) -> std::string
{
    std::string parameter_string;
    
    for (bool first = true; begin != end; ++begin)
    {
        auto parameter_name = begin->first;
        auto parameter_type = begin->second;
        if (function && first)
            parameter_string.append(parameter_name + ": " + parameter_type);
        else
            parameter_string.append(", " + parameter_name + ": " + parameter_type);
        first = false;
    }

    return parameter_string;
}

typedef std::vector<method_prototype*>::iterator method_iter;

auto get_method_strings(method_iter begin, const method_iter& end) -> std::string
{
    std::string method_strings;
    for (; begin != end; ++begin)
    {
        auto [param_begin, param_end] = (*begin)->get_parameters_iter();
        auto parameters = get_parameter_strings(param_begin, param_end);
        auto return_type = (*begin)->get_return_type();
        
        if (return_type == "void")
            return_type = "None";
        
        method_strings.append(
            "    def " + (*begin)->get_name() + "(self" + parameters + ") -> " + return_type + ":\n"
            "        pass\n\n"
        );
    }
    return method_strings;
}

auto python3_template::to_file(class_prototype *p_class) -> file
{
    const auto class_name = p_class->get_name();
    auto [has_parent, parent_name] = p_class->get_parent_name();
    auto [variable_begin, variable_end] = p_class->get_variable_iter();
    const auto variable_strings = get_variable_strings(variable_begin, variable_end);
    auto [method_begin, method_end] = p_class->get_method_iter();
    const auto method_strings = get_method_strings(method_begin, method_end);
    auto class_string = get_class_string(class_name, has_parent ? parent_name : "", variable_strings, method_strings);

    return { class_name + ".py", class_string };
}

auto python3_template::to_file(function_prototype *p_function) -> file
{
    std::string function_string;
    
    auto [param_begin, param_end] = p_function->get_parameters_iter();
    const auto parameters = get_parameter_strings(param_begin, param_end, true);
    auto return_type = p_function->get_return_type();
        
    if (return_type == "void")
        return_type = "None";
        
    function_string.append(
        "    def " + p_function->get_name() + "(" + parameters + ") -> " + return_type + ":\n"
        "        pass\n\n"
    );
    
    return { "main.py", function_string };
}


