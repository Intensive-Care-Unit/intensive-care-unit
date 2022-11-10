#include "Patient.hpp"
#include <chrono>
#include <iostream>

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
        , _id(duration_cast<seconds>(system_clock::now().time_since_epoch()).count())
{

}

Patient &Patient::operator=(const Patient &p)
{
    return *this;
}


uint64_t Patient::getId() const
{
    return _id;
}

const std::string &Patient::getName() const
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

const std::list<Measurement> &Patient::getHistory() const
{
    return history;
}

void Patient::addMeasurement(uint8_t systolicBP, uint8_t diastolicBP, uint8_t heartRate)
{
    // emplace_back() accepts arguments that initialize the constructor of the template type of the vector
    // we used emplace_front() bcs it's faster than push_front()
    // https://yasenh.github.io/post/cpp-diary-1-emplace_back/

    this->history.emplace_front(systolicBP, diastolicBP, heartRate);
}


void Patient::print() const
{
    cout << "id: " << _id << endl;
    cout << "name: " << _name << endl;
    cout << "age: " << (uint16_t) _age << endl;
    cout << "height: " << (uint16_t) _height << " cm" << endl;
    cout << "weight: " << _weight << " kg" << endl;
    cout << "gender: " << (_gender ? "male" : "female") << endl;
}

const std::string &Patient::getServiceName() const
{
    return _serviceName;
}

void Patient::moveToCritical()
{

}

void Patient::release()
{

}

void Patient::addMeasurement()
{

}

// TODO finish Patient's update()
void Patient::update()
{

}

