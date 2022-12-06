#pragma once
#include "settings.h"
#include "Project/project.h"

class linker
{
public:
    // default constructor
    linker() = delete;

    // with settings
    explicit linker(const settings& settings);

    // destructor
    ~linker() = default;

    // copy / move
    linker(const linker& rhs) = default;
    linker(linker&& rhs) = default;
    auto operator=(const linker& rhs) -> linker&;
    auto operator=(linker&& rhs) noexcept -> linker&;

    // link project internals together
    auto link(project* proj) -> void;
    auto link(project& proj) -> void;
private:
    settings settings_;
};
