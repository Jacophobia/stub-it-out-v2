#pragma once

#include <memory>
#include <string>

#define _CRT_SECURE_NO_WARNINGS
#include "TOML/tomlcpp.hpp"
#undef _CRT_SECURE_NO_WARNINGS

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
    [[nodiscard]] auto get_table() const -> std::shared_ptr<toml::Table>;

    typedef std::shared_ptr<toml::Table> toml_table;
    
    auto convert_to_project(const toml_table& table) const -> project*;

    auto add_methods(const toml_table& table, project::builder&) const -> void;

    auto add_classes(const toml_table& table, project::builder&) const -> void;

    auto add_functions(const toml_table& table, project::builder&) const -> void;
    
    std::string path_;
    settings settings_;
};
