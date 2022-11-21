/** Mohammed Iyad Benkhaled **/

#include "State.hpp"
#include <iostream>
#include <fstream>
#include <chrono>

using namespace std;
using namespace chrono;


int main()
{
    auto &unit = State::getHospital()->getCriticalUnit();

    ofstream csv;
    csv.open("addPatients-AVL.csv");

    csv << "n,t" << endl;


    for (int i = 1; i <= 100000; i++)
    {
        string istr = to_string(i);
        auto start = steady_clock::now();
        unit.addPatient({"critical", "name " + istr, 'm', 19, 150, 90});
        auto end = steady_clock::now();

        if (i % 100 == 0)
        {
            auto duration = (long long int) chrono::duration_cast<chrono::nanoseconds>(end - start).count();

            csv << to_string(unit.getPatients().size()) << "," << to_string(duration) << endl;
        }
    }


}
