#pragma once

#include "composition.hpp"
#include "section_generator.hpp"
#include "palette_generator.hpp"

#include <vector>

namespace komposto
{

class CompositionGenerator
{
    struct SectionDraft
    {
        integer_t motif_beats_count_;
        integer_t pattern_motifs_count_;
        integer_t patterns_count_;
        harmonic_complexity_t section_harmonic_complexity_;
        rhythmic_complexity_t section_rhythmic_complexity_;
    };

    struct CompositionDraft
    {
        std::vector<SectionDraft> section_drafts_;
    };

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
    
    Section draft_to_section(SectionDraft draft) const;

private:
    static CompositionDraft generate_composition_draft(
        harmonic_complexity_t harmonic_complexity,
        rhythmic_complexity_t rhythmic_complexity);

    static integer_t calculate_tuning_p_limit(
        harmonic_complexity_t harmonic_complexity);
    static integer_t calculate_palette_tones_count(
        harmonic_complexity_t harmonic_complexity, const Tuning &tuning);

    static integer_t calculate_motif_beats_count(
        rhythmic_complexity_t rhythmic_complexity);
    static integer_t calculate_pattern_motifs_count(
        rhythmic_complexity_t rhythmic_complexity);

};

}