
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
    try
    {
        while (true)
        {
            size_t count = 0;
            for (auto &service: _serviceUnits)
            {
                count += service.second.getPatientsCount();
                service.second.update();
            }

            system("clear");
            std::cout << "count: " << count << std::endl;


            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
    }
    catch (std::runtime_error &e)
    {
        std::cout << e.what() << std::endl;
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

std::vector<CareUnit> Hospital::getUnits()
{
    std::vector<CareUnit> out;

    for (auto &pair: _serviceUnits)
    {
        out.push_back(pair.second);
    }

    return out;
}

