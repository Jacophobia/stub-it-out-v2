#include "linker.h"

#include <cassert>

linker::linker(const settings& settings) : settings_(settings)
{
    assert(false); // not yet implemented
}

auto linker::operator=(const linker& rhs) -> linker&
{
    assert(false); // not yet implemented
    return *this;
}

auto linker::operator=(linker&& rhs) noexcept -> linker&
{
    assert(false); // not yet implemented
    return *this;
}

auto linker::link(project& proj) -> void
{
    link(&proj);
}

auto linker::link(project* proj) -> void
{
    assert(false); // not yet implemented
}
