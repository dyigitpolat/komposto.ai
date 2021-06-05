#pragma once

#include <random>

namespace komposto
{

class Random
{
public:
    static std::mt19937& get_engine();
};

}