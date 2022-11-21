#include <algorithm>
#include <iostream>
#include "Patient.hpp"
#include "CareUnit.hpp"
#include "State.hpp"
#include "Utils.hpp"

/***
 *
 * Implementation file for CareUnit Class
 *
 * * */

CareUnit::CareUnit(const std::string &name)
        : _serviceName(name)
{}


void CareUnit::addPatient(const std::string &name, uint8_t gender, uint8_t age, uint8_t height, uint16_t weight)
{
    addPatient({_serviceName, name, gender, age, height, weight}); // Creates Patient object, and call addPatient( Patient )
}

void CareUnit::addPatient(const Patient &patient)
{
    // Insert required data to _idToName HashTable
    // Emplace is used because it is faster than insert
    // https://yasenh.github.io/post/cpp-diary-1-emplace_back/
    _idToName.emplace(patient.getId(), patient.getName());
    
    // Insert required data to _nameToPatient HashTable
    // Emplace is used because it is faster than insert
    _nameToPatient.emplace(patient.getName(), patient);
    
}

void CareUnit::removePatient(uint64_t id)
{
    auto it = _idToName.find(id);

    if (it != _idToName.end())
    {
        auto name = _idToName[id];

        auto it2 = _nameToPatient.find(name);

        if (it2 != _nameToPatient.end())
        {
            (*it2).second.remove(); // Call remove( ) function on the specified Patient object
            _idToName.erase(it);
        }
    }
}

const std::string &CareUnit::getServiceName() const
{
    return _serviceName;
}

std::unordered_map<std::string, Patient> &CareUnit::getPatients()
{
  return _nameToPatient;
}


void CareUnit::addRandomPatient()
{
    // generate patient info from dataset
    // generate random metadata (age, height, weight)
    // construct the patient and add them to the patients HMs

    PatientData patientInfo = State::getData()->generatePatientData();

    // generating age:
    uint8_t age = Utils::rng(200);

    uint8_t height, weight;

    bool isBaby = age <= 1; // weight from 2kg to 12kg, height 50-70
    bool isLittleKid = age > 1 && age <= 5; // weight from 10 to 22, height 70-110
    bool isKid = age > 5 && age <= 9; // weight from 17 to 45kg, height 110-150
    bool isTeen = age > 9 && age < 18; // weight from 40 to 65, height 150-170
    bool isAdult = age >= 18; // weight from 50 to 100, height 150 - 200

    if (isBaby)
    {
        weight = Utils::rng(2, 12);
        height = Utils::rng(50, 70);
    } else if (isLittleKid)
    {
        weight = Utils::rng(10, 22);
        height = Utils::rng(70, 110);
    } else if (isKid)
    {
        weight = Utils::rng(17, 45);
        height = Utils::rng(110, 150);
    } else if (isTeen)
    {
        weight = Utils::rng(40, 65);
        height = Utils::rng(150, 170);
    } else if (isAdult)
    {
        weight = Utils::rng(50, 100);
        height = Utils::rng(150, 200);
    }

    addPatient(patientInfo.name, patientInfo.gender, age, height, weight);

}


Patient &CareUnit::getPatient(const std::string &name)
{
    return _nameToPatient.at(name);
}


Patient &CareUnit::getPatient(uint64_t id)
{
    return getPatient(_idToName.at(id));
}


void CareUnit::update()
{

    //    // updating all the patient's objects
    for (auto &patientPair: _nameToPatient)
    {
        if (!(patientPair.second.isDeleted()))
        {
            patientPair.second.update();
        }
    }


    // probability of 3/5 to add 3 patients
    int randomNum = Utils::rng(100);
    if (randomNum >= 40) // add 3 patients
    {
        if (_serviceName != "critical")
        {
            addRandomPatient();
            addRandomPatient();
            addRandomPatient();
        }
    }





// TODO fix lazy deletion
    size_t countOfDeleted = _nameToPatient.size() - _idToName.size();
//    std::cout << "size of deleted: " << countOfDeleted << std::endl;
    if ((countOfDeleted * 2) >= _idToName.size())
    {
        auto it = _nameToPatient.cbegin();
        // we remove patients with the flag "isDeleted" set to true
        while (it != _nameToPatient.cend())
        {
            if ((*it).second.isDeleted())
            {
//                std::cout << "size before erase: " << _nameToPatient.size() << std::endl;
                it = _nameToPatient.erase(it);
//                std::cout << "size after erase: " << _nameToPatient.size() << std::endl;
            } else
            {
                ++it;
            }
        }
    }


}

bool CareUnit::hasPatients() const
{
    return !(_nameToPatient.empty());
}

size_t CareUnit::getPatientsCount() const
{
    return _idToName.size();
}

bool CareUnit::hasPatient(const std::string& name) {
    try {
        _nameToPatient.at(name);
        return true;
    } catch(const std::out_of_range& e)   {
        return false;
    }
}

bool CareUnit::hasPatient(uint64_t id) {
    try {
        _idToName.at(id);
        return true;
    } catch(const std::out_of_range& e)   {
        return false;
    }
}
