#include "palette_generator.hpp"

#include "constants.hpp"
#include "harmonizer.hpp"
#include "random.hpp"

#include <vector>
#include <algorithm>

namespace rng = std::ranges;


namespace komposto
{

Palette PaletteGenerator::generate(
    Tuning &tuning, integer_t tones_count) const
{
    std::vector<Ratio> palette_ratios{
        sort_ratios_in_likelihood_order(tuning.harmonics_)
    };

    palette_ratios.resize(tones_count);

    palette_ratios = squeeze_ratios_into_octave(palette_ratios);

    palette_ratios = widen_ratios(palette_ratios);

    sort_ratios_ascending(palette_ratios);

    Palette palette{};
    rng::for_each(palette_ratios,
        [&palette, this](const Ratio& ratio){
            palette.tones_.emplace_back(base_frequency_, ratio);
        });

    return palette;
}

std::vector<Ratio> PaletteGenerator::sort_ratios_in_likelihood_order(
    const std::vector<Ratio> &harmonic_ratios)
{
    std::vector<Ratio> sorted_ratios{harmonic_ratios};

    std::sort(sorted_ratios.begin(), sorted_ratios.end(), 
        [](const Ratio& ratio1, const Ratio& ratio2)
        {
            return calculate_likelihood_score(ratio1) 
                > calculate_likelihood_score(ratio2);
        });

    return sorted_ratios;
}

floating_point_t PaletteGenerator::calculate_likelihood_score(
    const Ratio &harmonic_ratio)
{
    Ratio simplified_ratio{octave_equivalent_simplify(harmonic_ratio)};

    floating_point_t loss{
        static_cast<floating_point_t>
            (simplified_ratio.denominator_ + simplified_ratio.numerator_)
    };

    return 1. / loss;
}

Ratio PaletteGenerator::octave_equivalent_simplify(const Ratio &harmonic_ratio)
{
    numerator_t simplified_numerator{harmonic_ratio.numerator_};
    denominator_t simplified_denominator{harmonic_ratio.denominator_};

    while(0 == simplified_numerator % 2) 
    {
        simplified_numerator /= 2;
    }

    while(0 == simplified_denominator % 2) 
    {
        simplified_denominator /= 2;
    }

    return Ratio{simplified_numerator, simplified_denominator};
}

std::vector<Ratio> PaletteGenerator::squeeze_ratios_into_octave(
        const std::vector<Ratio> &harmonic_ratios)
{
    std::vector<Ratio> squeezed_ratios;
    
    rng::for_each(harmonic_ratios,
        [&squeezed_ratios](const Ratio &ratio)
        {
            squeezed_ratios.push_back(squeeze_into_octave(ratio));
        });   

    return squeezed_ratios;
}

Ratio PaletteGenerator::squeeze_into_octave(const Ratio &harmonic_ratio)
{
    Ratio squeezed_ratio{harmonic_ratio};

    while(squeezed_ratio.get_frequency_factor() > 2)
    {
        squeezed_ratio.denominator_ *= 2;
    }

    while(squeezed_ratio.get_frequency_factor() < 1)
    {
        squeezed_ratio.numerator_ *= 2;
    }

    return squeezed_ratio;
}

std::vector<Ratio> PaletteGenerator::widen_ratios(
        const std::vector<Ratio> &harmonic_ratios)
{
    std::vector<Ratio> widened_ratios;

    rng::for_each(harmonic_ratios,
        [&widened_ratios](const Ratio &ratio)
        {
            widened_ratios.push_back(octave_down(ratio));
        });
    
    rng::for_each(harmonic_ratios,
        [&widened_ratios](const Ratio &ratio)
        {
            widened_ratios.push_back(ratio);
        });

    rng::for_each(harmonic_ratios,
        [&widened_ratios](const Ratio &ratio)
        {
            widened_ratios.push_back(octave_up(ratio));
        });

    return widened_ratios;
}

Ratio PaletteGenerator::octave_up(const Ratio &harmonic_ratio)
{
    numerator_t modified_numerator{harmonic_ratio.numerator_ * 2};
    return Ratio(modified_numerator, harmonic_ratio.denominator_);
}

Ratio PaletteGenerator::octave_down(const Ratio &harmonic_ratio)
{
    denominator_t modified_denominator{harmonic_ratio.denominator_ * 2};
    return Ratio(harmonic_ratio.numerator_, modified_denominator);
}

void PaletteGenerator::sort_ratios_ascending(std::vector<Ratio> &harmonic_ratios)
{
    auto compare_ratios = [](Ratio &r1, Ratio &r2)
    {
        return r1.get_frequency_factor() < r2.get_frequency_factor();
    };

    rng::sort(harmonic_ratios, compare_ratios);
}

}