#pragma once

#include <string>

#include "class.h"
#include "function.h"

class method_prototype : public function_prototype
{
public:
    // construct / copy
    explicit method_prototype(
        std::string name = "",
        std::string class_name = "",
        std::string returns = ""
    );
    method_prototype(const method_prototype &rhs);
    method_prototype(method_prototype &&rhs) noexcept;
    method_prototype & operator=(const method_prototype &rhs);
    method_prototype & operator=(method_prototype &&rhs) noexcept;
    
    // destructor
    ~method_prototype() = default;
    
    auto set_class(class_prototype* parent_class) -> void;
    [[nodiscard]] auto get_class_name() const -> std::string;
private:
    std::string class_name_;
    class_prototype* class_;
};
