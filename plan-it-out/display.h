#pragma once

#include <string>

namespace display
{
    auto help() -> void;
    auto version() -> void;
    auto message(const std::string& message) -> void;
    auto error(const std::string& message) -> void;
    auto error(const std::exception& exception) -> void;
}

auto println(const std::string& message) -> void;
