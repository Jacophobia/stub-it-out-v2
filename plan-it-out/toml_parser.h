#pragma once

#include <string>

#include "settings.h"
#include "Project/project.h"

class toml_parser
{
public:
    // default constructor
    toml_parser() = delete;
    
    // with file path
    toml_parser(std::string path, const settings& settings);

    // destructor
    ~toml_parser();

    // copy / move
    toml_parser(const toml_parser& rhs);
    toml_parser(toml_parser&& rhs) noexcept;
    auto operator=(const toml_parser& rhs) -> toml_parser&;
    auto operator=(toml_parser&& rhs) noexcept -> toml_parser&;

    // parse from file
    [[nodiscard]] auto parse() const -> project*;
private:
    std::string path_;
    settings settings_;
};
