#include "display.h"

#include <iostream>

auto display::help() -> void
{
    message("Hello and welcome to Stub it Out!");
    message(
        "Please enter a toml file location as the first argument\n"
        "followed by the settings you would like the program to follow.\n"
        "** at the moment the only supported language is python so use\n"
        "the --language flag followed by python3\n"
        "Example:\n"
        "\tstub-it-out example.toml --language python3\n"
    );
}

auto display::version() -> void
{
    message("v0.0.0");
}

auto display::message(const std::string& message) -> void
{
    std::cout << message << std::endl;
}

auto display::error(const std::string& message) -> void
{
    std::cerr << message << std::endl;
}

auto display::error(const std::exception& exception) -> void
{
    error(exception.what());
}

auto println(const std::string& message) -> void
{
    display::message(message);
}
