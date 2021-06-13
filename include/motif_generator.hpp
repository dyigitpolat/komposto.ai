#pragma once

#include "motif.hpp"
#include "palette.hpp"
#include "rhythmic_motif_generator.hpp"
#include "dynamics_generator.hpp"

namespace komposto
{
    
class MotifGenerator
{
    RhythmicMotifGenerator rhythmic_motif_generator_;
    DynamicsGenerator dynamics_generator_;

public:
    MotifGenerator(
        const RhythmicMotifGenerator& rhythmic_motif_generator,
        const DynamicsGenerator& dynamics_generator) :
        rhythmic_motif_generator_(rhythmic_motif_generator),
        dynamics_generator_(dynamics_generator)
    {}
    Motif generate(const Palette &palette, integer_t motif_beats) const;
    Motif generate(
        const Palette &palette, const RhythmicMotif &rhytmic_motif) const;

private:
    Note create_note(timestamp_beats_t note_begin) const;
};

}