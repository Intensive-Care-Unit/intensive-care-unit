#include <iostream>
#include "State.hpp"
#include "Data.hpp"

/***
 *
 * Implementation file for State Class
 *
 * * */

Hospital *State::getHospital()
{
    if (!hospital)
    {
        hospital = new Hospital;
    }

    return hospital;
}

Hospital *State::hospital = nullptr;

DataSets *State::data = nullptr;

DataSets *State::getData()
{
    if (!data)
    {
        data = new DataSets;
    }

    return data;
}

