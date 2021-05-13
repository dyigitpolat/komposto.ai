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
    RhythmicMotif rhythmic_motif = 
        rhythmic_motif_generator_.generate(motif_beats);

    return generate(palette, rhythmic_motif);
}

Motif MotifGenerator::generate(
    const Palette &palette, const RhythmicMotif &rhythmic_motif) const
{
    Motif motif{rhythmic_motif.beats_};

    std::for_each(rhythmic_motif.timings_.begin(), rhythmic_motif.timings_.end(),
        [&motif, &palette, this](const Timing &timing){
            motif.notes_.emplace_back(
                timing, Harmonizer::pick_tone(palette), k__default_dynamics);
        });
    
    return motif;
}

}