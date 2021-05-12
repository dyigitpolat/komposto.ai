#include "section.hpp"

#include "utilities.hpp"

#include <algorithm>

namespace komposto
{

std::vector<Note> Section::get_notes() const
{
    std::vector<Note> notes;

    timestamp_beats_t pattern_begin{};
    std::for_each(patterns_.begin(), patterns_.end(),
        [&notes, &pattern_begin, this](const Pattern& pattern){
            Utilities::time_shift_and_append_notes(
                pattern_begin, pattern.get_notes(), notes);
            pattern_begin += pattern.get_duration();
        });
    
    return notes;
}

duration_beats_t Section::get_duration() const
{
    duration_beats_t duration{};
    std::for_each(patterns_.begin(), patterns_.end(),
        [&duration, this](const Pattern& pattern){
            duration += pattern.get_duration();
        });
    
    return duration;
}

}