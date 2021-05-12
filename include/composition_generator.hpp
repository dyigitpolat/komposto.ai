#pragma once

#include "composition.hpp"
#include "section_generator.hpp"
#include "palette_generator.hpp"

namespace komposto
{

class CompositionGenerator
{
    SectionGenerator section_generator_;
    PaletteGenerator palette_generator_;

public:
    CompositionGenerator(
        const SectionGenerator section_generator,
        const PaletteGenerator palette_generator) :
        section_generator_(section_generator),
        palette_generator_(palette_generator) {}

    Composition generate(
        harmonic_complexity_t harmonic_complexity,
        rhythmic_complexity_t rhythmic_complexity) const;

private:
    static integer_t calculate_tuning_p_limit(
        harmonic_complexity_t harmonic_complexity);
    static integer_t calculate_palette_tones_count(
        harmonic_complexity_t harmonic_complexity);

    static integer_t calculate_motif_beats_count(
        rhythmic_complexity_t rhythmic_complexity);
    static integer_t calculate_pattern_motifs_count(
        rhythmic_complexity_t rhythmic_complexity);

};

}