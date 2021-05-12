#pragma once

#include "komposto_types.hpp"
#include "note.hpp"

#include <vector>

namespace komposto
{
    
class Utilities
{
public:
    static void time_shift_and_append_notes (
        timestamp_beats_t shift_amount, 
        const std::vector<Note> &notes_to_shift, 
        std::vector<Note> &shifted_notes);
};

}