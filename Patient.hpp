#pragma once

#include "Measurement.hpp"
#include <string>
#include <vector>

class Patient
{
public:
    explicit Patient(const std::string &name, uint8_t gender, uint8_t age, uint8_t height, uint16_t weight);


    // custom copy assignment since it will be implicitly deleted bcs of having const members
    Patient &operator=(const Patient &p);


/*********************************
*          Getters
********************************/

    uint64_t getId() const;

    const std::string &getName() const;

    uint8_t getGender() const;

    uint8_t getAge() const;

    uint8_t getHeight() const;

    uint16_t getWeight() const;

    const std::vector<Measurement> &getHistory() const;



/*******************************
 *  Functionality
 ******************************/


    /**
     * adds a new measurement to the history of the patient
     * @param pressure in //TODO unit
     * @param heartRate in //TODO unit
     * */
    void addMeasurement(float pressure, float heartRate);


    void print() const;

private:

    /*
     * Here we've used specific integer types to make sure we don't allocate more memory than we need
     * taking into consideration that we'll have many of these objects initialized at once
     *
     * added _ as a prefix to avoid ambiguity between private members and function params
     * */

    // a unique id assigned from the timestamp when the patient is created
    const uint64_t _id;

    const std::string _name;

    // 1 for male, 0 for female, we'll use an enum to avoid ambiguity
    const uint8_t _gender;

    const uint16_t _age;

    const uint16_t _height; // in cm

    const uint16_t _weight; // in kg;  uint16, bcs weight can be more than 255


    // history of measurements
    std::vector<Measurement> history;

};
