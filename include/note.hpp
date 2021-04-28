#pragma once

#include "timing.hpp"
#include "tone.hpp"
#include "dynamics.hpp"

namespace komposto
{

class Note 
{
    Timing timing_;
    Tone tone_;
    Dynamics dynamics_;

public:
    Note(Timing timing, Tone tone, Dynamics dynamics = Dynamics{}) : 
        timing_(timing),
        tone_(tone),
        dynamics_(dynamics)
    {}

    const Timing& get_timing() const;
    const Tone& get_tone() const;
    const Dynamics& get_dynamics() const;
   
};

}