#pragma once

#include "Patient.hpp"
#include <string>
#include <vector>
#include <unordered_map>


class CareUnit
{
public:
    explicit CareUnit(const std::string &name);

    const std::string &getServiceName() const;

    /**
     * procedurally generates a patient's info and calls addPatient(name, gender, age, height, weight) to add him to the hashmaps
     * */
    void addPatient();

    /**
     * Removes a patient from the patients hashmaps by their id
     * */
    void removePatient(uint64_t id);


    /**
     * @returns a const reference to a patient using their name
     * */
    const Patient &getpatient(const std::string &name) const;


    /**
     * @returns a const reference to a patient using their ID
     * */
    const Patient &getpatient(uint64_t id) const;


    /**
     * @returns a const reference to the patients in an array
     * @attention NOT SURE ABOUT THIS, might be used when printing the list of patients
     * */
    const std::vector<Patient> &getPatients() const;

private:
    // name of the service the care unit belongs to, must be initialized
    const std::string _serviceName;

//    // list of _patients that are under the current service
//    std::vector<Patient> _patients;

    // a hashmap that maps each patient's id to their name
    std::unordered_map<uint64_t, std::string> _idToName;

    // a hashmap that maps each patient's name to their Patient object
    std::unordered_map<std::string, Patient> _nameToPatient;


    /**
     * Adds a new patient to the patients hashmaps
     * */
    void addPatient(const std::string &name, uint8_t gender, uint8_t age, uint8_t height, uint16_t weight);


};
