#pragma once

#include "palette.hpp"
#include "tuning.hpp"

namespace komposto
{
    
class Harmonizer
{

public:
    static const Tone& pick_tone(const Palette &palette);
    static Tuning get_p_limit_tuning(integer_t prime_p);

private:
    static Tuning get_5_limit_tuning();
    static Tuning get_7_limit_tuning();
    static Tuning get_11_limit_tuning();
};

}