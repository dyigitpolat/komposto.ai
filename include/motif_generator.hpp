#pragma once

#include "motif.hpp"
#include "palette.hpp"
#include "rhythmic_motif_generator.hpp"

namespace komposto
{
    
class MotifGenerator
{
    RhythmicMotifGenerator rhythmic_motif_generator_;

public:
    MotifGenerator(const RhythmicMotifGenerator& rhythmic_motif_generator) :
        rhythmic_motif_generator_(rhythmic_motif_generator)
    {}
    Motif generate(const Palette &palette, integer_t motif_beats) const;

private:
    const Tone& pick_tone(const Palette &palette) const;
    Note create_note(timestamp_beats_t note_begin) const;
};

}