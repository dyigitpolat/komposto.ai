#pragma once

#include "pattern.hpp"
#include "motif_generator.hpp"
#include "motif_mutator.hpp"

namespace komposto
{

class PatternGenerator
{
    MotifMutator motif_mutator_;
    MotifGenerator motif_generator_;

public:
    PatternGenerator(
        const MotifMutator& motif_mutator,
        const MotifGenerator& motif_generator) :
        motif_mutator_(motif_mutator),
        motif_generator_(motif_generator) {}

    Pattern generate(const Motif &motif, integer_t pattern_motif_count) const;

private:
    void mutate_motifs(std::vector<Motif> &motifs) const;
    void generate_tail(
        const Motif &base_motif, 
        std::vector<Motif> &motifs, 
        integer_t pattern_motif_count) const;
    void generate_head(
        const Motif &base_motif, std::vector<Motif> &motifs) const;
    Motif generate_base_head(const Motif &base_motif) const;
    
    static Palette get_motif_palette(const Motif& motif);
};

}