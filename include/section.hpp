#pragma once

#include "pattern.hpp"

#include <vector>

namespace komposto
{

class Section
{
public:
    std::vector<Pattern> patterns_;

public:
    std::vector<Note> get_notes() const;
    duration_beats_t get_duration() const;
};

}