#pragma once

#include "komposto_types.hpp"

namespace komposto
{

class Timing
{
public:
    timestamp_t start_;
    duration_t duration_;

    Timing(timestamp_t start, duration_t duration) :
        start_(start),
        duration_(duration)
    {}

    inline timestamp_t get_end() const;
};

}