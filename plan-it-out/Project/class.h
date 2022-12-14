#pragma once

#include <map>
#include <string>
#include <vector>

class method_prototype;

class class_prototype
{
public:
    explicit class_prototype(std::string name = "", std::string parent_name = "");

    // setters
    auto set_parent(class_prototype* parent) -> void;
    auto add_child_name(const std::string& child_name) -> void;
    auto add_child(class_prototype* child) -> void;
    auto add_variable(const std::string& name, const std::string& data_type) -> void;
    auto add_method_name(const std::string& method_name) -> void;
    auto add_method(method_prototype* method) -> void;

    // typedefs for readability
    typedef std::_Tree_iterator<std::_Tree_val<std::_Tree_simple_types<std::pair<const std::string, std::string>>>> variable_iter;
    typedef std::vector<method_prototype *>::iterator method_iter;

    // getters
    [[nodiscard]] auto get_name() const -> std::string;
    [[nodiscard]] auto get_parent_name() const -> std::pair<bool, std::string>;
    [[nodiscard]] auto get_child_names() const -> std::vector<std::string>;
    [[nodiscard]] auto get_method(const std::string& name) const -> std::pair<bool, method_prototype*>;
    [[nodiscard]] auto get_variable_iter() -> std::pair<variable_iter, variable_iter>;
    [[nodiscard]] auto get_method_iter() -> std::pair<method_iter, method_iter>;

    // contains
    [[nodiscard]] auto contains_method(const std::string & method_name) -> bool;

    // is valid?
    [[nodiscard]] auto valid_children() -> bool;
private:
    std::string name_;
    std::string parent_name_;
    class_prototype* parent_;
    std::vector<std::string> children_names_;
    std::vector<class_prototype*> children_;
    std::map<std::string, std::string> variables_;
    std::vector<std::string> method_names_;
    std::vector<method_prototype*> methods_;
};
