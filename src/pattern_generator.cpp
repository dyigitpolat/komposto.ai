#include "pattern_generator.hpp"

#include "constants.hpp"
#include "motif_generator.hpp"
#include "motif_mutator.hpp"

#include <algorithm>
#include <vector>

namespace komposto
{

Palette PatternGenerator::get_motif_palette(const Motif& motif)
{
    Palette motif_palette{};
    std::for_each(motif.notes_.begin(), motif.notes_.end(),
        [&motif_palette](const Note& note){
            motif_palette.tones_.push_back(note.tone_);
        });
    
    return motif_palette;
}

void PatternGenerator::mutate_motifs(std::vector<Motif> &motifs) const
{
    std::for_each(motifs.begin(), motifs.end(),
        [this](Motif &motif){
            motif_mutator_.mutate(motif);
        });
}

void PatternGenerator::generate_tail(
    const Motif &base_motif, std::vector<Motif> &motifs) const
{
    integer_t tail_motif_count{base_motif.beats_ - k__default_head_motif_count};
    
    std::fill_n(std::back_inserter(motifs), 
        tail_motif_count, Motif{base_motif});

    mutate_motifs(motifs);
}

Motif PatternGenerator::generate_base_head(const Motif &base_motif) const
{
    RhythmicMotifGenerator rhythmic_motif_generator{};
    RhythmicMotif head_rhythmic_motif{
        rhythmic_motif_generator.generate(base_motif.beats_)};

    Palette head_palette{get_motif_palette(base_motif)};

    return Motif{
        motif_generator_.generate(head_palette, head_rhythmic_motif)};
}

void PatternGenerator::generate_head(
    const Motif &base_motif, std::vector<Motif> &motifs) const
{
    std::fill_n(std::back_inserter(motifs), 
        k__default_head_motif_count, generate_base_head(base_motif));

    mutate_motifs(motifs);
}

Pattern PatternGenerator::generate(const Motif &base_motif) const
{
    Pattern pattern{};

    generate_tail(base_motif, pattern.motifs_);
    generate_head(base_motif, pattern.motifs_);

    return pattern;
}

}