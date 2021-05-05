#include "notes_to_midi.hpp"

#include "constants.hpp"

#include "MidiFile.h"

#include <cmath>
#include <algorithm>

namespace komposto
{

octaves_t NotesToMidi::octaves(
    const frequency_t x, const frequency_t base) const
{
    return std::log2(x / base);
}

semitones_t NotesToMidi::semitones_from_middle_a(
    const midi_key_t key) const
{
    return key - k__middle_a_midi_key;
}

midi_key_t NotesToMidi::frequency_to_midi_key(
    const frequency_t frequency) const
{
    return 
        octaves(frequency, k__middle_a_frequency)
        * k__equal_temparament_steps 
        + k__middle_a_midi_key;
}

frequency_t NotesToMidi::midi_key_to_frequency(
    const midi_key_t key) const
{
    return 
        k__middle_a_frequency
        * std::pow(
            k__equal_temparament_exponent, 
            semitones_from_middle_a(key) / k__equal_temparament_steps);
}

midi_pitch_bend_t NotesToMidi::pitch_bend_amount(
    const frequency_t x, 
    const frequency_t base) const
{
    return 
        octaves(x, base)
        * k__cents_in_octave 
        / k__midi_pitch_bend_range;
}

NotesToMidi::MidiTone NotesToMidi::frequency_to_midi_tone(
    frequency_t frequency) const
{
    frequency += k__epsilon;

    const midi_key_t coarse_key{frequency_to_midi_key(frequency)};

    const frequency_t coarse_frequency{midi_key_to_frequency(coarse_key)};

    const midi_pitch_bend_t bend_amount{
        pitch_bend_amount(frequency, coarse_frequency)
    };

    return MidiTone{coarse_key, bend_amount};
}

midi_velocity_t NotesToMidi::get_velocity_midi_value(
        const velocity_t velocity) const
{
    return static_cast<midi_velocity_t>(velocity * k__midi_velocity_max);
}

midi_time_tick_t NotesToMidi::get_midi_time_tick(
        const timestamp_t timestamp) const
{
    return static_cast<midi_time_tick_t>(timestamp * k__midi_ticks_per_beat);
}

void NotesToMidi::generate_midi_file(
    const std::vector<Note> &notes, const std::string &file_name)
{
    smf::MidiFile midi_file{};

    midi_file.setTicksPerQuarterNote(k__midi_ticks_per_beat);
    
    auto add_midi_messages = [&midi_file, this](const Note &note) {
        integer_t track{};
        integer_t channel{};

        MidiTone tone{frequency_to_midi_tone(note.tone_.get_frequency())};

        midi_velocity_t midi_velocity = 
            get_velocity_midi_value(note.dynamics_.velocity_);

        midi_time_tick_t midi_ticks_start = 
            get_midi_time_tick(note.timing_.start_);
        
        midi_time_tick_t midi_ticks_end = 
            get_midi_time_tick(note.timing_.get_end()) - 2;

        midi_file.addPitchBend(
            track, midi_ticks_start, channel, tone.midi_pitch_bend_amount_);
        midi_file.addNoteOn(
            track, midi_ticks_start, 
            channel, tone.midi_key_, midi_velocity);
        midi_file.addNoteOff(
            track, midi_ticks_end, 
            channel, tone.midi_key_, midi_velocity);
        midi_file.addPitchBend(
            track, midi_ticks_end, channel, tone.midi_pitch_bend_amount_);    
        midi_file.addPitchBend(
            track, midi_ticks_end + 1, channel, k__zero_bend);    
    };

    std::for_each(notes.begin(), notes.end(), add_midi_messages);

    midi_file.write(file_name);
}

}