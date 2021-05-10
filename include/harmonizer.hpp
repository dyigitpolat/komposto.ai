#pragma once

#include "palette.hpp"

namespace komposto
{
    
class Harmonizer
{

public:
    static const Tone& pick_tone(const Palette &palette);
};

}