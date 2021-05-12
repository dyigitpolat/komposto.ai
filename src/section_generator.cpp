#include "section_generator.hpp"

#include "constants.hpp"

#include <algorithm>

namespace komposto
{

Section SectionGenerator::generate(
    const Palette &palette, 
    integer_t motif_beats, 
    integer_t patterns_count,
    integer_t pattern_motif_count) const
{
    Motif base_motif{motif_generator_.generate(palette, motif_beats)};
    Section section{};

    Pattern base_pattern{pattern_generator_.generate(
        base_motif, pattern_motif_count)};

    integer_t tail_pattern_count{
        patterns_count - k__default_head_pattern_count
    };

    std::fill_n(std::back_inserter(section.patterns_),
        tail_pattern_count, base_pattern);

    section.patterns_.push_back(pattern_generator_.generate(
        base_motif, pattern_motif_count));

    return section;
}

}