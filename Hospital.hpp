#pragma once

#include "CareUnit.hpp"
#include <vector>

class Hospital
{
public:
    // initialize Hospital with at least Director


    bool addUnit(const std::string &unit);

    const CareUnit &getServiceUnit(const std::string &name);


private:
    std::vector<CareUnit> _services;


    // Director

    // array of staff

};


// TODO: make Staff classes