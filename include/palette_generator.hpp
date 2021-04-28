#pragma once

#include "palette.hpp"

#include <vector>

namespace komposto
{

class PaletteGenerator
{
    frequency_t base_frequency_;
    
public:
    Palette generate() const;
};

}