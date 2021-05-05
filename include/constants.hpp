#pragma once

#include "komposto_types.hpp"

#include <limits>

namespace komposto
{

// Arithmetic
constexpr floating_point_t k__epsilon{
    std::numeric_limits<floating_point_t>::epsilon()};

// Music theory
constexpr frequency_t k__middle_a_frequency{440.0};
constexpr frequency_t k__equal_temparament_exponent{2.0};
constexpr integer_t k__equal_temparament_steps{12};
constexpr pitch_cents_t k__cents_in_octave{k__equal_temparament_steps * 100.0};

// MIDI
constexpr integer_t k__middle_a_midi_key{69};
constexpr pitch_cents_t k__midi_pitch_bend_range{200.0};
constexpr midi_velocity_t k__midi_velocity_max{127};
constexpr midi_pitch_bend_t k__zero_bend{0.0};
constexpr midi_time_tick_t k__midi_ticks_per_beat{4800};

}
