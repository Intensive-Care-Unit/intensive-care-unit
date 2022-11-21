#include "Patient.hpp"
#include <chrono>
#include <iostream>
#include "Utils.hpp"
#include "State.hpp"

using std::cout;
using std::endl;
using namespace std::chrono;

Patient::Patient(const std::string &serviceName, const std::string &name, uint8_t gender, uint8_t age, uint8_t height,
                 uint16_t weight)
        :
        _serviceName(serviceName)
        , _name(name)
        , _gender(gender)
        , _age(age)
        , _height(height)
        , _weight(weight)
        , _id(Utils::rng())
{

}

//Patient &Patient::operator=(const Patient &p)
//{
//    return *this;
//}


uint64_t Patient::getId() const
{
    return _id;
}

std::string Patient::getName() const
{
    return _name;
}

uint8_t Patient::getGender() const
{
    return _gender;
}

uint8_t Patient::getAge() const
{
    return _age;
}

uint8_t Patient::getHeight() const
{
    return _height;
}

uint16_t Patient::getWeight() const
{
    return _weight;
}

std::list<Measurement *> &Patient::getHistory()
{
    return _history;
}

void Patient::addMeasurement(uint8_t systolicBP, uint8_t diastolicBP, uint8_t heartRate)
{
    // emplace_back() accepts arguments that initialize the constructor of the template type of the vector
    // we used emplace_front() bcs it's faster than push_front()
    // https://yasenh.github.io/post/cpp-diary-1-emplace_back/

    this->_history.emplace_back(new Measurement(systolicBP, diastolicBP, heartRate));
}


const std::string &Patient::getServiceName() const
{
    return _serviceName;
}

void Patient::moveToCritical()
{
    auto &currentUnit = State::getHospital()->getServiceUnit(_serviceName);
    auto &criticalUnit = State::getHospital()->getCriticalUnit();

    if (_serviceName == criticalUnit.getServiceName())
    {
        return; // patient already in critical
    }

    // removing the patient from the current unit and adding them to the critical unit
    currentUnit.removePatient(_id);
//    markAsDeleted();
    criticalUnit.addPatient({_serviceName, _name, _gender, _age, _height, _weight});

}

void Patient::release()
{
    auto &currentUnit = State::getHospital()->getServiceUnit(_serviceName);
    currentUnit.removePatient(_id);
//    markAsDeleted();
}

void Patient::generateMeasurement()
{
    // heart rate: 0-200
    // blood pressure:
    // systolic € [50 - 220]
    // diastolic € [30 - 180]
    // systolic is always higher than diastolic

    uint8_t heartRate, systolicBP, diastolicBP;


    // critical Heart rate < 30 or > 130
    // critical BP:
    // sys < 90 or dias < 60
    // sys > 180 and/or dias > 120


    int ran = Utils::rng(100);
    if (ran < 1)
    {
        // generate critical - normal measurements
        //heart rate:
        heartRate = Utils::rng(220);

        // blood pressure
        diastolicBP = Utils::rng(30, 190);
        systolicBP = Utils::rng(diastolicBP, 220);
    } else
    {
        // generate normal measurements
        //heart rate:
        heartRate = Utils::rng(40, 100);

        // blood pressure
        diastolicBP = Utils::rng(90, 120);
        systolicBP = Utils::rng(diastolicBP, 180);
    }


    this->addMeasurement(systolicBP, diastolicBP, heartRate);

}


void Patient::update()
{
    // add measurement
    generateMeasurement();

    // based on the new measurement, decide whether to move patient to critical

    // critical Heart rate < 30 or > 130
    // critical BP:
    // sys < 90 or dias < 60
    // sys > 180 and/or dias > 120

    if (_history.empty())
    {
        return;
    }

    Measurement *lastMeasurement = _history.back();

    int systolicBP = lastMeasurement->getBloodPressure().first;
    int diastolicBP = lastMeasurement->getBloodPressure().second;
    int heartRate = lastMeasurement->getHeartRate();

    // Heart Rate
    bool isHeartRateCritical = heartRate < 30 || heartRate > 130;
    bool isBpCritical = (systolicBP < 90 || diastolicBP < 60) || (systolicBP > 180 || diastolicBP > 120);


//    if (_serviceName == "critical")
//    {
//        int releaseRandoNum = Utils::rng(100);
//        if (releaseRandoNum < 3)
//        {
//            release();
//            return;
//        }
//    }
//
//    if (isHeartRateCritical || isBpCritical)
//    {
//        moveToCritical();
//        return;
//    }

}
