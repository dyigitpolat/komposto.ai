#pragma once

#include "palette.hpp"
#include "tone.hpp"

namespace komposto
{
    
class Harmonizer
{

public:
    static const Tone& pick_tone(
        const Palette &palette, const Tone &previous_tone);
};

}