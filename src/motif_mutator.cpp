#include "motif_mutator.hpp"

#include "constants.hpp"
#include "harmonizer.hpp"
#include "random.hpp"

#include <algorithm>

namespace rng = std::ranges;


namespace komposto
{

probability_t MotifMutator::
    calculate_mutation_proabaility(integer_t motif_notes_count)
{
    probability_t probability{1. / motif_notes_count};

    if(probability <= k__half - k__epsilon)
    {
        probability *= k__default_mutation_amplifier;
    }

    return probability;
}

void MotifMutator::mutate_tone(Tone &tone, integer_t motif_notes_count) const
{
    probability_t mutation_probability{
        calculate_mutation_proabaility(motif_notes_count)};

    std::discrete_distribution<> distribution(
        {1. - mutation_probability, mutation_probability});

    if (distribution(Random::get_engine())) 
    {
        tone = Harmonizer::pick_tone(palette_, tone);
    }   
}

void MotifMutator::mutate(Motif &motif) const
{
    rng::for_each(motif.notes_,
        [&motif, this](Note &note){
            mutate_tone(
                note.tone_, 
                static_cast<integer_t>(motif.notes_.size()));
        });
}

}