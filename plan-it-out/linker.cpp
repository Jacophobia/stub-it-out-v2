#include "linker.h"

#include <cassert>

const auto invalid_class_and_method_link = "Linking Error: there was a missing reference between a class and method";
const auto reference_declaration_number_mismatch = "Linking Error: number of references doesn't match number of declarations";
const auto caller_callee_number_mismatch = "Linking Error: attempted to call an undeclared method/function";

linker::linker(const settings& settings) : settings_(settings) {}

auto linker::operator=(const linker& rhs) -> linker&
{
    if (this == &rhs)
        return *this;
    
    settings_ = rhs.settings_;
    return *this;
}

auto linker::operator=(linker&& rhs) noexcept -> linker&
{
    if (this == &rhs)
        return *this;
    
    settings_ = rhs.settings_;
    return *this;
}

auto link_parent_to_child(project* proj, class_prototype* child) -> void
{
    // for each parent name, find the associated class and add it to the
    //  current class
    auto [has_parent, parent_name] = child->get_parent_name();
    
    if (!has_parent)
        return;
    
    const auto parent_class = proj->get_class(parent_name);
    
    child->set_parent(parent_class);
    parent_class->add_child(child);
}

auto link_parents_to_children(project* proj) -> void
{
    // iterate through all classes
    for (auto [it, end] = proj->get_class_iter(); it != end; ++it)
    {
        const auto curr_class = &(it->second);
        link_parent_to_child(proj, curr_class);
    }
    
    for (auto [it, end] = proj->get_class_iter(); it != end; ++it)
    {
        if (
            const auto curr_class = &(it->second);
            !curr_class->valid_children()
        )
        {
            throw std::exception(reference_declaration_number_mismatch);
        }
    }
}

auto link_methods_to_classes(project* proj) -> void
{
    // iterate through all methods
    for (auto [it, end] = proj->get_method_iter(); it != end; ++it)
    {
        const auto curr_method = &(*it);
        // get the associated class
        auto containing_class_name = curr_method->get_class_name();
        const auto containing_class = proj->get_class(containing_class_name);
        // confirm that the class contains the name of the method in its
        //  list of method names (otherwise throw an error)
        if (
            auto curr_method_name = curr_method->get_name();
            !containing_class->contains_method(curr_method_name)
        )
        {
            throw std::exception(invalid_class_and_method_link);
        }
        // add the method to the class
        containing_class->add_method(curr_method);
        // add the class to the method
        curr_method->set_class(containing_class);
    }
}

auto link_callee_and_caller(project* proj, function_prototype* function)
{
    for (auto [it, end] = function->get_call_names_iter(); it != end; ++it)
    {
        auto curr_function_name = *it;
        const auto [contains_function, callee] = proj->get_function(curr_function_name);
        function->add_function_call(callee);
    }

    if (!function->valid_calls())
    {
        throw std::exception(caller_callee_number_mismatch);
    }
}

auto link_callees_and_callers(project* proj) -> void
{
    for (auto [it, end] = proj->get_function_iter(); it != end; ++it)
    {
        const auto curr_function = &(it->second);
        link_callee_and_caller(proj, curr_function);
    }
    
    for (auto [it, end] = proj->get_method_iter(); it != end; ++it)
    {
        const auto curr_method = &(*it);
        link_callee_and_caller(proj, curr_method);
    }
}

auto linker::link(project* proj) -> void
{
    // 1. Link parent and child classes
    link_parents_to_children(proj);
    // 2. Link methods to their classes
    link_methods_to_classes(proj);
    // 3. Link functions to the functions they call
    link_callees_and_callers(proj);
}

auto linker::link(project& proj) -> void
{
    link(&proj);
}
