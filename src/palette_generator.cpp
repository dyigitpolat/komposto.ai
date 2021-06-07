#include "palette_generator.hpp"

#include "constants.hpp"
#include "harmonizer.hpp"
#include "random.hpp"

#include <vector>
#include <algorithm>

namespace komposto
{

Ratio PaletteGenerator::unisonic_widen(const Ratio &harmonic_ratio)
{
    std::discrete_distribution<> widening_decision_distribution(
        {1. - k__default_widening_probability, 
        k__default_widening_probability});

    bool has_decided_widening{
        1 == widening_decision_distribution(Random::get_engine())}; 

    if(false == has_decided_widening)
    {
        return harmonic_ratio;
    }

    numerator_t modified_numerator{harmonic_ratio.numerator_ * 2};
    return Ratio(modified_numerator, harmonic_ratio.denominator_);
}

Ratio PaletteGenerator::unisonic_simplify(const Ratio &harmonic_ratio)
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

std::vector<floating_point_t> PaletteGenerator::generate_likelihood_weights(
    const std::vector<Ratio> &harmonic_ratios) const
{
    std::vector<floating_point_t> weights;
    std::vector<Ratio> simplified_harmonic_ratios{};

    std::for_each(harmonic_ratios.begin(), harmonic_ratios.end(),
        [&simplified_harmonic_ratios](const Ratio &ratio){
            simplified_harmonic_ratios.push_back(
                unisonic_simplify(ratio));
        });

    auto likelihood = [](const Ratio &ratio) -> auto {
        floating_point_t loss{
            static_cast<floating_point_t>
                (ratio.denominator_ * ratio.numerator_ + 200)
            };
        loss += k__default_likelihood_loss_modifier;
        return 1. / loss;
    };

    std::for_each(
        simplified_harmonic_ratios.begin(), simplified_harmonic_ratios.end(),
        [&weights, &likelihood](const Ratio &ratio){
            weights.push_back(likelihood(ratio));
        });
    
    return weights;
}

std::vector<Ratio> PaletteGenerator::sample_weighted(
    const Tuning &tuning, integer_t tones_count) const
{
    std::vector<floating_point_t> weights{
        generate_likelihood_weights(tuning.harmonics_)};
    floating_point_t total_weight{ 
        std::accumulate(weights.begin(), weights.end(), 0.0)};

    std::vector<Ratio> sampled_ratios{};

    auto tuning_ratios_iterator = tuning.harmonics_.begin();
    auto sample_probabilistically = 
        [total_weight, &tuning_ratios_iterator, &sampled_ratios, tones_count]
        (floating_point_t weight){
            probability_t pick_probability{
                tones_count * weight / total_weight};

            std::discrete_distribution<> pick_distribution(
                {1. - pick_probability, 
                pick_probability});

            if(pick_distribution(Random::get_engine()))
            {
                sampled_ratios.push_back(*tuning_ratios_iterator);
            }
            ++tuning_ratios_iterator;
        };

    std::for_each(weights.begin(), weights.end(), sample_probabilistically);
    
    if(static_cast<integer_t>(sampled_ratios.size()) >= tones_count)
    {
        sampled_ratios.resize(tones_count);
    }
    else
    {
        integer_t remaining{
            tones_count - static_cast<integer_t>(sampled_ratios.size())};
        std::sample(
            tuning.harmonics_.begin(), tuning.harmonics_.end(), 
            std::back_inserter(sampled_ratios), 
            remaining, Random::get_engine());
    }
    
    return sampled_ratios;
}

std::vector<Ratio> PaletteGenerator::sample_ratios_from_tuning(
    Tuning &tuning, integer_t tones_count) const
{
    std::vector<Ratio> ratios{sample_weighted(tuning, tones_count)};
    
    return ratios;
}

void PaletteGenerator::sort_ratios(std::vector<Ratio> &harmonic_ratios)
{
    auto compare_ratios = [](Ratio &r1, Ratio &r2)
    {
        return r1.get_frequency_factor() < r2.get_frequency_factor();
    };

    std::sort(harmonic_ratios.begin(), harmonic_ratios.end(), compare_ratios);
}

Palette PaletteGenerator::generate(
    Tuning &tuning, integer_t tones_count) const
{
    std::vector<Ratio> palette_ratios{sample_ratios_from_tuning(
        tuning, tones_count)};

    Tone base_tone{base_frequency_};
    Palette palette{};

    sort_ratios(palette_ratios);

    std::for_each(palette_ratios.begin(), palette_ratios.end(),
        [&palette, this](const Ratio& ratio){
            palette.tones_.emplace_back(base_frequency_, ratio);
        });

    std::for_each(palette.tones_.begin(), palette.tones_.end(),
        [&palette, this](Tone &tone){
            tone.ratio_ = unisonic_widen(tone.ratio_);
        }); 

    return palette;
}

}