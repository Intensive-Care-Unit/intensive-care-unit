#include <algorithm>
#include "CareUnit.hpp"
#include "State.hpp"

CareUnit::CareUnit(const std::string &name)
        : _serviceName(name)
{}

void CareUnit::addPatient(const std::string &name, uint8_t gender, uint8_t age, uint8_t height, uint16_t weight)
{

}

void CareUnit::addPatient(const Patient &patient)
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

void CareUnit::addPatient()
{

}

const Patient &CareUnit::getpatient(const std::string &name) const
{
}

const Patient &CareUnit::getpatient(uint64_t id) const
{
}

void CareUnit::update()
{
    // probability of 1/2 to add 3 patients
    int randomNum = rng(10);
    if (randomNum >= 5) // add 3 patients
    {
        addPatient();
        addPatient();
        addPatient();
    }


    // probability of 3/10 to remove 1 random patient (dead or released)
    randomNum = rng(10);
    if (randomNum < 3)
    {
        // removing the patient after getting their idIndex randomly
        uint64_t idIndex = rng(_patientsIds.size());

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
        randomNum = rng(10);

        if (randomNum < 4)
        {
            int tenthOfPatientsCount = _idToName.size() / 10;
            for (int i = 0; i < tenthOfPatientsCount; ++i)
            {
                int index = rng(_patientsIds.size());

                // checking if patient at index is already deleted
                if (_patientsIds[index] == -1)
                {
                    --i;
                    continue;
                } else
                {
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

int CareUnit::rng(int a)
{
    // assert aborts the program if the condition is not true
    assert(a > 0);

    auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();

    std::mt19937 num(seed);
    std::uniform_int_distribution<int> distr(0, a);

    return static_cast<int>(distr(num));
}

int CareUnit::rng(int a, int b)
{
    // assert aborts the program if the condition is not true
    assert(a < b);

    auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();

    std::mt19937 num(seed);
    std::uniform_int_distribution<int> distr(a, b);

    return static_cast<int>(distr(num));
}

