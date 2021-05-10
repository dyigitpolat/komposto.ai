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
    Palette generate(integer_t tuning_p_limit, integer_t tones_count) const;

private:
    std::vector<Ratio> sample_palette_ratios(
        integer_t tuning_p_limit, integer_t tones_count) const;
    std::vector<Ratio> sample_weighted(
        const Tuning &tuning, integer_t tones_count) const;

    std::vector<floating_point_t> generate_likelihood_weights(
        const std::vector<Ratio> &harmonic_ratios) const;
    
    static Ratio unisonic_simplify(const Ratio &harmonic_ratio);
    static Ratio unisonic_widen(const Ratio &harmonic_ratio);
};

}