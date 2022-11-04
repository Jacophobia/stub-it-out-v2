#include "toml_parser.h"

#include <fstream>
#include <cassert>

const auto invalid_filepath = "Invalid Filepath";

auto file_exists(const std::ifstream& f) -> bool
{
    return f.good();
}

toml_parser::toml_parser(std::string path, const settings& settings) :
    path_(std::move(path)), settings_(settings)
{
    assert(false); // not yet implemented
}

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
    // confirm that the first argument provided is a valid filepath
    
    // if it is not valid, throw an error

    // get the provided file
    assert(false); // not yet implemented
    return new project();
}
