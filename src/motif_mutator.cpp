#include "motif_mutator.hpp"

#include "constants.hpp"
#include "harmonizer.hpp"

#include <random>
#include <algorithm>

namespace komposto
{

probability_t MotifMutator::
    calculate_mutation_proabaility(integer_t count_motif_notes)
{
    probability_t probability{1. / count_motif_notes};

    if(probability <= k__half - k__epsilon)
    {
        probability *= k__default_mutation_amplifier;
    }

    return probability;
}

void MotifMutator::mutate_tone(Tone &tone, integer_t count_motif_notes) const
{
    static std::random_device device;
    static std::mt19937 engine(device());

    probability_t mutation_probability{
        calculate_mutation_proabaility(count_motif_notes)};

    std::discrete_distribution<> distribution(
        {1. - mutation_probability, mutation_probability});

    if (distribution(engine)) 
    {
        tone = Harmonizer::pick_tone(palette_, tone);
    }   
}

void MotifMutator::mutate(Motif &motif) const
{
    std::for_each(motif.notes_.begin(), motif.notes_.end(),
        [&motif, this](Note &note){
            mutate_tone(
                note.tone_, 
                static_cast<integer_t>(motif.notes_.size()));
        });
}

}