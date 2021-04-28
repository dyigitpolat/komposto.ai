#pragma once

#include "motif.hpp"
#include "palette.hpp"

namespace komposto
{
    
class MotifGenerator
{
    Palette palette_;

public:
    MotifGenerator(const Palette& palette) :
        palette_(palette)
    {}
    Motif generate() const;

private:
    const Tone& pick_tone() const;
    Note create_note(timestamp_t note_begin) const;
};

}