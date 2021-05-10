#pragma once

#include "timing.hpp"

#include <vector>

namespace komposto
{

class RhythmicMotif
{
public:
    integer_t beats_;
    std::vector<Timing> timings_;

public:
    RhythmicMotif(integer_t beats) : beats_(beats) {}
};

}