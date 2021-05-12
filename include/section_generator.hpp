#pragma once

#include "pattern_generator.hpp"
#include "pattern_mutator.hpp"
#include "section.hpp"
#include "palette.hpp"

namespace komposto
{

class SectionGenerator
{
    PatternMutator pattern_mutator_;
    PatternGenerator pattern_generator_;
    MotifGenerator motif_generator_;

public:
    SectionGenerator(
        const PatternMutator& pattern_mutator,
        const PatternGenerator& pattern_generator,
        const MotifGenerator& motif_generator) :
        pattern_mutator_(pattern_mutator),
        pattern_generator_(pattern_generator),
        motif_generator_(motif_generator) {}

    Section generate(
        const Palette &palette, 
        integer_t motif_beats, 
        integer_t patterns_count,
        integer_t pattern_motif_count) const;

};

}