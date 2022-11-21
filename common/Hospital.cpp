
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
//    auto it = _serviceUnits.find(name);
//
//    // if it already exists, we return
//    if (it != _serviceUnits.end())
//    {
//        return false;
//    }
//
//    _serviceUnits.insert(std::make_pair(name, CareUnit(name)));
//
//    return true;

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
//    auto it = _serviceUnits.find(name);
//
//    if (it != _serviceUnits.end())
//    {
//        return (*it).second;
//    } else
//    {
//        throw std::runtime_error("service not found");
//    }


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
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
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

