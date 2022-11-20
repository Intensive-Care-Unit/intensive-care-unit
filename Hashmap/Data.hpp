
#pragma once


#include <utility>
#include <vector>
#include <string>
#include <fstream>
#include "Hospital.hpp"

struct PatientData
{
    PatientData(std::string n, uint8_t g)
            :
            name(std::move(n))
            , gender(g)
    {}

    std::string name;
    uint8_t gender;
};

struct DataSets
{
    explicit DataSets();


    /**
    * @returns a randomly generated patient name and gender
    */
    PatientData generatePatientData();

    // we'll use these to generate gendered random patient names
    std::vector<std::string> maleNames;
    std::vector<std::string> femaleNames;
    std::vector<std::string> lastNames;
};
