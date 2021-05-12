#include "harmonizer.hpp"

#include <random>
#include <vector>

namespace komposto
{

const Tone& Harmonizer::pick_tone(const Palette &palette)
{
    static std::random_device device;
    static std::mt19937 engine(device());

    const int tones_count{static_cast<int>(palette.tones_.size())};
    std::uniform_int_distribution distribution{0, tones_count - 1};
    
    //pick random
    return palette.tones_[ distribution(engine) ];
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

Tuning Harmonizer::get_p_limit_tuning(integer_t prime_p)
{
    if(prime_p >= 11) return get_11_limit_tuning();
    if(prime_p >= 7) return get_7_limit_tuning();

    return get_5_limit_tuning();
}

}