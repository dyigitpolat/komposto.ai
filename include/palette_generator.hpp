#pragma once

#include "palette.hpp"

#include <vector>

namespace komposto
{

class PaletteGenerator
{
    frequency_t base_frequency_;
    
public:
    PaletteGenerator(frequency_t base_frequency) :
        base_frequency_(base_frequency)
    {}
    Palette generate() const;
};

}