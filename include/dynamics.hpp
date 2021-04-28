#pragma once

#include "komposto_types.hpp"

namespace komposto
{

class Dynamics
{
    velocity_t velocity_;

public:
    velocity_t get_velocity() const;
};

}