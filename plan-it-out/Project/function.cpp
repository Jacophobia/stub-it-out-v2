#include "function.h"

function_prototype::function_prototype(std::string name, std::string returns) :
    name_(std::move(name)), returns_(std::move(returns)) {}

function_prototype::function_prototype(const function_prototype &rhs) :
    name_(rhs.name_), calls_names_(rhs.calls_names_), calls_(rhs.calls_),
    parameters_(rhs.parameters_), returns_(rhs.returns_) {}

function_prototype::function_prototype(function_prototype &&rhs) noexcept :
    name_(std::move(rhs.name_)), calls_names_(std::move(rhs.calls_names_)),
    calls_(std::move(rhs.calls_)), parameters_(std::move(rhs.parameters_)),
    returns_(std::move(rhs.returns_)) {}

function_prototype & function_prototype::operator=(const function_prototype &rhs)
{
    if (this == &rhs)
        return *this;
    
    name_ = rhs.name_;
    calls_names_ = rhs.calls_names_;
    calls_ = rhs.calls_;
    parameters_ = rhs.parameters_;
    returns_ = rhs.returns_;

    return *this;
}

function_prototype & function_prototype::operator=(function_prototype &&rhs) noexcept
{
    name_ = std::move(rhs.name_);
    calls_names_ = std::move(rhs.calls_names_);
    calls_ = std::move(rhs.calls_);
    parameters_ = std::move(rhs.parameters_);
    returns_ = std::move(rhs.returns_);

    return *this;
}

auto function_prototype::add_function_call_name(const std::string& function_name) -> void
{
    calls_names_.emplace_back(function_name);
}

auto function_prototype::add_function_call(function_prototype *function) -> void
{
    calls_.emplace_back(function);
}

auto function_prototype::add_parameter(const std::string& name, const std::string& data_type) -> void
{
    parameters_.emplace(name, data_type);
}

auto function_prototype::get_name() const -> std::string
{
    return name_;
}

auto function_prototype::get_call_names_iter() -> std::pair<call_name_iter, call_name_iter>
{
    return { calls_names_.begin(), calls_names_.end() };
}

auto function_prototype::valid_calls() const -> bool
{
    return calls_names_.size() == calls_.size();
}
