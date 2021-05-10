#include "motif_generator.hpp"

#include "komposto_types.hpp"
#include "constants.hpp"
#include "harmonizer.hpp"

#include <random>
#include <algorithm>
#include <cstdlib>

namespace komposto
{

Motif MotifGenerator::generate(
    const Palette &palette, integer_t motif_beats) const
{
    Motif motif{motif_beats};

    RhythmicMotif rhytmic_motif = 
        rhythmic_motif_generator_.generate(motif_beats);

    std::for_each(rhytmic_motif.timings_.begin(), rhytmic_motif.timings_.end(),
        [&motif, &palette, this](const Timing &timing){
            motif.notes_.emplace_back(
                timing, Harmonizer::pick_tone(palette), k__default_dynamics);
        });
    
    return motif;
}

Motif MotifGenerator::generate(
    const Palette &palette, const RhythmicMotif &rhytmic_motif) const
{
    Motif motif{rhytmic_motif.beats_};

    std::for_each(rhytmic_motif.timings_.begin(), rhytmic_motif.timings_.end(),
        [&motif, &palette, this](const Timing &timing){
            motif.notes_.emplace_back(
                timing, Harmonizer::pick_tone(palette), k__default_dynamics);
        });
    
    return motif;
}

}