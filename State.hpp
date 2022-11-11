
#pragma once

#include "Hospital.hpp"
#include "Data.hpp"
#include <utility>
#include <vector>
#include <string>
#include <fstream>


//TODO move PatientData and DataSets classes to a separate file



class State
{
public:
    /**
     * @returns static hospital instance pointer
     */
    static Hospital *getHospital();


    /**
 * @returns static hospital instance pointer
 */
    static DataSets *getData();


    /**
     * State can't be cloned
     */
    State(State &other) = delete;


    /**
     * State can't be assigned
     */
    void operator=(const State &) = delete;

private:
    static DataSets *data;


    // private default constructor to prevent creating multiple instances
    explicit State() = default;

    // static hospital pointer, gets initialized by getHospital only once
    static Hospital *hospital;


};
