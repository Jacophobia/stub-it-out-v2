#include "project.h"

#include <cassert>

const auto class_doesnt_exist = "Improper Link: Class not found";
const auto cannot_end_with_semicolon = "Syntax Error: Cannot end a callee name with a colon";   

project::project(const project& rhs) :
    functions_(rhs.functions_), methods_(rhs.methods_),
    classes_(rhs.classes_) {}

project::project(project&& rhs) noexcept :
    functions_(std::move(rhs.functions_)), methods_(std::move(rhs.methods_)),
    classes_(std::move(rhs.classes_)) {}

auto project::operator=(const project& rhs) -> project&
{
    if (this == &rhs)
        return *this;
    
    functions_ = rhs.functions_;
    methods_ = rhs.methods_;
    classes_ = rhs.classes_;
    
    return *this;
}

auto project::operator=(project&& rhs) noexcept -> project&
{
    if (this == &rhs)
        return *this;
    
    functions_ = std::move(rhs.functions_);
    methods_ = std::move(rhs.methods_);
    classes_ = std::move(rhs.classes_);
    
    return *this;
}

auto project::add_class(const class_prototype& p_class) -> void
{
    classes_.emplace(p_class.get_name(), p_class);
}

auto project::add_method(const method_prototype& p_method) -> void
{
    methods_.emplace_back(p_method);
}

auto project::add_function(const function_prototype& p_function) -> void
{
    functions_.emplace(p_function.get_name(), p_function);
}

auto project::get_class_iter() -> std::pair<class_iter, class_iter>
{
    return { classes_.begin(), classes_.end() };
}

auto project::get_function_iter() -> std::pair<function_iter, function_iter>
{
    return { functions_.begin(), functions_.end() };
}

auto project::get_method_iter() -> std::pair<method_iter, method_iter>
{
    return { methods_.begin(), methods_.end() };
}

auto project::get_class(const std::string &name) -> class_prototype *
{
    if (!classes_.contains(name))
    {
        throw std::exception(class_doesnt_exist);
    }
    return &classes_.at(name);
}

auto project::get_function(const std::string &name) -> std::pair<bool, function_prototype*>
{
    if (
        const auto break_character_index = name.find(':');
        std::string::npos != break_character_index
    )
    {
        if (break_character_index >= name.size() - 1)
            throw std::exception(cannot_end_with_semicolon);

        const auto class_name = name.substr(0, break_character_index);
        const auto method_name = name.c_str() + break_character_index + 1;
        return get_method(class_name, method_name);
    }
    
    return { functions_.contains(name), &functions_.at(name) };
}

auto project::get_method(const std::string& class_name, const std::string& method_name) -> std::pair<bool, method_prototype*>
{
    auto [has_method, method] = classes_.at(class_name).get_method(method_name);
    return { has_method, method };
}

project::builder::builder(const builder &rhs) : project_(rhs.project_) {}

project::builder::builder(builder &&rhs) noexcept :
    project_(std::move(rhs.project_)) {}

auto project::builder::operator=(const builder &rhs) -> builder &
{
    if (this == &rhs)
        return *this;
    
    project_ = rhs.project_;
    return *this;
}

auto project::builder::operator=(builder &&rhs) noexcept -> builder &
{
    if (this == &rhs)
        return *this;
    
    project_ = std::move(rhs.project_);
    return *this;
}

auto project::builder::add_class(const class_prototype& p_class) -> builder &
{
    project_.add_class(p_class);
    return *this;
}

auto project::builder::add_method(const method_prototype& p_method) -> builder &
{
    project_.add_method(p_method);
    return *this;
}

auto project::builder::add_function(
    const function_prototype& p_function
) -> builder &
{
    project_.add_function(p_function);
    return *this;
}

auto project::builder::build() const -> project*
{
    return new project(project_);
}

