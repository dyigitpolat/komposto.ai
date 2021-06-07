#include "composition_generator.hpp"

#include "constants.hpp"
#include "tuning_provider.hpp"
#include "random.hpp"

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
    return harmonic_complexity * tuning.harmonics_.size();
}


integer_t CompositionGenerator::calculate_motif_beats_count(
    rhythmic_complexity_t rhythmic_complexity)
{
    std::discrete_distribution<> distribution(
        {
            0.25,
            0.50,
            0.25,
        });

    integer_t beat_count_modifier{distribution(Random::get_engine()) - 1};
    integer_t mean_beat_count{
        static_cast<integer_t>(
            rhythmic_complexity * k__default_beat_count_factor)};
    
    return 2 + mean_beat_count + beat_count_modifier;
}

integer_t CompositionGenerator::calculate_pattern_motifs_count(
    rhythmic_complexity_t rhythmic_complexity)
{
    
    return k__default_pattern_motifs_count + (rhythmic_complexity * k__zero);
}

Composition CompositionGenerator::generate(
    harmonic_complexity_t harmonic_complexity,
    rhythmic_complexity_t rhythmic_complexity) const
{
    Composition composition{};

    Tuning tuning{TuningProvider::get_just_harmonic_minor_tuning()};

    integer_t palette_tones_count{
        calculate_palette_tones_count(harmonic_complexity, tuning)};

    integer_t motif_beats_count{
        calculate_motif_beats_count(rhythmic_complexity)};
    
    integer_t intro_section_patterns_count{
        k__default_intro_section_patterns_count};

    integer_t intro_section_pattern_motifs_count{
        calculate_pattern_motifs_count(rhythmic_complexity)};

    Section intro{
        section_generator_.generate(
            palette_generator_.generate(
                tuning, palette_tones_count),
            motif_beats_count,
            intro_section_patterns_count,
            intro_section_pattern_motifs_count)};

    integer_t solo_section_patterns_count{
        k__default_solo_section_patterns_count};

    integer_t solo_section_pattern_motifs_count{
        k__default_solo_section_pattern_motifs_count};

    Section solo{
        section_generator_.generate(
            palette_generator_.generate(
                tuning, palette_tones_count),
            motif_beats_count,
            solo_section_patterns_count,
            solo_section_pattern_motifs_count)};

    integer_t outro_section_patterns_count{
        k__default_outro_section_patterns_count};

    integer_t outro_section_pattern_motifs_count{
        calculate_pattern_motifs_count(rhythmic_complexity)};

    Section outro{
        section_generator_.generate(
            palette_generator_.generate(
                tuning, palette_tones_count),
            motif_beats_count,
            outro_section_patterns_count,
            outro_section_pattern_motifs_count)};

    composition.sections_.push_back(intro);
    composition.sections_.push_back(solo);
    composition.sections_.push_back(outro);

    return composition;
}

}
