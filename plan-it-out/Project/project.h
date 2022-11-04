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
    auto add_class(class_prototype* p_class) -> void;
    auto add_method(method_prototype* p_method) -> void;
    auto add_function(function_prototype* p_function) -> void;
private:
    std::vector<function_prototype> functions_;
    std::vector<method_prototype> methods_;
    std::vector<class_prototype> classes_;
};
