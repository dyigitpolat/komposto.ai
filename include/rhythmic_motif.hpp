#pragma once

#include "timing.hpp"

#include <vector>

namespace komposto
{

class RhythmicMotif
{
public:
    integer_t beats_count_;
    std::vector<Timing> timings_;

public:
    RhythmicMotif(integer_t beats) : beats_count_(beats) {}
};

}