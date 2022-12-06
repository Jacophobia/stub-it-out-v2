#include "arg_parser.h"

#include <cassert>

const auto invalid_arguments_message = "Invalid Arguments";
const auto not_enough_arguments_message = "Invalid Arguments: Too few arguments";
const auto no_file_path_given = "Invalid Arguments: No filepath was given";
const auto invalid_language = "Invalid Argument: The specified setting_value is not supported";
constexpr int minimum_args = 2;
constexpr int filepath_arg = 1;
constexpr int arg_pair_size = 2;



/*
 Command Line Argument Constructor
  Creates pairings of all command line arguments and saves them to
  args_ to be consumed later by arg_parser's other methods.
 */
arg_parser::arg_parser(const int argc, char** argv)
{
    // need at least one argument
    if (argc < minimum_args)
        throw std::exception(not_enough_arguments_message);

    // skip first arg since it is just the file path
    first_arg_ = argv[filepath_arg];

    // check to see if the pairing is off.
    if (!(argc % arg_pair_size + filepath_arg))
        throw std::exception(invalid_arguments_message);

    // store the other args
    for (int i = minimum_args; i < argc; i += arg_pair_size)
    {
        add_kv_pair(argv[i], argv[i + 1]);
    }
}

arg_parser::arg_parser(const arg_parser& rhs)
{
    assert(false); // not yet implemented
}

arg_parser::arg_parser(arg_parser&& rhs) noexcept
{
    assert(false); // not yet implemented
}

auto arg_parser::operator=(const arg_parser& rhs) -> arg_parser&
{
    assert(false); // not yet implemented
    
    return *this;
}

auto arg_parser::operator=(arg_parser&& rhs) noexcept -> arg_parser&
{
    assert(false); // not yet implemented

    return *this;
}

auto arg_parser::get_settings() const -> settings
{
    assert(!is_help_request());
    assert(!is_version_request());
    assert(!first_arg_.empty());
    
    return { args_.at(language) };
}

auto arg_parser::get_filepath() const -> std::string
{
    assert(!is_help_request());
    assert(!is_version_request());
    
    if (first_arg_.empty())
        throw std::exception(no_file_path_given);
    
    return first_arg_;
}

auto arg_parser::is_version_request() const -> bool
{
    return first_arg_ == "-v" || first_arg_ == "--version";
}

auto arg_parser::is_help_request() const -> bool
{
    return first_arg_ == "-h" || first_arg_ == "--help";
}

auto arg_parser::add_kv_pair(const std::string &k, const std::string &v) -> void
{
    args_.emplace(string_to_setting_key(k), string_to_setting_value(v));
}
