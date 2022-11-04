#include "toml_parser.h"

#include <cassert>

const auto invalid_filepath = "Invalid Filepath: File does not exist";

toml_parser::toml_parser(std::string path, const settings& settings) :
    path_(std::move(path)), settings_(settings) {}

toml_parser::~toml_parser()
{
    assert(false); // not yet implemented
}

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
auto toml_parser::convert_to_project(const toml_table &table) const -> project *
{
    project::builder builder;

    add_methods(table, builder);
    add_classes(table, builder);
    add_functions(table, builder);

    return builder.build();
}

auto toml_parser::add_methods(const toml_table &table, project::builder &) const -> void
{
    auto methods = table->getArray("methods");
    assert(false); // not yet implemented
}

auto toml_parser::add_classes(const toml_table &table, project::builder &) const -> void
{
    auto classes = table->getArray("classes");
    assert(false); // not yet implemented
}

auto toml_parser::add_functions(const toml_table &table, project::builder &) const -> void
{
    auto functions = table->getArray("functions");
    assert(false); // not yet implemented
}
