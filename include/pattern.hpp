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
    duration_beats_t get_duration() const;
};

}