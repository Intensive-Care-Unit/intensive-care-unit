#include "Measurement.hpp"
#include <chrono>


/**
 * duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count():
 *
 * returns the number of milliseconds since epoch
 *
 */
Measurement::Measurement(float pressure, float heartRate)
        :
        _bloodPressure(pressure)
        , _heartRate(heartRate)
        , _time(duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count())
{}

long long int Measurement::getTime() const
{
    return _time;
}

float Measurement::getBloodPressure() const
{
    return _bloodPressure;
}

float Measurement::getHeartRate() const
{
    return _heartRate;
}



