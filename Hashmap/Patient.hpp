#pragma once

#include "Measurement.hpp"
#include <string>
#include <vector>
#include <unordered_map>
#include <list>


class Patient
{
public:

    Patient(const std::string &serviceName, const std::string &name, uint8_t gender, uint8_t age,
            uint8_t height, uint16_t weight);


/*********************************
*          Getters
********************************/

    uint64_t getId() const;

    std::string getName() const;

    uint8_t getGender() const;

    uint8_t getAge() const;

    uint8_t getHeight() const;

    uint16_t getWeight() const;

    std::list<Measurement *> &getHistory();

    bool isDeleted() const;


/*********************************
*          Functionality
********************************/

    void remove();


    /**
     * Procedurally generates measurements and adds them to the patient's _history
     * */
    void generateMeasurement();


    /**
     * adds a new measurement to the _history of the patient from the parameters
     * @param pressure in mmHG
     * @param heartRate in BPM
     * */
    void addMeasurement(uint8_t systolicBP, uint8_t diastolicBP, uint8_t heartRate);


    /**
     * Removes the patient from its current careUnit object
     * @attention might need access to the CareUnit object it belongs to in order to complete this operation
     * */
    void release();

    const std::string &getServiceName() const;


    /**
     * Moves the current patient to the critical CareUnit object's _patients array
     * @attention might need access to the CareUnit object it belongs to as well as the critical CareUnit object in order to complete this operation
     */
    void moveToCritical();


    // TODO remove later, just for testing if code works
    void print() const;


    /**
     * @brief Generates a measurement and adds it to the _history, might check for the patient's last measurement to decide whether they should be moved to the critical unit,
     * @attention takes into consideration the unit the patient belongs to (if he is already in critical unit, no need to move him to it)
     */
    void update();

private:


    // the service unit the patient belongs to (might be helpful later)
    std::string _serviceName;


    /*
     * Here we've used specific integer types to make sure we don't allocate more memory than we need
     * taking into consideration that we'll have many of these objects initialized at once
     *
     * added _ as a prefix to avoid ambiguity between private members and function params
     * */

    // a unique id assigned from the timestamp when the patient is created
    uint64_t _id;

    std::string _name;

    // 'm' for male, 'f' for female, we'll use an enum to avoid ambiguity
    uint8_t _gender;

    uint8_t _age;

    uint8_t _height; // in cm

    uint16_t _weight; // in kg;  uint16, bcs weight can be more than 255


    // history of measurements
    std::list<Measurement *> _history;


    bool _isDeleted = false;


};
