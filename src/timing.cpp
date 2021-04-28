#include "timing.hpp"

namespace komposto
{

inline timestamp_t Timing::get_end() const
{
    return start_ + duration_;
} 

}