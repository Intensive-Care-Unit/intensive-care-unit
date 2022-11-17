
#include "State.hpp"
#include <iostream>
#include <fstream>
#include <chrono>

using namespace std;
using namespace chrono;


int main()
{
    auto unit = State::getHospital()->getCriticalUnit();

    ofstream csv;
    csv.open("addPatients-profiling.csv");

    csv << "n,t" << endl;


    Patient dummyPatient("critical", "name", 'm', 19, 150, 90);


    for (int i = 1; i <= 1000000; i++)
    {
        auto start = steady_clock::now();
        unit.addPatient(dummyPatient);
        auto end = steady_clock::now();

        auto duration = (long long int) chrono::duration_cast<chrono::nanoseconds>(end - start).count();

        csv << i << "," << duration << endl;
    }

}