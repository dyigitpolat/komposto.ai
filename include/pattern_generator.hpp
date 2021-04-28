#pragma once

#include "pattern.hpp"

namespace komposto
{

class PatternGenerator
{
public:
    virtual Pattern generate() const = 0;
};

}