/** Mohammed Iyad Benkhaled **/

#pragma once

#include "Patient.hpp"
#include <string>
#include <vector>
#include <chrono>
#include <random>
#include <cassert>
#include "AvlTree.h"

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
// vector<Patient> getPatients( )                      --> Get all patients of the unit
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
     * @brief procedurally generates a patient's info and calls addRandomPatient(name, gender, age, height, weight) to add him to the tree
     * */
    void addRandomPatient();


    /**
     * O(1) on average
     * @brief adds a patient from an existing patient object
     * */
    void addPatient(const Patient &patient);


    /**
     * O(1) on average
     * @brief adds a new patient to the patients trees
     * @attention add patient's id to _patientIds array taking into consideration _deletedPatientsIndexes
     * */
    void addPatient(const std::string &name, uint8_t gender, uint8_t age, uint8_t height, uint16_t weight);


    /**
     * O(1) on average
     * @brief removes a patient from the patients tree by their id
     * */
    void removePatient(uint64_t id);

    /**
     * O(1)
     * @returns a boolean indicating wither there are patients in the unit
     * */
    bool hasPatients() const;


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
     * @returns a reference to the patients in a vector
     * */
    std::vector<Patient> getPatients() const;

private:
    // name of the service the care unit belongs to, must be initialized
    const std::string _serviceName;


    // an AVL tree that maps each patient's id to their name
    AvlTree<uint64_t, std::string> _idToName;


    // an AVL tree that maps each patient's name to their Patient object
    AvlTree<std::string, Patient> _nameToPatient;

};