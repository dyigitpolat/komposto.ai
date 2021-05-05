#pragma once

#include "komposto_types.hpp"
#include "note.hpp"

#include <string>
#include <vector>

namespace komposto
{
    
class NotesToMidi
{

public:
    void generate_midi_file(
        const std::vector<Note> &notes, const std::string &file_name);

private:
    struct MidiTone
    {
        midi_key_t midi_key_;
        midi_pitch_bend_t midi_pitch_bend_amount_;
    };

    midi_velocity_t get_velocity_midi_value(
        const velocity_t velocity) const;
    midi_time_tick_t get_midi_time_tick(
        const timestamp_t timestamp) const;
    octaves_t octaves(const frequency_t x, const frequency_t base) const;
    semitones_t semitones_from_middle_a(const midi_key_t key) const;
    midi_key_t frequency_to_midi_key(const frequency_t frequency) const;
    frequency_t midi_key_to_frequency(const midi_key_t key) const;
    midi_pitch_bend_t pitch_bend_amount(
        const frequency_t x, 
        const frequency_t base) const;
    MidiTone frequency_to_midi_tone(frequency_t frequency) const;

};

}


/*
https://forum.juce.com/t/mapping-frequencies-to-midi-notes/1762

ANSWER OF: robiwan
*/

/*
With 440 Hz at middle A (midi note 69) you get:
Hertz = 440.0 * pow(2.0, (midi note - 69)/12);

Reversed:
midi note = log(Hertz/440.0)/log(2) * 12 + 69;

If you want to play the correct frequency from that, 
you need to pitch bend from the midi note. 

Say you want 430.3 Hz when having +/- 200 cents pitch bend:
1 cent = 1/1200 octave
log(430.3/440)/log(2) * 1200 ~= -39 cents

with +8191/-8192 resolution of pitch bend that would be:
pitch bend value = 8192 * -39/200 = -1597

Hope that helps…
*/

/*
setPitchBendRange(...) //must be 2.0, it is default but beware.
addPitchBend(...) //for frequency adjustment

addNoteOn(...)
addNoteOff(...)

// parameters will be calculated according to above formula.
*/

/*
PPQN/PPQ : Pulses per quarter note
BPM : beats (quarter notes) per minute
if BPM is 120 and PPQN is 480, 
there are 120*480 ticks in 60 seconds
so 1 tick takes 60 / (120*480) seconds.

DEFAULT PPQN in midifile library is 120.

to set custom PPQN, USE:
MidiFile::setTicksPerQuarterNote(int ticks) 
*/