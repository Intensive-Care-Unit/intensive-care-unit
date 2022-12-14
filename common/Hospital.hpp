/** Mohammed Iyad Benkhaled **/
#pragma once

#include "CareUnit.hpp"
#include <vector>

// Hospital class
//
// ******************PUBLIC OPERATIONS*********************
// bool addUnit( unit )              --> Add unit to the _hospital
// CareUnit getServiceUnit( name )   --> Get CareUnit object
// CareUnit getCriticalUnit( )       --> Get Critical Care Unit's object
// vector<CareUnit> getUnits( )      --> Get vector of all units present in the _hospital

class Hospital
{
public:
    /**
     * Initializes the _hospital object
     * Creates the critical service unit and pushes it to the array of services
     * */
    explicit Hospital();

    /**
     * O(1) on average
     * Adds a new unit to the services array if it doesn't already exist
     * @param unit: name of the unit that will be added to the services
     * @return true if adding unit was successful, otherwise false
     * */
    bool addUnit(const std::string &unit);


    /**
     * O(number of units)
     * returns a const reference to a requested unit
     * @param name: name of the service unit
     * @returns const reference to CareUnit object that has the given name
     * */
    CareUnit &getServiceUnit(const std::string &name);


    /**
     * O(1)
     * @return first element of _services
     * */
    CareUnit &getCriticalUnit();

    /**
     * O(1)
     * @return a vector of the units' present in the _hospital
     * */
    std::vector<CareUnit> &getUnits();


    /**
     * a function that runs in a different thread, it runs a loop to go through all CareUnit objects in _services and for each one, it procedurally adds/removes _patients, as well as adds new measurements to their history, runs in a constant interval of time
     * */
    void update();


private:
    // array of the care units, index 0 is the critical unit object
    std::vector<CareUnit> _serviceUnits;

};