#pragma once

#include "komposto_types.hpp"
#include "ratio.hpp"

namespace komposto
{

class Tone
{
public:
    frequency_t base_frequency_;
    Ratio ratio_;

public:
    Tone(frequency_t base_frequency, Ratio ratio = Ratio{}) :
        base_frequency_(base_frequency),
        ratio_(ratio)
    {}
    
    inline frequency_t get_frequency() const;

};

}