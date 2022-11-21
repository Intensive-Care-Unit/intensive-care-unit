/** Mohammed Iyad Benkhaled **/
#pragma once

#include <cstdint>
#include <utility>
#include <ctime>

// Measurement class
//
// CONSTRUCTION: Systolic Blood Pressure, Diastolic Blood Pressure, Heart Rate
//
class Measurement
{
public:

    /**
     * constructor for the measurement's _data, _time is initialized using timestamps
     * @param systolicBP in mmHG
     * @param diastolicBP in mmHG
     * @param heartRate in mmHG
     * */
    explicit Measurement(uint8_t systolicBP, uint8_t diastolicBP, uint8_t heartRate);


    /********************************
    *          Getters
    *           O(1)
    ********************************/
    time_t getTime() const;

    std::pair<uint8_t, uint8_t> getBloodPressure() const;

    uint8_t getHeartRate() const;

private:
    const time_t _time; // U_int64 number that represents the timestamp when the measurement was taken;

    const std::pair<uint8_t, uint8_t> _bloodPressure; // first is Systolic BP, second is Diastolic BP

    const uint8_t _heartRate;      // heart rate in BPM
};
