#include "tone_picker.hpp"

#include "constants.hpp"
#include "random.hpp"

#include <algorithm>

namespace rng = std::ranges;


namespace komposto
{

const Tone& TonePicker::pick_tone(
    const Palette &palette, const Tone &previous_tone)
{
    const tone_iterator_t previous_tone_iter = 
        find_previous_tone(palette, previous_tone);

    const bool tone_not_found{previous_tone_iter == palette.tones_.cend()};
    if(tone_not_found)
    {
        return *(palette.tones_.begin());
    }

    return *step_bounded(palette, previous_tone_iter, pick_random_steps());
}

tone_iterator_t TonePicker::find_previous_tone(
    const Palette& palette, const Tone &previous_tone)
{
    tone_iterator_t iter = rng::find_if(
        palette.tones_.cbegin(), palette.tones_.cend(), 
        [&previous_tone](const Tone &t)
        {
            return t.ratio_ == previous_tone.ratio_;
        });
    
    return iter;
}

integer_t TonePicker::pick_random_steps()
{
    std::discrete_distribution<> distribution(
        {0.125, 0.5, 0.25, 0.125});

    integer_t step_amount{distribution(Random::get_engine())};

    if(Direction::k__down == pick_random_direction())
    {
        step_amount = -step_amount;
    }

    return step_amount;
}

TonePicker::Direction TonePicker::pick_random_direction()
{
    std::discrete_distribution<> distribution({k__half, k__half});
    return Direction{distribution(Random::get_engine())};
}

tone_iterator_t TonePicker::step_bounded(
    const Palette& palette, 
    const tone_iterator_t &iter, 
    integer_t steps)
{
    integer_t prev_tone_index{
        rng::distance(palette.tones_.cbegin(), iter)};

    integer_t next_tone_index{
        prev_tone_index + steps
    };

    integer_t clamped_index = clamp_index(palette, next_tone_index);

    return rng::next(palette.tones_.cbegin(), clamped_index);
}

integer_t TonePicker::clamp_index(
    const Palette &palette, integer_t index)
{
    bool underflowed{index < 0};
    if(underflowed)
    {
        return 0;
    }

    integer_t last_tone_index{get_palette_last_tone_index(palette)};

    bool overflowed{index > last_tone_index};
    if(overflowed)
    {
        return last_tone_index;
    }

    return index;
}

integer_t TonePicker::get_palette_last_tone_index(
    const Palette &palette)
{
    return rng::distance(
        palette.tones_.cbegin(), 
        rng::prev(palette.tones_.cend()));
}

}