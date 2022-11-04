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

auto project::add_class(const class_prototype& p_class) -> void
{
    assert(false); // not yet implemented
}

auto project::add_method(const method_prototype& p_method) -> void
{
    assert(false); // not yet implemented
}

auto project::add_function(const function_prototype& p_function) -> void
{
    assert(false); // not yet implemented
}

project::builder::builder(const builder &rhs) : project_(rhs.project_) {}

project::builder::builder(builder &&rhs) noexcept :
    project_(std::move(rhs.project_)) {}

auto project::builder::operator=(const builder &rhs) -> builder &
{
    project_ = rhs.project_;
    return *this;
}

auto project::builder::operator=(builder &&rhs) noexcept -> builder &
{
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

auto project::builder::build() const -> project *
{
    return new project(project_);
}

