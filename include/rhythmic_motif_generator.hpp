#pragma once

#include "komposto_types.hpp"
#include "rhythmic_motif.hpp"

#include <unordered_map>

namespace komposto
{
    
class RhythmicMotifGenerator
{

public:
    RhythmicMotif generate(integer_t beats) const;

private:
    static integer_t get_random_divisor();

};

}