#include "utilities.hpp"

#include <algorithm>

namespace komposto
{

void Utilities::time_shift_and_append_notes(
    timestamp_beats_t shift_amount, 
    const std::vector<Note> &notes_to_shift, 
    std::vector<Note> &shifted_notes)
{
    std::for_each(notes_to_shift.begin(), notes_to_shift.end(),
        [&shifted_notes, shift_amount](const Note& note){
            Note shifted_note{note};
            shifted_note.timing_.start_ += shift_amount;
            shifted_notes.emplace_back(shifted_note);
        });
}

}