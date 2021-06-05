#include "random.hpp"

namespace komposto
{

std::mt19937& Random::get_engine()
{
    static std::random_device device;
    static std::mt19937 engine(device());

    return engine;
}

}