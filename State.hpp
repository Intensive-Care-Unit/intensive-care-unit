
#pragma once

#include "Hospital.hpp"

class State
{
public:
    /**
     * @return the same hospital instance pointer everytime
     */
    static Hospital *getHospital();

    /**
     * State can't be cloned
     */
    State(State &other) = delete;

    
    /**
     * State can't be assigned
     */
    void operator=(const State &) = delete;

private:
    // private default constructor to prevent creating multiple instances
    explicit State() = default;

    // static hospital pointer, gets initialized by getHospital only once
    static Hospital *hospital;
};
