#pragma once

#include "komposto_types.hpp"
#include "dynamics.hpp"

#include <limits>

namespace komposto
{

// Arithmetic
constexpr floating_point_t k__epsilon{
    std::numeric_limits<floating_point_t>::epsilon()};
constexpr floating_point_t k__half{0.5};
constexpr floating_point_t k__zero{0.0};

// Music theory
constexpr frequency_t k__middle_a_frequency{440.0};
constexpr frequency_t k__equal_temparament_exponent{2.0};
constexpr integer_t k__equal_temparament_steps{12};
constexpr pitch_cents_t k__cents_in_octave{k__equal_temparament_steps * 100.0};

// komposto defaults, mostly temporary stuff that need to be generic-ified
constexpr floating_point_t k__default_beats_per_minute{120.0};
constexpr velocity_t k__default_velocity{1.0};
constexpr Dynamics k__default_dynamics{k__default_velocity};
constexpr integer_t k__default_head_motif_count{1};
constexpr integer_t k__default_head_pattern_count{1};
constexpr integer_t k__default_intro_section_patterns_count{4};
constexpr integer_t k__default_solo_section_patterns_count{1};
constexpr integer_t k__default_solo_section_pattern_motifs_count{12};
constexpr integer_t k__default_outro_section_patterns_count{4};

constexpr floating_point_t k__minimum_beats_in_motif{3};
constexpr integer_t k__default_pattern_motifs_count{4};
constexpr floating_point_t k__default_mutation_amplifier{1.25};
constexpr probability_t k__default_widening_probability{0.25};
constexpr integer_t k__default_tuning_p_limit{11};
constexpr floating_point_t k__default_likelihood_loss_modifier{
    k__default_tuning_p_limit * 2.};
constexpr integer_t k__default_palette_diversity_factor{20};
constexpr auto k__default_calculate_tuning_p_limit{
    [](harmonic_complexity_t harmonic_complexity) -> integer_t
    {
        if(harmonic_complexity > 0.8)
        {
            return 11;
        }

        if(harmonic_complexity > 0.5)
        {
            return 7;
        }

        return 5;
    }
};

// MIDI
constexpr integer_t k__middle_a_midi_key{69};
constexpr pitch_cents_t k__midi_pitch_bend_range_cents{200.0};
constexpr semitones_t k__midi_pitch_bend_range_semitones{
    k__midi_pitch_bend_range_cents / 100.0};
constexpr midi_velocity_t k__midi_velocity_max{127};
constexpr midi_pitch_bend_t k__zero_bend{0.0};
constexpr midi_time_tick_t k__midi_ticks_per_beat{4800};

}
