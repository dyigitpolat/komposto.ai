#include "tone_picker.hpp"

#include "constants.hpp"
#include "random.hpp"

#include <algorithm>

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

    tone_iterator_t next_iter = 
        previous_tone_iter + pick_random_steps();

    tone_iterator_t clamped_iter = clamp_iterator(palette, next_iter);

    return *(clamped_iter);
}

tone_iterator_t TonePicker::find_previous_tone(
    const Palette& palette, const Tone &previous_tone)
{
    tone_iterator_t iter = std::find_if(
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

tone_iterator_t TonePicker::clamp_iterator(
    const Palette &palette, const tone_iterator_t& iter)
{
    bool is_underflow{iter < palette.tones_.cbegin()};
    if(is_underflow)
    {
        return palette.tones_.cbegin();
    }

    bool is_overflow{iter >= palette.tones_.cend()};
    if(is_overflow)
    {
        return std::prev(palette.tones_.cend());
    }

    return iter;
}

}