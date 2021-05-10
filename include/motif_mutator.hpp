#pragma once

#include "motif.hpp"
#include "palette.hpp"

namespace komposto
{
    
class MotifMutator
{
    Palette palette_;

public:
    MotifMutator(const Palette &palette) : palette_(palette) {};
    void mutate(Motif &motif) const;

private:
    static probability_t calculate_mutation_proabaility(
        integer_t count_motif_notes);
    void mutate_tone(Tone &tone, integer_t count_motif_notes) const;

};

}