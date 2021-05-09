#pragma once

#include "komposto_types.hpp"

namespace komposto
{

class Timing
{
public:
    timestamp_beats_t start_;
    duration_beats_t duration_;

    Timing(timestamp_beats_t start, duration_beats_t duration) :
        start_(start),
        duration_(duration)
    {}

    inline timestamp_beats_t get_end() const
    {
        return start_ + duration_;
    } 
};

}