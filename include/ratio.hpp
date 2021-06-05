#pragma once

#include "komposto_types.hpp"

namespace komposto
{

class Ratio
{
public:
    numerator_t numerator_;
    denominator_t denominator_;

public:
    Ratio(numerator_t numerator = 1, denominator_t denominator = 1) :
        numerator_(numerator),
        denominator_(denominator)
    {}

    frequency_t get_frequency_factor() const;
};

bool operator==(const Ratio& ratio1, const Ratio& ratio2);
Ratio operator*(const Ratio& ratio1, const Ratio& ratio2);
frequency_t operator*(const Ratio& ratio, const frequency_t& frequency);
frequency_t operator*(const frequency_t& frequency, const Ratio& ratio);

}