#pragma once

#include "tone.hpp"

#include <vector>

namespace komposto
{

class Palette
{
public:
    std::vector<Tone> tones_;

    Tone get_base_tone() const;
    
};

}