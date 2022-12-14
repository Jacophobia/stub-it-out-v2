#include "typescript_template.h"


auto typescript_template::get_class_string(
    const std::string& class_name,
    const std::string& parent_name,
    const std::string& variables,
    const std::string& methods
) -> std::string
{
    std::string class_string;

    const std::string super_class = parent_name.empty() ?
        " {\n" : " extends " + parent_name + " {\n";
    
    class_string.append(
        "class " + class_name + super_class +
        variables + "\n" +
        methods +
        "}\n"
    );

    return class_string;
}

auto typescript_template::get_variable_strings(variable_iter begin, const variable_iter& end) -> std::string
{
    std::string variable_strings;
    for (; begin != end; ++begin)
    {
        variable_strings.append(
            "    private " + begin->first + ": " + begin->second + "\n"
        );
    }

    return variable_strings;
}

auto typescript_template::get_parameter_strings(variable_iter begin, const variable_iter& end) -> std::string
{
    std::string parameter_string;
    
    for (bool first = true; begin != end; ++begin)
    {
        auto parameter_name = begin->first;
        auto parameter_type = begin->second;
        if (first)
            parameter_string.append(parameter_name + ": " + parameter_type);
        else
            parameter_string.append(", " + parameter_name + ": " + parameter_type);
        first = false;
    }

    return parameter_string;
}

auto typescript_template::get_method_strings(method_iter begin, const method_iter& end) -> std::string
{
    std::string method_strings;
    for (; begin != end; ++begin)
    {
        auto [param_begin, param_end] = (*begin)->get_parameters_iter();
        auto parameters = get_parameter_strings(param_begin, param_end);
        auto return_type = (*begin)->get_return_type();

        std::string return_statement = "        return new " + return_type + "()\n";

        if (return_type == "void")
        {
            return_statement = "";
        }
        
        method_strings.append(
            "    public " + (*begin)->get_name() + "(" + parameters + "): " + return_type + " {\n" +
            return_statement +
            "    }\n"
        );
    }
    return method_strings;
}

auto typescript_template::to_file(class_prototype *p_class) -> file
{
    const auto class_name = p_class->get_name();
    auto [has_parent, parent_name] = p_class->get_parent_name();
    auto [variable_begin, variable_end] = p_class->get_variable_iter();
    const auto variable_strings = get_variable_strings(variable_begin, variable_end);
    auto [method_begin, method_end] = p_class->get_method_iter();
    const auto method_strings = get_method_strings(method_begin, method_end);
    auto class_string = get_class_string(class_name, has_parent ? parent_name : "", variable_strings, method_strings);

    return { class_name + ".ts", class_string };
}

auto typescript_template::to_file(function_prototype *p_function) -> file
{
    std::string function_string;
    
    auto [param_begin, param_end] = p_function->get_parameters_iter();
    const auto parameters = get_parameter_strings(param_begin, param_end);
    const auto return_type = p_function->get_return_type();

    std::string return_statement = "    return new " + return_type + "()\n";

    if (return_type == "void")
    {
        return_statement = "";
    }
        
    function_string.append(
        "const " + p_function->get_name() + " = (" + parameters + ") => {\n" +
        return_statement +
        "}\n\n"
    );
    
    return { "functions.ts", function_string };
}