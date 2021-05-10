#include "pattern.hpp"

#include <algorithm>

namespace komposto
{

void Pattern::shift_and_append(
    timestamp_beats_t shift_amount, 
    const Motif &motif, 
    std::vector<Note> &notes) const
{
    std::for_each(motif.notes_.begin(), motif.notes_.end(),
        [&notes, shift_amount, this](const Note& note){
            Note shifted_note{note};
            shifted_note.timing_.start_ += shift_amount;
            notes.emplace_back(shifted_note);
        });
}

std::vector<Note> Pattern::get_notes() const
{
    std::vector<Note> notes;

    timestamp_beats_t motif_begin{};
    std::for_each(motifs_.begin(), motifs_.end(),
        [&notes, &motif_begin, this](const Motif& motif){
            shift_and_append(motif_begin, motif, notes);
            motif_begin += motif.beats_;
        });
    
    return notes;
}

}