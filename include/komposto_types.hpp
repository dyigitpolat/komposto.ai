#pragma once

namespace komposto
{

using floating_point_t = double;
using integer_t = long;

// timing
using timestamp_beats_t = floating_point_t;
using duration_beats_t = floating_point_t;

// tone
using frequency_t = floating_point_t;
using pitch_cents_t = floating_point_t;
using octaves_t = floating_point_t;
using semitones_t = floating_point_t;

// fractionals
using fraction_term_t = integer_t;
using numerator_t = fraction_term_t;
using denominator_t = fraction_term_t;

// dynamics
using velocity_t = floating_point_t;

// complexity types
using harmonic_complexity_t = floating_point_t;
using rhythmic_complexity_t = floating_point_t;

// richness types
using harmonic_richness_t = floating_point_t;
using rhythmic_richness_t = floating_point_t;

// midi
using midi_key_t = integer_t;
using midi_velocity_t = integer_t;
using midi_pitch_bend_t = floating_point_t;
using midi_time_tick_t = integer_t;

// probability
using probability_t = floating_point_t;

}
