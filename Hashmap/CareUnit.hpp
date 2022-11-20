#pragma once

#include "Patient.hpp"
#include <string>
#include <vector>
#include <chrono>
#include <random>
#include <cassert>
#include <unordered_map>
#include <map>


//typedef std::unordered_map<std::string, Patient *>::iterator patientsIterator;

class CareUnit
{
public:
    explicit CareUnit(const std::string &name);

    const std::string &getServiceName() const;


    /**
     * @brief procedurally generates a patient's info and calls addRandomPatient(name, gender, age, height, weight) to add him to the hashmaps
     * */
    void addRandomPatient();


    /*
    * Adds a patient from an existing patient object
    */
    void addPatient(const Patient &patient);


    /**
    * @brief Adds a new patient to the patients hashmaps
    * */
    void addPatient(const std::string &name, uint8_t gender, uint8_t age, uint8_t height, uint16_t weight);

    /**
     * Removes a patient from the patients hashmaps by their id
     * */
    void removePatient(uint64_t id);


    bool hasPatients() const;


    /**
     * @returns a const reference to a patient using their name
     * */
    Patient &getPatient(const std::string &name);


    /**
     * @returns a const reference to a patient using their ID
     * */
    Patient &getPatient(uint64_t id);


    /**
     * @returns a reference to the patients in a hashmap
     * @attention NOT SURE ABOUT THIS, might be used when printing the list of patients
     * */
    std::unordered_map<std::string, Patient> &getPatients();


    size_t getPatientsCount() const;


    /**
    * procedurally adds new patients, releases ones, and marks ones as dead (thus removed from the record)
    * this function is ran by the update() method in Hospital.hpp
    * */
    void update();


private:
    // name of the service the care unit belongs to, must be initialized
    const std::string _serviceName;


    // a hashmap that maps each patient's id to their name
    std::unordered_map<uint64_t, std::string> _idToName;


    // a hashmap that maps each patient's name to their Patient object
    std::unordered_map<std::string, Patient> _nameToPatient;




    // https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2003/n1456.html

};
