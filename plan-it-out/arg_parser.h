#pragma once

#include <map>
#include <string>

#include "settings.h"

/*
 Command Line Interface Parser
  Parses command line arguments and returns relevant information.
  Supports:
    --help
    --version
    <path> -l <setting_value> -u <bool>
    <path> --setting_value <setting_value> --unit-tests <bool>
 */
class arg_parser
{
public:
    // default constructor
    arg_parser() = delete;

    // destructor
    ~arg_parser();

    // with command line arguments
    arg_parser(int argc, char **argv);

    // copy / move
    arg_parser(const arg_parser& rhs);
    arg_parser(arg_parser&& rhs) noexcept;
    auto operator=(const arg_parser& rhs) -> arg_parser&;
    auto operator=(arg_parser&& rhs) noexcept -> arg_parser&;

    // parse operations
    [[nodiscard]] auto get_settings() const -> settings;

    // get file handle
    [[nodiscard]] auto get_filepath() const -> std::string;

    // is information request?
    [[nodiscard]] auto is_version_request() const -> bool;
    [[nodiscard]] auto is_help_request() const -> bool;
private:
    auto add_kv_pair(const std::string& k, const std::string& v) -> void;
    
    std::map<setting_key, setting_value> args_;
    std::string first_arg_;
};
