#include "tone.hpp"

namespace komposto
{

inline frequency_t Tone::get_frequency() const
{
    return base_frequency_ * ratio_;
}

}
