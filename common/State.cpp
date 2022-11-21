/** Mohammed Iyad Benkhaled **/

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
    if (!_hospital)
    {
        _hospital = new Hospital;
    }

    return _hospital;
}

Hospital *State::_hospital = nullptr;

DataSets *State::_data = nullptr;

DataSets *State::getData()
{
    if (!_data)
    {
        _data = new DataSets;
    }

    return _data;
}
