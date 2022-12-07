#pragma once

#include <map>
#include <string>

class file_writer
{
public:
    auto write(const std::map<std::string, std::string>& files) -> void;
};
