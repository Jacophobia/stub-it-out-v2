#pragma once

#include <vector>

#include "class.h"
#include "function.h"
#include "method.h"

class project
{
public:
    // default constructor
    project() = default;
    
    // destructor
    ~project();

    // copy / move
    project(const project& rhs);
    project(project&& rhs) noexcept;
    auto operator=(const project& rhs) -> project&;
    auto operator=(project&& rhs) noexcept -> project&;

    // add prototypes
    auto add_class(const class_prototype& p_class) -> void;
    auto add_method(const method_prototype& p_method) -> void;
    auto add_function(const function_prototype& p_function) -> void;

    class builder;
private:
    std::vector<function_prototype> functions_;
    std::vector<method_prototype> methods_;
    std::vector<class_prototype> classes_;
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
