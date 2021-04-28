#include "motif_generator.hpp"

#include "komposto_types.hpp"

#include <random>
#include <cstdlib>

namespace komposto
{

/* should be a member of rhytmic distribution */
duration_t get_random_duration()
{
    /* rhythmic distribution should take care */
    static std::default_random_engine generator;
    // magic_number
    const double gamma = 5.0; //smaller this number, bigger the results.
    std::exponential_distribution<double> distribution{gamma};
    /**/
    
    integer_t exponent = distribution(generator)*20;
    duration_t time_denominator = std::pow(2.0, exponent);
    
    // get rid of magic_number, complexity and richness will help.
    return 1.0 / time_denominator;
}

const Tone& MotifGenerator::pick_tone() const
{
    static std::default_random_engine generator;
    const int tones_count{static_cast<int>(palette_.tones.size())};
    std::uniform_int_distribution distribution{0, tones_count};

    return palette_.tones[ distribution(generator) ];
}

Note MotifGenerator::create_note(timestamp_t note_begin) const
{
    Timing timing{note_begin, get_random_duration()};
    Tone tone{pick_tone()};

    return Note{timing, tone};
}

Motif MotifGenerator::generate() const
{
    Motif motif{};

    // this will be handled by rhythmic distribution modifiers
    // magic_number
    integer_t number_of_notes{5};

    // this is madness, should use algorithms for_each
    duration_t current_duration{};
    for(int i = 0; i < number_of_notes; i++)
    {
        // not necessarily a note. may be a tacet or a chord
        Note note{create_note(current_duration)};
        current_duration += note.timing_.duration_;

        motif.notes.push_back(note);
    }

    return motif;
}

}