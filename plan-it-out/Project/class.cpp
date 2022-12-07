#include "class.h"

#include <algorithm>
#include <xkeycheck.h>

#include "method.h"

class_prototype::class_prototype(std::string name, std::string parent_name) :
    name_(std::move(name)), parent_name_(std::move(parent_name)),
    parent_(nullptr) {}

auto class_prototype::set_parent(class_prototype *parent) -> void
{
    parent_ = parent;
}

auto class_prototype::add_child_name(const std::string &child_name) -> void
{
    children_names_.emplace_back(child_name);
}

auto class_prototype::add_child(class_prototype *child) -> void
{
    children_.emplace_back(child);
}

auto class_prototype::add_variable(const std::string &name, const std::string &data_type) -> void
{
    variables_.emplace(name, data_type);
}

auto class_prototype::add_method_name(const std::string &method_name) -> void
{
    method_names_.emplace_back(method_name);
}

auto class_prototype::add_method(method_prototype *method) -> void
{
    methods_.emplace_back(method);
}

auto class_prototype::get_name() const -> std::string
{
    return name_;
}

auto class_prototype::get_parent_name() const -> std::pair<bool, std::string>
{
    return { !parent_name_.empty(), parent_name_ };
}

auto class_prototype::get_child_names() const -> std::vector<std::string>
{
    return children_names_;
}

auto class_prototype::get_method(const std::string &name) const -> std::pair<bool, method_prototype*>
{
    for (auto& method : methods_)
    {
        if (method->get_name() == name)
            return { true, method };
    }
    
    return { false, nullptr };
}

auto class_prototype::get_variable_iter() -> std::pair<variable_iter, variable_iter>
{
    return { variables_.begin(), variables_.end() };
}

auto class_prototype::get_method_iter() -> std::pair<method_iter, method_iter>
{
    return { methods_.begin(), methods_.end() };
}

auto class_prototype::contains_method(const std::string &method_name) -> bool
{
    return std::ranges::any_of(
        method_names_.begin(),
        method_names_.end(),
        [method_name](auto curr){ return curr == method_name; }
    );
}

auto class_prototype::valid_children() -> bool
{
    return children_names_.size() == children_.size();
}

