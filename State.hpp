
#pragma once

#include "Hospital.hpp"
#include <utility>
#include <vector>
#include <string>
#include <fstream>


class PatientData
{
public:
    PatientData(std::string n, uint8_t g)
            :
            name(std::move(n))
            , gender(g)
    {}

private:
    std::string name;
    uint8_t gender;
};

class State
{
public:
    /**
     * @returns static hospital instance pointer
     */
    static Hospital *getHospital();


    /**
     * @returns a randomly generated patient name and gender
     */
    static PatientData generatePatientData();


    /**
     * State can't be cloned
     */
    State(State &other) = delete;


    /**
     * State can't be assigned
     */
    void operator=(const State &) = delete;

private:
    struct Data
    {
        Data()
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

                if (gender == "male")
                {
                    data->maleNames.push_back(fname);
                } else if (gender == "female")
                {
                    data->femaleNames.push_back(fname);
                }

                data->lastNames.push_back(lname);
            }

            file.close();
        }

        // we'll use these to generate random patient names
        std::vector<std::string> maleNames;
        std::vector<std::string> femaleNames;
        std::vector<std::string> lastNames;
    };


    static Data *data;


    // private default constructor to prevent creating multiple instances
    explicit State() = default;

    // static hospital pointer, gets initialized by getHospital only once
    static Hospital *hospital;


};
