#pragma once

#include "palette.hpp"
#include "tone.hpp"

namespace komposto
{

using tone_iterator_t = decltype(std::begin(Palette{}.tones_));

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

    static tone_iterator_t step_bounded(
        const Palette& palette, 
        const tone_iterator_t &iter, 
        integer_t steps); 

    static Direction pick_random_direction();

    static integer_t pick_random_steps();

    static integer_t clamp_index(
        const Palette &palette, integer_t index);

    static integer_t get_palette_last_tone_index(
        const Palette &palette);
};

}