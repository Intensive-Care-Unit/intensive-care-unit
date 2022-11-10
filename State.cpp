
#include "State.hpp"

Hospital *State::getHospital()
{
    if (!hospital)
    {
        hospital = new Hospital;
    }

    return hospital;
}

