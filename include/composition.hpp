#pragma once

#include "section.hpp"

#include <vector>

namespace komposto
{

class Composition
{
public:
    std::vector<Section> sections_;

public:
    std::vector<Note> get_notes() const;
};

}
