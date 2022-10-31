#pragma once

#include "Patient.hpp"
#include <string>
#include <vector>

class CareUnit
{
public:
    explicit CareUnit(const std::string &name);

    const std::string &getServiceName() const;

    // adds a patient to the current service, called occasionally
    Patient addPatient(const std::string &name, uint8_t gender, uint8_t age, uint8_t height, uint16_t weight);


    const std::vector<Patient> &getPatients() const;

private:
    // name of the service the care unit belongs to, must be initialized
    const std::string _serviceName;

    // list of patients that are under the current service
    std::vector<Patient> patients;



/**********************
 * Helper functions
 *********************/



    // removes a patient from the list using his unique id
    void removePatient(uint64_t id);

};
