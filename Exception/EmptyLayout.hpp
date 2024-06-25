#pragma once

#include <stdexcept>

class EmptyLayout : public std::runtime_error
{
public:
    EmptyLayout() : std::runtime_error("Layout is empty") { }
    ~EmptyLayout() { }
};