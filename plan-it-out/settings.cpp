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
    if (str == "python3" || str == "py")
        return python3;
    if (str == "cplusplus" || str == "cpp")
        return cplusplus;
    if (str == "java")
        return java;
    if (str == "csharp" || str == "cs")
        return csharp;
    if (str == "javascript" || str == "js")
        return javascript;
    if (str == "typescript" || str == "ts")
        return typescript;

    throw std::exception(invalid_argument_value);
}
