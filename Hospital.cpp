
#include "Hospital.hpp"
#include <stdexcept>
#include <algorithm>
#include <thread>
#include <chrono>
#include <iostream>


Hospital::Hospital()
{
    // adding default units
    addUnit("critical");
    addUnit("cardiology");
    addUnit("pulmonology");
    addUnit("gynaecology");
}


bool Hospital::addUnit(const std::string &name)
{
    auto it = _serviceUnits.find(name);

    // if it already exists, we return
    if (it != _serviceUnits.end())
    {
        return false;
    }

    _serviceUnits.insert(std::make_pair(name, CareUnit(name)));

    return true;
}


CareUnit &Hospital::getServiceUnit(const std::string &name)
{
    auto it = _serviceUnits.find(name);

    if (it != _serviceUnits.end())
    {
        return (*it).second;
    } else
    {
        throw std::runtime_error("service not found");
    }
}


void Hospital::update()
{
    while (true)
    {

        /**
         * For each service:
         *  - there is a 1/2 chance that a new patient will be added
         *  - for each patient, add a new generated measurement to their history
         * */

        for (auto &service: _serviceUnits)
        {
            service.second.update();
        }

        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
}


bool Hospital::removeUnit(const std::string &name)
{

    if (_serviceUnits.size() == 2)
    {
        return false; // TODO: throw EnoughUnitsException instead
    }

    auto it = _serviceUnits.find(name);

    // if unit exists
    if (it != _serviceUnits.end())
    {
        if ((*it).second.hasPatients())
        {
            return false; // TODO throw HasPatientsException instead
        } else
        {
            _serviceUnits.erase(name);
        }
    } else
    {
        return false; // TODO: throw PatientDoesntExistException instead
    }
}


CareUnit &Hospital::getCriticalUnit()
{
    return _serviceUnits.at("critical");
}

