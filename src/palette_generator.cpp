#include "palette_generator.hpp"

#include <random>

namespace komposto
{

/* should be a member of harmonic distribution */
fraction_term_t get_random_harmonic_fraction_term()
{
    /* harmonic distribution should take care */
    static std::default_random_engine generator;
    // magic_number
    const double gamma = 3.5; //smaller this number, bigger the results.
    std::exponential_distribution<double> distribution{gamma};
    /**/
    
    // get rid of magic_number, complexity and richness will help.
    return 1 + distribution(generator)*10;
}

/* should be a member of harmonic distribution */
// harmonic distribution will have several modifiers such as:
// complexity, richness etc.
Ratio get_random_ratio()
{
    numerator_t numerator = get_random_harmonic_fraction_term();
    denominator_t denominator = get_random_harmonic_fraction_term();

    return Ratio{numerator, denominator};
}

/* member of Harmonizer? */
Tone derive_random_harmonic_tone(const Tone& base_tone)
{
    Ratio modifier{get_random_ratio()};
    Ratio modified_ratio{base_tone.ratio_ * modifier};

    return Tone{base_tone.base_frequency_, modified_ratio};
}

Palette PaletteGenerator::generate() const
{
    Tone base_tone{base_frequency_};
    Palette palette{};

    // this will be handled by harmonic distribution modifiers
    // magic_number
    integer_t number_of_tones{10};

    // this is madness, should use algorithms for_each
    for(int i = 0; i < number_of_tones; i++)
    {
        palette.tones_.push_back(derive_random_harmonic_tone(base_tone));
    }

    return palette;
}

}