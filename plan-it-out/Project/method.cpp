#include "method.h"

method_prototype::method_prototype(std::string name, std::string class_name, std::string returns):
    function_prototype(std::move(name), std::move(returns)),
    class_name_(std::move(class_name)), class_(nullptr) {}

method_prototype::method_prototype(const method_prototype &rhs):
    function_prototype(rhs), class_name_(rhs.class_name_), class_(rhs.class_) {}

method_prototype::method_prototype(method_prototype &&rhs) noexcept:
    function_prototype(std::move(rhs)), class_name_(std::move(rhs.class_name_)),
    class_(rhs.class_) {}

method_prototype & method_prototype::operator=(const method_prototype &rhs) {
    if (this == &rhs)
        return *this;
        
    function_prototype::operator=(rhs);
        
    class_name_ = rhs.class_name_;
    class_ = rhs.class_;
        
    return *this;
}

method_prototype & method_prototype::operator=(method_prototype &&rhs) noexcept {
    if (this == &rhs)
        return *this;
        
    class_name_ = std::move(rhs.class_name_);
        
    class_ = rhs.class_;
    function_prototype::operator=(std::move(rhs));
        
    return *this;
}

auto method_prototype::set_class(class_prototype *parent_class) -> void
{
    class_ = parent_class;
}

auto method_prototype::get_class_name() const -> std::string
{
    return class_name_;
}

