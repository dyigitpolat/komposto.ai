#pragma once

#include "motif.hpp"

#include <vector>

namespace komposto
{

class Pattern
{
public:
    std::vector<Motif> motifs_;

public:
    std::vector<Note> get_notes() const;

private:
    void shift_and_append(
        timestamp_beats_t shift_amount, 
        const Motif &motif, 
        std::vector<Note> &notes) const;
};

}