#pragma once

#include "CareUnit.hpp"
#include <vector>
#include <unordered_map>

class Hospital
{
public:
    /**
     * Initializes the hospital object
     * Creates the critical service unit and pushes it to the array of services
     * */
    explicit Hospital();

    /**
     * Adds a new unit to the services array if it doesn't already exist
     * @param unit: name of the unit that will be added to the services
     * @return true if adding unit was successful, otherwise false
     * */
    bool addUnit(const std::string &unit);


    /**
     * Removes a unit from the services array if it doesn't have _patients
 * @param unit: name of the unit that will be removed from the services
 * @return true if removing unit was successful, otherwise false
 * */
    bool removeUnit(const std::string &unit);


    /**
     * returns a const reference to a requested unit
     * @param name: name of the service unit
     * @returns const reference to CareUnit object that has the given name
     * */
    CareUnit &getServiceUnit(const std::string &name);

    /**
     * @return first element of _services
     */
    CareUnit &getCriticalUnit();


    /**
     * a function that runs in a different thread, it runs a loop to go through all CareUnit objects in _services and for each one, it procedurally adds/removes _patients, as well as adds new measurements to their history, runs in a constant interval of time (//TODO define the interval that the function runs on)
     * */
    void update();


private:
    // array of the care units, index 0 is the critical unit object
//    std::vector<CareUnit> _services;


    // hashmap of CareUnits (hashed with their names)
    std::unordered_map<std::string, CareUnit> _serviceUnits;


    // TODO: comment functions after the ADT change

};
