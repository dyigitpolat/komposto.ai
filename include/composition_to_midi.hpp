#pragma once

class CompositionToMIDI
{
/*
https://forum.juce.com/t/mapping-frequencies-to-midi-notes/1762

ANSWER OF: robiwan
*/

/*
With 440 Hz at middle A (midi note 69) you get:

Hertz = 440.0 * pow(2.0, (midi note - 69)/12);

Reversed:

midi note = log(Hertz/440.0)/log(2) * 12 + 69;

If you want to play the correct frequency from that, you need to pitch bend from the midi note. Say you want 430.3 Hz when having +/- 200 cents pitch bend:

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
};