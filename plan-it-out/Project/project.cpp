#include "project.h"

#include <cassert>

project::~project()
{
    assert(false); // not yet implemented
}

project::project(const project& rhs)
{
    assert(false); // not yet implemented
}

project::project(project&& rhs) noexcept
{
    assert(false); // not yet implemented
}

auto project::operator=(const project& rhs) -> project&
{
    assert(false); // not yet implemented
    return *this;
}

auto project::operator=(project&& rhs) noexcept -> project&
{
    assert(false); // not yet implemented
    return *this;
}

auto project::add_class(class_prototype* p_class) -> void
{
    assert(false); // not yet implemented
}

auto project::add_method(method_prototype* p_method) -> void
{
    assert(false); // not yet implemented
}

auto project::add_function(function_prototype* p_function) -> void
{
    assert(false); // not yet implemented
}
