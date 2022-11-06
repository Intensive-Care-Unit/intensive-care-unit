#include <iostream>
#include "Hospital.hpp"

#include <chrono>
#include <thread>

using namespace std::this_thread;     // sleep_for, sleep_until
using namespace std::chrono_literals; // ns, us, ms, s, h, etc.
using std::chrono::system_clock;

int main()
{
    Hospital h;
    h.addUnit("cardiology");

    CareUnit card = h.getServiceUnit("cardiology");

    Patient p = card.addPatient("ahmed", 1, 19, 170, 60);

    p.print();


    return 0;
}
