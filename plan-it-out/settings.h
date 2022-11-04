﻿#pragma once

#include <string>

/*
 Setting Keys
  Keys representing each of the possible settings entered via command
  line.
 */
enum setting_key {
    language
};

/*
 Language
  The programming setting_value that the program will be generated in.
 */
enum setting_value
{
    // languages
    python3, cplusplus, java, csharp, javascript, typescript,
};

/*
 Settings
  The settings that each layer in the program will follow.
 */
struct settings
{
    setting_value language;
};

auto string_to_setting_key(const std::string& str) -> setting_key;

auto string_to_setting_value(const std::string& str) -> setting_value;