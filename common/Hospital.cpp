/** Mohammed Iyad Benkhaled **/
#include "Hospital.hpp"
#include <stdexcept>
#include <algorithm>
#include <thread>
#include <chrono>
#include <iostream>

/***
 *
 * Implementation file for Hospital Class
 *
 * * */

Hospital::Hospital()
{
    // adding default units
    addUnit("critical");
    addUnit("cardiology");
    addUnit("pulmonology");
    addUnit("gynecology");
}


bool Hospital::addUnit(const std::string &name)
{

    for (auto &unit: _serviceUnits)
    {
        if (unit.getServiceName() == name)
        {
            return false;
        }
    }

    _serviceUnits.emplace_back(name);

    return true;

}


CareUnit &Hospital::getServiceUnit(const std::string &name)
{

    for (auto &_serviceUnit: _serviceUnits)
    {
        if (_serviceUnit.getServiceName() == name)
        {
            return _serviceUnit;
        }
    }

    throw std::runtime_error("service unit not found");

}


void Hospital::update()
{
    try
    {
        while (true)
        {
            for (auto &service: _serviceUnits)
            {
                service.update();
            }
            std::this_thread::sleep_for(std::chrono::seconds(2));
        }
    }
    catch (std::runtime_error &e)
    {
        std::cout << e.what() << std::endl;
    }
}


CareUnit &Hospital::getCriticalUnit()
{
    return _serviceUnits[0];
}

std::vector<CareUnit> &Hospital::getUnits()
{
    return _serviceUnits;
}
