/** Mohammed Iyad Benkhaled **/

#pragma once

#include <utility>
#include <vector>
#include <string>
#include <fstream>
#include "Hospital.hpp"

//
// PatientData Struct used for getting patients' _data
//
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

//
// DataSets Struct used for _data generation
//
struct DataSets
{
    explicit DataSets();


    /**
* @returns a randomly generated patient name and gender
*/
    PatientData generatePatientData();

    // we'll use these to generate random patient names
    std::vector<std::string> maleNames;
    std::vector<std::string> femaleNames;
    std::vector<std::string> lastNames;
};