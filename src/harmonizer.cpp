#include "harmonizer.hpp"

#include "constants.hpp"
#include "random.hpp"

#include <vector>
#include <algorithm>

namespace komposto
{

enum class Direction
{
    k__up = 0,
    k__down = 1
};

const Tone& Harmonizer::pick_tone(
    const Palette &palette, const Tone &previous_tone)
{
    std::discrete_distribution<> distribution(
        {k__half, k__half});

    auto previous_tone_iter = std::find_if(
        palette.tones_.cbegin(), palette.tones_.cend(), 
        [&previous_tone](const Tone &t)
        {
            return t.ratio_ == previous_tone.ratio_;
        });
    
    bool tone_not_found{previous_tone_iter == palette.tones_.cend()};
    
    if(tone_not_found)
    {
        return palette.tones_[0];
    }

    Direction direction{distribution(Random::get_engine())};

    bool is_lower_bound{previous_tone_iter == palette.tones_.cbegin()};
    bool is_upper_bound{previous_tone_iter == std::prev(palette.tones_.cend())};

    if(Direction::k__up == direction && is_upper_bound)
    {
        direction = Direction::k__down;
    }

    if(Direction::k__down == direction && is_lower_bound)
    {
        direction = Direction::k__up;
    }

    if(Direction::k__up == direction)
    {
       return *(std::next(previous_tone_iter));
    }
    else if(Direction::k__down == direction)
    {
       return *(std::prev(previous_tone_iter));
    }
    else
    {
        return *previous_tone_iter;
    }
}

Tuning Harmonizer::get_5_limit_tuning()
{
    const std::vector<Ratio> limit_5_tuning {
        Ratio{1,1}, Ratio{5,4}, Ratio{3,2},
        Ratio{8,5}, Ratio{1,1}, Ratio{6,5},
        Ratio{4,3}, Ratio{5,3}, Ratio{1,1}
    };

    return Tuning{limit_5_tuning};
}

Tuning Harmonizer::get_7_limit_tuning()
{
    const std::vector<Ratio> limit_7_tuning {
        Ratio{1,1}, Ratio{5,4},  Ratio{3,2},  Ratio{7,4},
        Ratio{8,5}, Ratio{1,1},  Ratio{6,5},  Ratio{7,5},
        Ratio{4,3}, Ratio{5,3},  Ratio{1,1},  Ratio{7,6},
        Ratio{8,7}, Ratio{10,7}, Ratio{12,7}, Ratio{1,1},
    };

    return Tuning{limit_7_tuning};
}

Tuning Harmonizer::get_11_limit_tuning()
{
    using R = Ratio;
    const std::vector<Ratio> limit_11_tuning {
        R{1,1},   R{9,8},   R{5,4},   R{11,8},  R{3,2},   R{7,4},
        R{16,9},  R{1,1},   R{10,9},  R{11,9},  R{12,9},  R{14,9},
        R{8,5},   R{9,5},   R{1,1},   R{11,10}, R{6,5},   R{7,5},
        R{16,11}, R{18,11}, R{20,11}, R{1,1},   R{12,11}, R{14,11},
        R{4,3},   R{9,6},   R{5,3},   R{11,6},  R{1,1},   R{7,6},
        R{8,7},   R{9,7},   R{10,7},  R{11,7},  R{12,7},  R{1,1}
    };

    return Tuning{limit_11_tuning};
}


Tuning Harmonizer::get_just_major_tuning()
{
    using R = Ratio;
    const std::vector<Ratio> just_major {
        R{1,1}, R{9,8}, R{5,4}, R{4,3}, R{3,2}, R{5,3}, R{18,8}, R{2,1}
    };

    return Tuning{just_major};
}

Tuning Harmonizer::get_just_minor_tuning()
{
    using R = Ratio;
    const std::vector<Ratio> just_minor {
        R{1,1}, R{9,8}, R{6,5}, R{4,3}, R{3,2}, R{8,5}, R{9,5}, R{2,1}
    };

    return Tuning{just_minor};
}

Tuning Harmonizer::get_just_harmonic_minor_tuning()
{
    using R = Ratio;
    const std::vector<Ratio> just_harmonic_minor {
        R{1,1}, R{9,8}, R{6,5}, R{4,3}, R{3,2}, R{8,5}, R{7,4}, R{2,1}
    };

    return Tuning{just_harmonic_minor};
}

Tuning Harmonizer::get_just_grave_minor_tuning()
{
    using R = Ratio;
    const std::vector<Ratio> just_grave_minor {
        R{1,1}, R{9,8}, R{6,5}, R{4,3}, R{3,2}, R{8,5}, R{16,9}, R{2,1}
    };

    return Tuning{just_grave_minor};
}

Tuning Harmonizer::get_pythagorean_tuning(integer_t notes_count)
{
    using R = Ratio;
    std::vector<Ratio> pythagorean(notes_count);
    
    R current_ratio = R{1,1};
    for(R &target_ratio : pythagorean)
    {
        target_ratio = current_ratio;
        current_ratio = current_ratio * R{3,2};
    }

    for(R &target_ratio : pythagorean)
    {
        while(target_ratio.get_frequency_factor() > 2.0)
        {
            target_ratio = target_ratio * R{1,2};
        }
    }

    return Tuning{pythagorean};
}

Tuning Harmonizer::get_p_limit_tuning(integer_t prime_p)
{
    if(prime_p >= 11) return get_11_limit_tuning();
    if(prime_p >= 7) return get_7_limit_tuning();

    return get_5_limit_tuning();
}

}