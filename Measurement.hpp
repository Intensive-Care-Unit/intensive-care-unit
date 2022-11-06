#pragma once

#include <cstdint> // for uint64_t
#include <utility>

class Measurement
{
public:

    /**
     * A constructor for the measurement's data, _time is initialized using timestamps
     * @param pressure in //TODO unit
     * @param heartRate in //TODO unit
     * */
    explicit Measurement(uint8_t systolicBP, uint8_t diastolicBP, uint8_t heartRate);

    uint64_t getTime() const;

    std::pair<uint8_t, uint8_t> getBloodPressure() const;

    uint8_t getHeartRate() const;

private:
    const uint64_t _time; // U_int64 number that represents the timestamp when the measurement was taken;

//    const uint8_t _bloodPressure;

    const std::pair<uint8_t, uint8_t> _bloodPressure; // first is Systolic BP, second is Diastolic BP

    const uint8_t _heartRate;      // heart rate in BPM
};