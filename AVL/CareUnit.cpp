#include <algorithm>
#include<vector>
#include "Patient.hpp"
#include "CareUnit.hpp"
#include "State.hpp"
#include "Utils.hpp"


CareUnit::CareUnit(const std::string &name)
        : _serviceName(name)
{}

void CareUnit::addPatient(const std::string &name, uint8_t gender, uint8_t age, uint8_t height, uint16_t weight)
{
    Patient p = Patient(_serviceName, name, gender, age, height, weight);
    addPatient(p);
}

void CareUnit::addPatient(const Patient &patient)
{
    _nameToPatient.insert(patient.getName(), patient);
    _idToName.insert(patient.getId(), patient.getName());
}


void CareUnit::removePatient(uint64_t id)
{
    std::string name = _idToName.at(id);
    _nameToPatient.remove(name);
    _idToName.remove(id);
}

const std::string &CareUnit::getServiceName() const
{
    return _serviceName;
}

const std::vector<Patient> &CareUnit::getPatients() const
{
    return _nameToPatient.toVector();
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
    bool isKid = age > 5 && age <= 12; // weight from 17 to 45kg, height 110-150
    bool isTeen = age > 12 && age < 18; // weight from 40 to 65, height 150-170
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

const Patient &CareUnit::getPatient(const std::string &name) const
{
    return _nameToPatient.at(name);
}

const Patient &CareUnit::getPatient(uint64_t id) const
{
    return getPatient(_idToName.at(id));
}


void CareUnit::update()
{
    // probability of 1/2 to add 3 patients
    int randomNum = Utils::rng(10);
    if (randomNum >= 5) // add 3 patients
    {
        addRandomPatient();
        addRandomPatient();
        addRandomPatient();
    }

    // updating all the patient's objects
    auto vPatients = _nameToPatient.toVector();
    for (auto &patientPair: vPatients)
    {
        patientPair.update();
    }
}

bool CareUnit::hasPatients() const
{
    return !(_nameToPatient.isEmpty());
}
