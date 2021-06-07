#include "harmonizer.hpp"

#include "tone_picker.hpp"

#include <vector>

namespace komposto
{

const Tone& Harmonizer::pick_tone(
    const Palette &palette, const Tone &previous_tone)
{
    return TonePicker::pick_tone(palette, previous_tone);
}

}