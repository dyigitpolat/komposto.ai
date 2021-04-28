#include "note.hpp"

namespace komposto
{

const Timing& Note::get_timing() const
{
    return timing_;
}

const Tone& Note::get_tone() const
{
    return tone_;
}

const Dynamics& Note::get_dynamics() const
{
    return dynamics_;
}

}
   