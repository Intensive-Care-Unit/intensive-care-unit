
#pragma once

#include "Hospital.hpp"
#include "Data.hpp"
#include <utility>
#include <vector>
#include <string>
#include <fstream>


class State
{
public:
    /**
     * @returns static hospital instance pointer
     */
    static Hospital *getHospital();


    /**
 * @returns static Dataset instance pointer
 */
    static DataSets *getData();


    /**
     * State can't be cloned
     */
    State(State &) = delete;


    /**
     * State can't be assigned
     */
    void operator=(const State &) = delete;

private:


    // private default constructor to prevent creating multiple instances
    explicit State() = default;

    // static hospital pointer, gets initialized by getHospital only once, behaves as a singleton
    static Hospital *hospital;


    // static Dataset pointer, initialized as a acts as a singleton
    static DataSets *data;
};
