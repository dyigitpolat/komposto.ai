#pragma once

#include "komposto_types.hpp"

namespace komposto
{

class Timing
{
    timestamp_t start_;
    duration_t duration_;

public:
    timestamp_t get_start() const;
    timestamp_t get_end() const;
    duration_t get_duration() const;
};

}