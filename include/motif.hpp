#pragma once

#include "note.hpp"

#include <vector>

namespace komposto
{

class Motif
{
public:
    integer_t beats_count_;
    std::vector<Note> notes_;

public:
    Motif(integer_t beats) : beats_count_(beats) {}

};

}