#pragma once

#include "palette.hpp"
#include "tuning.hpp"

namespace komposto
{
    
class Harmonizer
{

public:
    static const Tone& pick_tone(
        const Palette &palette, const Tone &previous_tone);
        
    static Tuning get_p_limit_tuning(integer_t prime_p);
    static Tuning get_pythagorean_tuning(integer_t notes_count);
    static Tuning get_just_major_tuning();
    static Tuning get_just_minor_tuning();
    static Tuning get_just_harmonic_minor_tuning();
    static Tuning get_just_grave_minor_tuning();

private:
    static Tuning get_5_limit_tuning();
    static Tuning get_7_limit_tuning();
    static Tuning get_11_limit_tuning();
};

}