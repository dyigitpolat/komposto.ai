#pragma once

#include "palette.hpp"
#include "tuning.hpp"

#include <vector>

namespace komposto
{

class PaletteGenerator
{
    frequency_t base_frequency_;
    
public:
    PaletteGenerator(frequency_t base_frequency) :
        base_frequency_(base_frequency)
    {}
    Palette generate(Tuning &tuning, integer_t tones_count) const;
    static void sort_ratios_ascending(std::vector<Ratio> &harmonic_ratios);

private:
    static std::vector<Ratio> squeeze_ratios_into_octave(
        const std::vector<Ratio> &harmonic_ratios);

    static std::vector<Ratio> widen_ratios(
        const std::vector<Ratio> &harmonic_ratios);

    static std::vector<Ratio> sort_ratios_in_likelihood_order(
        const std::vector<Ratio> &harmonic_ratios);

    static floating_point_t calculate_likelihood_score(
        const Ratio &harmonic_ratio);

    static Ratio octave_equivalent_simplify(const Ratio &harmonic_ratio);
    static Ratio octave_up(const Ratio &harmonic_ratio);
    static Ratio octave_down(const Ratio &harmonic_ratio);
    static Ratio squeeze_into_octave(const Ratio &harmonic_ratio);
};

}