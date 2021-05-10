#include "harmonizer.hpp"

#include <random>

namespace komposto
{

const Tone& Harmonizer::pick_tone(const Palette &palette)
{
    static std::default_random_engine generator;

    const int tones_count{static_cast<int>(palette.tones_.size())};
    std::uniform_int_distribution distribution{0, tones_count - 1};
    
    //pick random
    return palette.tones_[ distribution(generator) ];
}

}