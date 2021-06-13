#include "dynamics_generator.hpp"

#include "random.hpp"

#include <algorithm>

namespace komposto
{

Dynamics DynamicsGenerator::generate() const
{
    std::discrete_distribution<> distribution(
        {0.125, 0.25, 0.50, 0.125});
    
    floating_point_t velocity{
        (distribution(Random::get_engine()) + 1)
        / 4.0 
    };

    return Dynamics{velocity};
}

}