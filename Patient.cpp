#include "Patient.hpp"
#include <chrono>


Patient::Patient(const std::string &name, uint8_t gender, uint8_t age, uint8_t height, uint16_t weight)
        :
        _name(name)
        , _gender(gender)
        , _age(age)
        , _height(height)
        , _weight(weight)
        , _id(duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count())
{

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

const std::vector<Measurement> &Patient::getHistory() const
{
    return history;
}

void Patient::addMeasurement(float pressure, float heartRate)
{
    // emplace_back() accepts arguments that initialize the constructor of the template type of the vector
    // we used emplace_back() bcs it's faster than push_back()
    // https://yasenh.github.io/post/cpp-diary-1-emplace_back/

    this->history.emplace_back(pressure, heartRate);
}

Patient &Patient::operator=(const Patient &p)
{
    return *this;
}

