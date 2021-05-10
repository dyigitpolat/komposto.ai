#pragma once

#include "ratio.hpp"

#include <vector>

namespace komposto
{
    
class Tuning
{

public:
    std::vector<Ratio> harmonics_;

public:
    Tuning(const std::vector<Ratio> &harmonics) : harmonics_(harmonics) {}
};

}