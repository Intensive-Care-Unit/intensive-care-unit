
#include "State.hpp"
#include "Utils.hpp"

Hospital *State::getHospital()
{
    if (!hospital)
    {
        hospital = new Hospital;
    }

    return hospital;
}

Hospital *State::hospital = nullptr;

State::Data *State::data = nullptr;

PatientData State::generatePatientData()
{
    // 1/2 proba of generating male, 1/2 for female
    int num = Utils::rng(10);

    if (num >= 5)
    {
        // generate male
        int randomNameIndex = Utils::rng(data->maleNames.size());
        std::string firstName = data->maleNames[randomNameIndex];

        int randomLastNameIndex = Utils::rng(data->lastNames.size());
        std::string lastName = data->maleNames[randomLastNameIndex];

        uint8_t gender = 1;

        std::string fullName = firstName + " " + lastName;

        return {fullName, gender};
    } else
    {
        // generate female
        int randomNameIndex = Utils::rng(data->femaleNames.size());
        std::string firstName = data->femaleNames[randomNameIndex];

        int randomLastNameIndex = Utils::rng(data->lastNames.size());
        std::string lastName = data->femaleNames[randomLastNameIndex];

        uint8_t gender = 0;

        std::string fullName = firstName + " " + lastName;

        return {fullName, gender};
    }
}
