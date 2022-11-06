#include <algorithm>
#include "CareUnit.hpp"

CareUnit::CareUnit(const std::string &name)
        : _serviceName(name)
{}

void CareUnit::addPatient(const std::string &name, uint8_t gender, uint8_t age, uint8_t height, uint16_t weight)
{

}

void CareUnit::removePatient(uint64_t id)
{

}

const std::string &CareUnit::getServiceName() const
{
    return _serviceName;
}

const std::vector<Patient> &CareUnit::getPatients() const
{

}
