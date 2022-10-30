#pragma once

#include <cstdint> // for uint64_t


class Measurement
{
public:

    /**
     * A constructor for the measurement's data, _time is initialized using timestamps
     * @param pressure in //TODO unit
     * @param heartRate in //TODO unit
     * */
    explicit Measurement(float pressure, float heartRate);

    long long int getTime() const;

    float getBloodPressure() const;

    float getHeartRate() const;

private:
    const uint64_t _time; // U_int64 number that represents the timestamp when the measurement was taken;
    const float _bloodPressure;  // blood pressure in //TODO find unit of blood pressure
    const float _heartRate;      // heart rate in //TODO find unit of heart rate
};