
#include <sstream>
#include "Data.hpp"
#include "Utils.hpp"


PatientData DataSets::generatePatientData()
{
    // 1/2 proba of generating male, 1/2 for female
    int num = Utils::rng(10);

    int randomLastNameIndex = Utils::rng(lastNames.size());
    std::string lastName = lastNames[randomLastNameIndex];

    if (num >= 5)
    {
        // generate male
        int randomNameIndex = Utils::rng(maleNames.size());
        std::string firstName = maleNames[randomNameIndex];

        uint8_t gender = 'm';

        std::string fullName = firstName + " " + lastName;

        return {fullName, gender};
    } else
    {
        // generate female
        int randomNameIndex = Utils::rng(femaleNames.size());
        std::string firstName = femaleNames[randomNameIndex];

        uint8_t gender = 'f';

        std::string fullName = firstName + " " + lastName;

        return {fullName, gender};
    }
}

DataSets::DataSets()
{
    // read name csv file
    std::ifstream file("data/names.csv", std::ios::in);

    std::string line;

    // dummy getline to get rid of the head row of the csv
    std::getline(file, line);

    // reading the data rows from the csv
    while (std::getline(file, line))
    {
        // making a string stream from the current line
        std::stringstream lineStream(line);

        // storage variables to use later
        std::string fname, lname, gender;


        // line: firstname,lastname,gender

        // reading first name:
        std::getline(lineStream, fname, ',');
        // reading last name:
        std::getline(lineStream, lname, ',');
        // reading gender:
        std::getline(lineStream, gender);

        if (gender == "Male")
        {
            maleNames.push_back(fname);
        } else if (gender == "Female")
        {
            femaleNames.push_back(fname);
        }

        lastNames.push_back(lname);
    }

    file.close();
}