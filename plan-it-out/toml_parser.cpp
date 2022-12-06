#include "toml_parser.h"

#include <cassert>
#include "Project/method.h"

const auto invalid_filepath = "Invalid Filepath: File does not exist";

auto get_toml_array_size(const std::unique_ptr<toml::Array>& array) -> int
{
    if (array == nullptr)
    {
        return 0;
    }
    return array->size();
}

auto get_toml_table_keys(const std::unique_ptr<toml::Table>& table) -> std::vector<std::string>
{
    if (table == nullptr)
    {
        return {};
    }
    return table->keys();
}

toml_parser::toml_parser(std::string path, const settings& settings) :
    path_(std::move(path)), settings_(settings) {}

toml_parser::toml_parser(const toml_parser& rhs)
{
    assert(false); // not yet implemented
}

toml_parser::toml_parser(toml_parser&& rhs) noexcept
{
    assert(false); // not yet implemented
}

auto toml_parser::operator=(const toml_parser& rhs) -> toml_parser&
{
    assert(false); // not yet implemented
    return *this;
}

auto toml_parser::operator=(toml_parser&& rhs) noexcept -> toml_parser&
{
    assert(false); // not yet implemented
    return *this;
}

auto toml_parser::parse() const -> project*
{
    // get the provided file
    const auto table = get_table();
    
    // convert file to a project object
    return convert_to_project(table);
}

auto toml_parser::get_table() const -> std::shared_ptr<toml::Table>
{
    // confirm that the first argument provided is a valid filepath
    auto [table, error_msg] = toml::parseFile(path_);
    
    // if it is not valid, throw an error
    if (!table) {
        throw std::exception(invalid_filepath);
    }

    return table;
}
auto toml_parser::convert_to_project(const toml_table &table) -> project *
{
    project::builder builder;

    add_methods(table, builder);
    add_classes(table, builder);
    add_functions(table, builder);

    return builder.build();
}

typedef std::unique_ptr<toml::Table> unique_table;
auto create_method(const unique_table& method) -> std::pair<bool, method_prototype>
{
    const auto [has_name, name] = method->getString("name");
    const auto [has_class_name, class_name] = method->getString("class");
    const auto [has_returns, returns] = method->getString("returns");

    if (!has_name || !has_class_name)
        return { false, method_prototype() };
        
    method_prototype method_prototype(
        name, class_name, has_returns ? returns : std::string()
    );

    return { true, method_prototype };
}

auto add_method(const unique_table& method, project::builder& builder) -> void
{
    auto [success, method_prototype] = create_method(method);

    if (!success)
        return;
    
    for (
        const auto parameters = method->getTable("parameters");
        const auto & param_name : get_toml_table_keys(parameters)
    )
    {
        if (
            const auto [has_param_type, param_type] = parameters->getString(param_name);
            has_param_type
        )
        {
            method_prototype.add_parameter(param_name, param_type);
        }
    }
    
    const auto calls = method->getArray("calls");
    for (int i = 0; i < get_toml_array_size(calls); i++)
    {
        if (const auto [had_call, call] = calls->getString(i); had_call)
        {
            method_prototype.add_function_call_name(call);
        }
    }

    builder.add_method(method_prototype);
}

auto toml_parser::add_methods(const toml_table& table, project::builder& builder) -> void
{
    const auto methods = table->getArray("methods");
    for (int i = 0; i < get_toml_array_size(methods); i++)
    {
        const auto method = methods->getTable(i);
        add_method(method, builder);
    }
}

auto create_class(const unique_table& class_table) -> std::pair<bool, class_prototype>
{
    // extract values
    const auto [has_name, name] = class_table->getString("name");
    const auto [has_parent, parent] = class_table->getString("parent");
    
    // validate that we have the essentials
    if (!has_name)
        return { false, class_prototype() };

    // construct object
    class_prototype class_prototype(name, has_parent ? parent : std::string());

    // return results
    return { true, class_prototype };
}

auto add_class(const unique_table& class_table, project::builder& builder) -> void
{
    
    auto [success, class_prototype] = create_class(class_table);
    
    if (!success)
        return;
    
    for (
        const auto variables = class_table->getTable("variables");
        const auto & variable_name : get_toml_table_keys(variables)
    )
    {
        if (
            const auto [has_variable_type, variable_type] = variables->getString(variable_name);
            has_variable_type
        )
        {
            class_prototype.add_variable(variable_name, variable_type);
        }
    }
    
    const auto children = class_table->getArray("children");
    for (int i = 0; i < get_toml_array_size(children); i++)
    {
        if (const auto [has_child, child] = children->getString(i); has_child)
        {
            class_prototype.add_child_name(child);
        }
    }

    const auto methods = class_table->getArray("methods");
    for (int i = 0; i < get_toml_array_size(methods); i++)
    {
        if (const auto [has_method, method] = methods->getString(i); has_method)
        {
            class_prototype.add_method_name(method);
        }
    }

    builder.add_class(class_prototype);
}

auto toml_parser::add_classes(const toml_table &table, project::builder & builder) -> void
{
    const auto classes = table->getArray("classes");
    for (int i = 0; i < get_toml_array_size(classes); i++)
    {
        const auto class_table = classes->getTable(i);
        add_class(class_table, builder);
    }
}

auto create_function(const unique_table& function_table) -> std::pair<bool, function_prototype>
{
    const auto [has_name, name] = function_table->getString("name");
    const auto [has_returns, returns] = function_table->getString("returns");

    if (!has_name)
        return { false, function_prototype() };

    function_prototype function(name, has_returns ? returns : std::string());

    return { true, function };
}

auto add_function(const unique_table& function_table, project::builder& builder) -> void
{
    auto [success, function] = create_function(function_table);

    if (!success)
        return;
    
    for (
        const auto parameters = function_table->getTable("parameters");
        const auto & parameter_name : get_toml_table_keys(parameters)
    )
    {
        if (
            const auto [has_parameter_type, parameter_type] = parameters->getString(parameter_name);
            has_parameter_type
        )
        {
            function.add_parameter(parameter_name, parameter_type);
        }
    }
    
    const auto calls = function_table->getArray("calls");
    for (int i = 0; i < get_toml_array_size(calls); i++)
    {
        if (
            const auto [has_call_name, call_name] = calls->getString(i);
            has_call_name
        )
        {
            function.add_function_call_name(call_name);
        }
    }

    builder.add_function(function);
}

auto toml_parser::add_functions(const toml_table &table, project::builder & builder) -> void
{
    const auto functions = table->getArray("functions");
    for (int i = 0; i < get_toml_array_size(functions); i++)
    {
        const auto function_table = functions->getTable(i);
        add_function(function_table, builder);
    }
}
