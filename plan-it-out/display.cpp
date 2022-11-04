#include "display.h"

#include <iostream>
#include <cassert>


auto display::help() -> void
{
    assert(false); // not yet implemented
}

auto display::version() -> void
{
    assert(false); // not yet implemented
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
