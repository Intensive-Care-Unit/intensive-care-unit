/** Mohammed Iyad Benkhaled **/

#pragma once

#include "Patient.hpp"
#include <string>
#include <vector>
#include <chrono>
#include <random>
#include <cassert>
#include <unordered_map>
#include <map>


// Care Unit class
//
// CONSTRUCTION: a name for the care unit (Same as name of the service in case of Intensive Care Unit)
//
// ******************PUBLIC OPERATIONS*********************
// string getServiceName( )                            --> Get the name of the unit
// void update( )                                      --> Update patients of the unit
// void addRandomPatient( )                            --> Randomly add patient
// void addPatient( patient )                          --> Add a patient to the unit
// void addPatient(name, gender, age, height, weight)  --> Add a patient to the unit (Using its information)
// bool hasPatients( )                                 --> Check that unit has patients 
// Patient getPatient( name )                          --> Search Patient by name
// Patient getPatient( id )                            --> Search Patient by ID
// unordered_map<string, Patient> getPatients( )  --> Get all patients of the unit
// size_t getPatientsCount( )                          --> Get number of patients in the unit
// bool hasPatient( name )                             --> Check if a patient exist, using the name
// bool hasPatient( id )                               --> Check if a patient exist, using the ID

class CareUnit
{
public:
    /**
     * @brief Constructor for CareUnit, requires the name of the unit
     * */
    explicit CareUnit(const std::string &name);

    /**
     * O(1)
     * @returns the name of the unit
     * */
    const std::string &getServiceName() const;

    /**
     * @brief procedurally adds new patients, releases ones, and marks ones as dead (thus removed from the record)
     * This function is ran by the update() method in Hospital.hpp
     * */
    void update();

    /**
     * @brief procedurally generates a patient's info and calls addRandomPatient(name, gender, age, height, weight) to add him to the hashmaps
     * */
    void addRandomPatient();


    /**
     * O(1) on average
     * @brief adds a patient from an existing patient object
     * */
    void addPatient(const Patient &patient);


    /**
     * O(1) on average
     * @brief adds a new patient to the patients hashmaps
     * @attention add patient's id to _patientIds array taking into consideration _deletedPatientsIndexes
     * */
    void addPatient(const std::string &name, uint8_t gender, uint8_t age, uint8_t height, uint16_t weight);


    /**
     * O(1) on average
     * @brief removes a patient from the patients hashmaps by their id
     * */
    void removePatient(uint64_t id);


    /**
     * O(1)
     * @returns a boolean indicating wither there are patients in the unit
     * */
    bool hasPatients() const;


    /**
     * O(1)
     * @return bool indicating if the patient exist
     */
    bool hasPatient(const std::string &name);

    bool hasPatient(uint64_t id);


    /**
     * O(1) on average
     * @returns a const reference to a patient using their name
     * */
    Patient &getPatient(const std::string &name);


    /**
     * O(1) on average
     * @returns a const reference to a patient using their ID
     * */
    Patient &getPatient(uint64_t id);


    /**
     * O(n)
     * @returns a reference to the patients in a hashmap
     * @attention NOT SURE ABOUT THIS, might be used when printing the list of patients
     * */
    std::unordered_map<std::string, Patient> &getPatients();

    /**
     * O(1)
     * @returns number of patients in the unit
     * */
    size_t getPatientsCount() const;


private:
    // name of the service the care unit belongs to, must be initialized
    const std::string _serviceName;


    // a hashmap that maps each patient's id to their name
    std::unordered_map<uint64_t, std::string> _idToName;


    // a hashmap that maps each patient's name to their Patient object
    std::unordered_map<std::string, Patient> _nameToPatient;


    // https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2003/n1456.html

};