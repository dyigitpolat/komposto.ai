#include "palette.hpp"
#include <algorithm>

namespace rng = std::ranges;


namespace komposto
{

Tone Palette::get_base_tone() const
{
    auto is_base_tone = [](const Tone &t)
    {
        return t.ratio_.numerator_ == t.ratio_.denominator_;
    };

    auto found_tone_iter{
        rng::find_if(tones_, is_base_tone)};

    bool tone_not_found{found_tone_iter == tones_.cend()};
    if(tone_not_found)
    {
        return *tones_.begin();
    }
    
    return *found_tone_iter;
}


}