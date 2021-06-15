#include "ratio.hpp"

namespace komposto
{

frequency_t Ratio::get_frequency_factor() const
{
    return
        static_cast<frequency_t>(numerator_) /
        static_cast<frequency_t>(denominator_);
}

bool operator==(const Ratio& ratio1, const Ratio& ratio2)
{
    bool numerators_are_equal = ratio1.numerator_ == ratio2.numerator_;
    bool denominators_are_equal = ratio1.denominator_ == ratio2.denominator_;
    
    return numerators_are_equal and denominators_are_equal;
}

Ratio operator*(const Ratio& ratio1, const Ratio& ratio2)
{
    numerator_t numerator = ratio1.numerator_ * ratio2.numerator_;
    denominator_t denominator = ratio1.denominator_ * ratio2.denominator_;
    
    return Ratio{numerator, denominator};
}

frequency_t operator*(const Ratio& ratio, const frequency_t& frequency)
{
    return frequency * ratio.get_frequency_factor();
}

frequency_t operator*(const frequency_t& frequency, const Ratio& ratio)
{
    return ratio * frequency;
}

}
