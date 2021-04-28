#include "timing.hpp"

namespace komposto
{

timestamp_t Timing::get_start() const
{
    return start_;
}

timestamp_t Timing::get_end() const
{
    return start_ + duration_;
} 

duration_t Timing::get_duration() const
{
    return duration_;
}

}