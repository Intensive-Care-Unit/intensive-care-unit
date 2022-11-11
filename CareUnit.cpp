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
  _nameToPatient.insert(std::make_pair(patient.getName(), patient));
  _idToName[patient.getId()] = patient.getName();
}


void CareUnit::removePatient(uint64_t id)
{
  std::string name = _idToName[id];
  _nameToPatient.erase(name);
  _idToName.erase(id);
}

const std::string &CareUnit::getServiceName() const
{
    return _serviceName;
}

const std::vector<Patient> &CareUnit::getPatients() const
{
  std::vector<Patient> unitPatients;
  for (auto patient : _nameToPatient){
    unitPatients.push_back(patient.second);
  }
  
  return unitPatients;
}

void CareUnit::addPatient()
{
  //TODO
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
        addPatient();
        addPatient();
        addPatient();
    }


    // probability of 3/10 to remove 1 random patient (dead or released)
    randomNum = Utils::rng(10);
    if (randomNum < 3)
    {
        // removing the patient after getting their idIndex randomly
        uint64_t idIndex = Utils::rng(_patientsIds.size());

        if (_patientsIds[idIndex] != -1)  // to make sure the patient isn't already deleted
        {
            removePatient(_patientsIds[idIndex]);

            // adding the removed index to the _deletedPatientsIndexes DLL
            _deletedPatientsIndexes.emplace_front(idIndex);
        }
    }

    // when number of patient exceeds 10, there is a probability of 4/10 that 10% of the patients get moved to critical unit
    if (_idToName.size() >= 10 && _serviceName != State::getHospital()->getCriticalUnit()._serviceName)
    {
        randomNum = Utils::rng(10);

        if (randomNum < 4)
        {
            int tenthOfPatientsCount = _idToName.size() / 10;
            for (int i = 0; i < tenthOfPatientsCount; ++i)
            {
                int index = Utils::rng(_patientsIds.size());

                // checking if patient at index is already deleted
                if (_patientsIds[index] == -1)
                {
                    --i;
                    continue;
                } else
                {

                    //TODO move this code to "moveToCritical()" function in Patient class
                    // we move the patient to critical unit
                    auto hospital = State::getHospital();

                    std::string patientName = _idToName[_patientsIds[index]];

                    Patient patient = _nameToPatient.find(patientName)->second;

                    // adding the patient to the critical unit
                    hospital->getCriticalUnit().addPatient(patient);

                    // removing the patient from the current unit
                    this->removePatient(_patientsIds[index]);
                }
            }
        }
    }

    // updating all the patient's objects
    for (auto &patientId: _patientsIds)
    {
        if (patientId != -1) // if patient isn't marked as deleted
        {
            // getting the name of the current patient from the (id -> name)  Hashmap
            std::string name = _idToName[patientId];

            // getting the Patient object from (name -> Patient) Hashmap
            auto patient = _nameToPatient.find(name)->second;

            // running the update method of the patient
            patient.update();
        }
    }
}
