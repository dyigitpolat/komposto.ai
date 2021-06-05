#include "palette.hpp"
#include <algorithm>

namespace komposto
{

Tone Palette::get_base_tone() const
{
    auto is_base_tone = [](const Tone &t)
    {
        return t.ratio_.numerator_ == t.ratio_.denominator_;
    };

    return *std::find_if(tones_.cbegin(), tones_.cend(), is_base_tone);
}


}