#pragma once

#include "CareUnit.hpp"
#include <vector>

class Hospital
{
public:

private:
    std::vector<CareUnit> _services;

    bool addUnit(const std::string &unit);

};
