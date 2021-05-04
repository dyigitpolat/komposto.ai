#include "notes_to_midi.hpp"

#include "constants.hpp"

#include <cmath>

namespace komposto
{

struct MidiTone
{
    midi_key_t midi_key;
    midi_pitch_bend_t midi_pitch_bend_amount;
};

inline octaves_t octaves(const frequency_t x, const frequency_t base)
{
    return std::log2(x / base);
}

inline semitones_t semitones_from_middle_a(const midi_key_t key)
{
    return key - k__middle_a_midi_key;
}

inline midi_key_t frequency_to_midi_key(const frequency_t frequency)
{
    return 
        octaves(frequency, k__middle_a_frequency)
        * k__equal_temparament_steps 
        + k__middle_a_midi_key;
}

inline frequency_t midi_key_to_frequency(const midi_key_t key)
{
    return 
        k__middle_a_frequency
        * std::pow(
            k__equal_temparament_exponent, 
            semitones_from_middle_a(key) / k__equal_temparament_steps);
}

inline midi_pitch_bend_t pitch_bend_amount(
    const frequency_t x, 
    const frequency_t base)
{
    return 
        octaves(x, base)
        * k__cents_in_octave 
        / k__midi_pitch_bend_range;
}

MidiTone frequency_to_midi_tone(frequency_t frequency)
{
    frequency += k__epsilon;

    const midi_key_t coarse_key{frequency_to_midi_key(frequency)};

    const frequency_t coarse_frequency{midi_key_to_frequency(coarse_key)};

    const midi_pitch_bend_t bend_amount{
        pitch_bend_amount(frequency, coarse_frequency)
    };

    return MidiTone{coarse_key, bend_amount};
}

}