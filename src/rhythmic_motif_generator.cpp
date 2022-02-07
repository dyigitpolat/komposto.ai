#include "rhythmic_motif_generator.hpp"
#include "random.hpp"

#include <algorithm>

namespace rng = std::ranges;


namespace komposto
{

integer_t RhythmicMotifGenerator::get_random_divisor()
{
    std::discrete_distribution<> distribution(
        {
        1./2.,  // 1
        1./4.,  // 2
        1./8.,  // 3
        1./16., // 4
        1./16.  // 5
        });
    
    return distribution(Random::get_engine()) + 1;
}

RhythmicMotif RhythmicMotifGenerator::generate(integer_t beats) const
{
    std::vector<integer_t> sub_divisors(beats);

    rng::generate(sub_divisors, get_random_divisor);

    RhythmicMotif motif{beats};
    timestamp_beats_t start_time{};

    rng::for_each(sub_divisors,
        [&motif, &start_time](integer_t divisor){
            duration_beats_t duration{1./divisor};
            while(divisor-- > 0)
            {
                motif.timings_.emplace_back(start_time, duration);
                start_time += duration;
            }
    });

    return motif;
}


}