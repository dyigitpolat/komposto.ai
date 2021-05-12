#include "pattern.hpp"

#include "utilities.hpp"

#include <algorithm>

namespace komposto
{

std::vector<Note> Pattern::get_notes() const
{
    std::vector<Note> notes;

    timestamp_beats_t motif_begin{};
    std::for_each(motifs_.begin(), motifs_.end(),
        [&notes, &motif_begin, this](const Motif& motif){
            Utilities::time_shift_and_append_notes(
                motif_begin, motif.notes_, notes);
            motif_begin += motif.beats_;
        });
    
    return notes;
}

duration_beats_t Pattern::get_duration() const
{
    duration_beats_t duration{};
    std::for_each(motifs_.begin(), motifs_.end(),
        [&duration, this](const Motif& motif){
            duration += motif.beats_;
        });
    
    return duration;
}

}