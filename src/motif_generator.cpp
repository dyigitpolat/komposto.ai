#include "motif_generator.hpp"

#include "komposto_types.hpp"
#include "constants.hpp"

#include <random>
#include <algorithm>
#include <cstdlib>

namespace komposto
{

const Tone& MotifGenerator::pick_tone(const Palette &palette) const
{
    static std::default_random_engine generator;

    const int tones_count{static_cast<int>(palette.tones_.size())};
    std::uniform_int_distribution distribution{0, tones_count - 1};
    
    //pick random
    return palette.tones_[ distribution(generator) ];
}

Motif MotifGenerator::generate(
    const Palette &palette, integer_t motif_beats) const
{
    Motif motif{};

    RhythmicMotif rhytmic_motif = 
        rhythmic_motif_generator_.generate(motif_beats);

    std::for_each(rhytmic_motif.timings_.begin(), rhytmic_motif.timings_.end(),
        [&motif, &palette, this](const Timing &timing){
            motif.notes_.emplace_back(
                timing, pick_tone(palette), k__default_dynamics);
    });
    
    return motif;
}

}