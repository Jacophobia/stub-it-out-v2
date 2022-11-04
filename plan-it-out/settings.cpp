#include "settings.h"

const auto invalid_argument_key = "Invalid Argument Key";
const auto invalid_argument_value = "Invalid Argument Value";

auto string_to_setting_key(const std::string& str) -> setting_key
{
    if (str == "-l" || str == "--language")
        return language;

    throw std::exception(invalid_argument_key);
}

auto string_to_setting_value(const std::string &str) -> setting_value
{
    if (str == "python3")
        return python3;
    if (str == "cplusplus")
        return cplusplus;
    if (str == "java")
        return java;
    if (str == "csharp")
        return csharp;
    if (str == "javascript")
        return javascript;
    if (str == "typescript")
        return typescript;

    throw std::exception(invalid_argument_value);
}
