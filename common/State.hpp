#pragma once

#include "Hospital.hpp"
#include "Data.hpp"
#include <utility>
#include <vector>
#include <string>
#include <fstream>

// State class
// 
// used for state management during the execution of the main driver program
//
class State
{
public:
    /**
     * @returns static _hospital instance pointer (singleton)
     */
    static Hospital *getHospital();


    /**
 * @returns static Dataset instance pointer (singleton)
 */
    static DataSets *getData();


    /**
     * State can't be cloned
     */
    State(State &other) = delete;


    /**
     * State can't be assigned (to preserve singleton behaviour)
     */
    void operator=(const State &) = delete;

private:
    // static _data pointer, gets initialized by getData only once
    static DataSets *_data;

    // private default constructor to prevent creating multiple instances (to preserve singleton behaviour)
    explicit State() = default;

    // static _hospital pointer, gets initialized by getHospital only once
    static Hospital *_hospital;
};