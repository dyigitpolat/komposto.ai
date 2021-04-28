#pragma once

#include "timing.hpp"
#include "tone.hpp"
#include "dynamics.hpp"

namespace komposto
{

class Note 
{
public:
    Timing timing_;
    Tone tone_;
    Dynamics dynamics_;

    Note(
        const Timing& timing, 
        const Tone& tone, 
        const Dynamics& dynamics = Dynamics{}) : 
        timing_(timing),
        tone_(tone),
        dynamics_(dynamics)
    {}
   
};

}