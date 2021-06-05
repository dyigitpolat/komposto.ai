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

    Tone previous_tone{palette.get_base_tone()};
    std::for_each(
        rhythmic_motif.timings_.begin(), rhythmic_motif.timings_.end(),
        [&motif, &palette, &previous_tone, this](const Timing &timing){
            Tone new_tone{Harmonizer::pick_tone(palette, previous_tone)};
            motif.notes_.emplace_back(
                timing, 
                new_tone, 
                k__default_dynamics);
            previous_tone = new_tone;
        });
    
    return motif;
}

}