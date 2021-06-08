#include "pattern_generator.hpp"

#include "constants.hpp"
#include "motif_generator.hpp"
#include "motif_mutator.hpp"

#include <algorithm>
#include <vector>
#include <set>

namespace komposto
{

Palette PatternGenerator::create_palette_from_motif(const Motif& motif)
{
    Palette motif_palette{};

    auto compare_tones{
        [](const Tone& t1, const Tone& t2)
        {
            return t1.ratio_.get_frequency_factor() + k__epsilon 
                < t2.ratio_.get_frequency_factor();
        }
    };

    std::set< Tone, decltype(compare_tones) > tone_set(compare_tones);

    std::for_each(motif.notes_.begin(), motif.notes_.end(),
        [&tone_set](const Note& note){
            tone_set.insert(note.tone_);
        });
    
    std::for_each(tone_set.begin(), tone_set.end(),
        [&motif_palette](const Tone& tone){
            motif_palette.tones_.push_back(tone);
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
    const Motif &base_motif, 
    std::vector<Motif> &motifs, 
    integer_t pattern_motif_count) const
{
    integer_t tail_motif_count{
        pattern_motif_count - k__default_head_motif_count};
    
    std::fill_n(std::back_inserter(motifs), 
        tail_motif_count, Motif{base_motif});

    mutate_motifs(motifs);
}

Motif PatternGenerator::generate_base_head(const Motif &base_motif) const
{
    RhythmicMotifGenerator rhythmic_motif_generator{};
    RhythmicMotif head_rhythmic_motif{
        rhythmic_motif_generator.generate(base_motif.beats_)};

    Palette head_palette{create_palette_from_motif(base_motif)};

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

Pattern PatternGenerator::generate(const Motif &base_motif, integer_t pattern_motif_count) const
{
    Pattern pattern{};

    generate_tail(base_motif, pattern.motifs_, pattern_motif_count);
    generate_head(base_motif, pattern.motifs_);

    return pattern;
}

}