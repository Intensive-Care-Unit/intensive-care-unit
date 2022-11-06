#include "Measurement.hpp"
#include <chrono>

using std::make_pair;
using namespace std::chrono;

/**
 * duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count():
 *
 * returns the number of milliseconds since epoch
 *
 */
Measurement::Measurement(uint8_t systolicBP, uint8_t diastolicBP, uint8_t heartRate)
        :
        _bloodPressure(make_pair(systolicBP, diastolicBP))
        , _heartRate(heartRate)
        , _time(duration_cast<seconds>(system_clock::now().time_since_epoch()).count())
{}

uint64_t Measurement::getTime() const
{
    return _time;
}

std::pair<uint8_t, uint8_t> Measurement::getBloodPressure() const
{
    return _bloodPressure;
}

uint8_t Measurement::getHeartRate() const
{
    return _heartRate;
}



