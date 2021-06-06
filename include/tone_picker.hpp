#pragma once

#include "palette.hpp"
#include "tone.hpp"

namespace komposto
{

using tone_iterator_t = std::vector<Tone>::const_iterator;

class TonePicker
{

enum class Direction
{
    k__up = 0,
    k__down = 1
};

public:
    static const Tone& pick_tone(
        const Palette &palette, const Tone &previous_tone);

private: 
    static tone_iterator_t find_previous_tone(
        const Palette& palette, const Tone &previous_tone); 

    static Direction pick_random_direction();

    static integer_t pick_random_steps();

    static tone_iterator_t clamp_iterator(
        const Palette &palette, const tone_iterator_t& iter);
};

}