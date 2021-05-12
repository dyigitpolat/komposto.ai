#include "composition.hpp"

#include "utilities.hpp"

#include <algorithm>

namespace komposto
{

std::vector<Note> Composition::get_notes() const
{
    std::vector<Note> notes;

    timestamp_beats_t sections_begin{};
    std::for_each(sections_.begin(), sections_.end(),
        [&notes, &sections_begin, this](const Section& section){
            Utilities::time_shift_and_append_notes(
                sections_begin, section.get_notes(), notes);
            sections_begin += section.get_duration();
        });
    
    return notes;
}

}