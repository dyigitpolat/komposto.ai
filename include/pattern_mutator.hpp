#pragma once

#include "pattern.hpp"
#include "palette.hpp"

namespace komposto
{
    
class PatternMutator
{
    Palette palette_;

public:
    PatternMutator(const Palette &palette) : palette_(palette) {};
    void mutate(Pattern &pattern) const;

};

}