#include "composition_generator.hpp"

#include "constants.hpp"
#include "tuning_provider.hpp"
#include "random.hpp"

#include <algorithm>

namespace komposto
{

integer_t CompositionGenerator::calculate_tuning_p_limit(
    harmonic_complexity_t harmonic_complexity)
{
    return k__default_calculate_tuning_p_limit(harmonic_complexity);
}

integer_t CompositionGenerator::calculate_palette_tones_count(
    harmonic_complexity_t harmonic_complexity, const Tuning &tuning)
{
    integer_t tones_count{harmonic_complexity * tuning.harmonics_.size()};

    if(tones_count <= 0) 
        return 1;

    return tones_count;
}


integer_t CompositionGenerator::calculate_motif_beats_count(
    rhythmic_complexity_t rhythmic_complexity)
{
    std::discrete_distribution<> distribution(
        {
            0.25 + rhythmic_complexity,
            0.50,
            0.25 + rhythmic_complexity,
        });

    integer_t beat_count_modifier{distribution(Random::get_engine())};
    
    return k__minimum_beats_in_motif + beat_count_modifier;
}

integer_t CompositionGenerator::calculate_pattern_motifs_count(
    rhythmic_complexity_t rhythmic_complexity)
{
    return k__default_pattern_motifs_count + (rhythmic_complexity * k__zero);
}

CompositionGenerator::CompositionDraft 
CompositionGenerator::generate_composition_draft(
    harmonic_complexity_t harmonic_complexity,
    rhythmic_complexity_t rhythmic_complexity)
{
    std::vector<SectionDraft> section_drafts;

    section_drafts.emplace_back(SectionDraft{
        2,4,2,
        harmonic_complexity * 0.4, 
        rhythmic_complexity * 0.4});

    section_drafts.emplace_back(SectionDraft{
        4,4,2,
        harmonic_complexity * 0.6, 
        rhythmic_complexity * 0.6});

    section_drafts.emplace_back(SectionDraft{
        8,2,1,
        harmonic_complexity * 0.8, 
        rhythmic_complexity * 0.8});

    section_drafts.emplace_back(SectionDraft{
        8,2,1,
        harmonic_complexity * 0.6, 
        rhythmic_complexity * 1.0});

    section_drafts.emplace_back(SectionDraft{
        2,4,2,
        harmonic_complexity * 0.4, 
        rhythmic_complexity * 0.5});
    
    section_drafts.emplace_back(SectionDraft{
        4,1,1,
        harmonic_complexity * 0.2, 
        rhythmic_complexity * 0.2});

    return CompositionDraft{section_drafts};
}

Section CompositionGenerator::draft_to_section(SectionDraft draft) const
{
    Tuning tuning{TuningProvider::get_just_harmonic_minor_tuning()};

    integer_t palette_tones_count{
        calculate_palette_tones_count(
            draft.section_harmonic_complexity_, tuning)};

    Palette palette{palette_generator_.generate(tuning, palette_tones_count)};

    return section_generator_.generate(
        palette,
        draft.motif_beats_count_,
        draft.patterns_count_,
        draft.pattern_motifs_count_
    );
}

Composition CompositionGenerator::generate(
    harmonic_complexity_t harmonic_complexity,
    rhythmic_complexity_t rhythmic_complexity) const
{
    CompositionDraft draft{generate_composition_draft(
        harmonic_complexity,
        rhythmic_complexity)};
    
    Composition composition{};
    std::for_each(draft.section_drafts_.cbegin(), draft.section_drafts_.cend(),
        [&composition, this](SectionDraft section_draft)
        {
            composition.sections_.push_back(draft_to_section(section_draft));
        }
    );

    return composition;
}

}
