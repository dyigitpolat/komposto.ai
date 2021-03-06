#include "tuning_provider.hpp"

#include <vector>

namespace komposto
{

Tuning TuningProvider::get_5_limit_tuning()
{
    const std::vector<Ratio> limit_5_tuning {
        Ratio{1,1}, Ratio{5,4}, Ratio{3,2},
        Ratio{8,5}, Ratio{1,1}, Ratio{6,5},
        Ratio{4,3}, Ratio{5,3}, Ratio{1,1}
    };

    return Tuning{limit_5_tuning};
}

Tuning TuningProvider::get_7_limit_tuning()
{
    const std::vector<Ratio> limit_7_tuning {
        Ratio{1,1}, Ratio{5,4},  Ratio{3,2},  Ratio{7,4},
        Ratio{8,5}, Ratio{1,1},  Ratio{6,5},  Ratio{7,5},
        Ratio{4,3}, Ratio{5,3},  Ratio{1,1},  Ratio{7,6},
        Ratio{8,7}, Ratio{10,7}, Ratio{12,7}, Ratio{1,1},
    };

    return Tuning{limit_7_tuning};
}

Tuning TuningProvider::get_11_limit_tuning()
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


Tuning TuningProvider::get_just_major_tuning()
{
    using R = Ratio;
    const std::vector<Ratio> just_major {
        R{1,1}, R{9,8}, R{5,4}, R{4,3}, R{3,2}, R{5,3}, R{15,8}, R{2,1}
    };

    return Tuning{just_major};
}

Tuning TuningProvider::get_just_minor_tuning()
{
    using R = Ratio;
    const std::vector<Ratio> just_minor {
        R{1,1}, R{9,8}, R{6,5}, R{4,3}, R{3,2}, R{8,5}, R{9,5}, R{2,1}
    };

    return Tuning{just_minor};
}

Tuning TuningProvider::get_just_harmonic_minor_tuning()
{
    using R = Ratio;
    const std::vector<Ratio> just_harmonic_minor {
        R{1,1}, R{9,8}, R{6,5}, R{4,3}, R{3,2}, R{8,5}, R{7,4}, R{2,1}
    };

    return Tuning{just_harmonic_minor};
}

Tuning TuningProvider::get_just_grave_minor_tuning()
{
    using R = Ratio;
    const std::vector<Ratio> just_grave_minor {
        R{1,1}, R{9,8}, R{6,5}, R{4,3}, R{3,2}, R{8,5}, R{16,9}, R{2,1}
    };

    return Tuning{just_grave_minor};
}

Tuning TuningProvider::get_pythagorean_tuning(integer_t notes_count)
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

Tuning TuningProvider::get_p_limit_tuning(integer_t prime_p)
{
    if(prime_p >= 11) return get_11_limit_tuning();
    if(prime_p >= 7) return get_7_limit_tuning();

    return get_5_limit_tuning();
}

}