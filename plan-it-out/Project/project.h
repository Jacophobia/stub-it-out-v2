#pragma once

#include <map>
#include <string>

#include "class.h"
#include "function.h"
#include "method.h"

class project
{
public:
    // default constructor
    project() = default;
    
    // destructor
    ~project() = default;

    // copy / move
    project(const project& rhs);
    project(project&& rhs) noexcept;
    auto operator=(const project& rhs) -> project&;
    auto operator=(project&& rhs) noexcept -> project&;

    // add prototypes
    auto add_class(const class_prototype& p_class) -> void;
    auto add_method(const method_prototype& p_method) -> void;
    auto add_function(const function_prototype& p_function) -> void;

    // map iterator type definitions (for readability)
    typedef std::_Tree_iterator<std::_Tree_val<std::_Tree_simple_types<std::pair<const std::string, class_prototype>>>> class_iter;
    typedef std::_Tree_iterator<std::_Tree_val<std::_Tree_simple_types<std::pair<const std::string, function_prototype>>>> function_iter;
    typedef std::vector<method_prototype>::iterator method_iter;

    // getters
    auto get_class_iter() -> std::pair<class_iter, class_iter>;
    auto get_function_iter() -> std::pair<function_iter, function_iter>;
    auto get_method_iter() -> std::pair<method_iter, method_iter>;

    auto get_class(const std::string& name) -> class_prototype*;
    auto get_function(const std::string& name) -> std::pair<bool, function_prototype*>;

    class builder;
private:
    auto get_method(const std::string& class_name, const std::string& method_name) -> std::pair<bool, method_prototype*>;
    
    std::map<std::string, function_prototype> functions_;
    std::vector<method_prototype> methods_;
    std::map<std::string, class_prototype> classes_;
};

class project::builder
{
public:
    // default constructor
    builder() = default;
    
    // destructor
    ~builder() = default;

    // copy / move
    builder(const builder& rhs);
    builder(builder&& rhs) noexcept;
    auto operator=(const builder& rhs) -> builder&;
    auto operator=(builder&& rhs) noexcept -> builder&;

    // construct project
    auto add_class(const class_prototype& p_class) -> builder&;
    auto add_method(const method_prototype& p_method) -> builder&;
    auto add_function(const function_prototype& p_function) -> builder&;

    // build
    [[nodiscard]] auto build() const -> project*;
private:
    project project_;
};
