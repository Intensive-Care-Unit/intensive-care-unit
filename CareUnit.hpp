#pragma once

#include "Patient.hpp"
#include <string>
#include <vector>
#include <chrono>
#include <random>
#include <cassert>
#include <unordered_map>


class CareUnit
{
public:
    explicit CareUnit(const std::string &name);

    const std::string &getServiceName() const;

    /**
     * procedurally adds new patients, releases ones, and marks ones as dead (thus removed from the record)
     * this function is ran by the update() method in Hospital.hpp
     * */
    void update();

    /**
     * @brief procedurally generates a patient's info and calls addRandomPatient(name, gender, age, height, weight) to add him to the hashmaps
     * */
    void addRandomPatient();


    /*
 * Adds a patient from an existing patient object
 */
    void addPatient(const Patient &patient);


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


    // a hashmap that maps each patient's id to their name
    std::unordered_map<uint64_t, std::string> _idToName;


    // a hashmap that maps each patient's name to their Patient object
    std::unordered_map<std::string, Patient> _nameToPatient;


    // https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2003/n1456.html


// TODO remove lazy deletion stuff from update() methods
//    // a vector array of the patient's IDS, we'll use it to traverse the patients in order to update them or print them in O(n) time
//    // if a patient is deleted, their ID is turned into -1 (for lazy deletion)
//    // we'll keep the indexes of the deleted patients in a linked list (below) to insert new patients into the deleted positions
//    std::vector<uint64_t> _patientsIds;
//
//
//    // doubly linked list of the deleted patients indexes in _patientsIds vector array
//    std::list<size_t> _deletedPatientsIndexes;





/****************** Utilities ***********************/

    /**
     * @brief Adds a new patient to the patients hashmaps
     * @attention add patient's id to _patientIds array taking into consideration _deletedPatientsIndexes
     * */
    void addPatient(const std::string &name, uint8_t gender, uint8_t age, uint8_t height, uint16_t weight);


};
