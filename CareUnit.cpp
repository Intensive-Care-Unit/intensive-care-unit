#include <algorithm>
#include "CareUnit.hpp"

CareUnit::CareUnit(const std::string &name)
        : _serviceName(name)
{}

Patient CareUnit::addPatient(const std::string &name, uint8_t gender, uint8_t age, uint8_t height, uint16_t weight)
{
    // https://yasenh.github.io/post/cpp-diary-1-emplace_back/
    this->patients.emplace_back(name, gender, age, height, weight);

    return this->patients.back();
}

void CareUnit::removePatient(uint64_t id)
{
    for (int i = 0; i < patients.size(); i++) // O(n)
    {
        // since "id" is the timestamp of patient creation, then we can consider our patient's array ordered by "id", so if the provided "id" is greater than the current patient's id, we'll be sure that this patient doesn't exist
        if (patients[i].getId() < id)
        {
            return;
        } else if (patients[i].getId() == id)
        {
            // erasing the patient when they exist
            patients.erase(patients.begin() + i); // O(n)
            return;
        }
    }

    // total: O(n²)  --> can it be improved ??
}

const std::string &CareUnit::getServiceName() const
{
    return _serviceName;
}

const std::vector<Patient> &CareUnit::getPatients() const
{
    return patients;
}
