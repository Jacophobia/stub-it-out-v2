#pragma once

#include <string>
#include <vector>
#include <map>

class function_prototype
{
public:
    // construct / copy
    explicit function_prototype(std::string name = "",std::string returns = "");
    function_prototype(const function_prototype& rhs);
    function_prototype(function_prototype&& rhs) noexcept;
    function_prototype& operator=(const function_prototype& rhs);
    function_prototype& operator=(function_prototype&& rhs) noexcept;

    // destructor
    ~function_prototype() = default;

    // set / add values
    auto add_function_call_name(const std::string& function_name) -> void;
    auto add_function_call(function_prototype* function) -> void;
    auto add_parameter(const std::string& name, const std::string& data_type) -> void;

    // type definitions (for readability)
    typedef std::vector<std::string>::iterator call_name_iter;

    // getters
    [[nodiscard]] auto get_name() const -> std::string;
    [[nodiscard]] auto get_call_names_iter() -> std::pair<call_name_iter, call_name_iter>;

    // validation
    [[nodiscard]] auto valid_calls() const -> bool;
protected:
    std::string name_;
    std::vector<std::string> calls_names_;
    std::vector<function_prototype*> calls_;
    std::map<std::string, std::string> parameters_;
    std::string returns_;
};
