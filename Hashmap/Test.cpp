/** Mohammed Iyad Benkhaled **/
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
    csv.open("addPatients-HM.csv");

    csv << "n,t" << endl;

    int EXP = 20;

    for (int i = 1; i <= 100000; i++)
    {
        long long int average = 0;
        for (int a = 1; a <= EXP; a++)
        {
            string istr = to_string(i);
            auto start = steady_clock::now();
            unit.addPatient({"critical", "name " + istr, 'm', 19, 150, 90});
            auto end = steady_clock::now();

            auto duration = (long long int) chrono::duration_cast<chrono::nanoseconds>(end - start).count();

            average += duration / EXP;

        }

        if (i % 100 == 0)
        {
            csv << to_string(unit.getPatients().size()) << "," << to_string(average) << endl;
        }
    }

}