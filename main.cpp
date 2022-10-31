#include <iostream>
#include "Hospital.hpp"

int main()
{
    Hospital h;
    h.addUnit("cardiology");

    CareUnit card = h.getServiceUnit("cardiology");

    Patient p = card.addPatient("ahmed", 1, 19, 170, 60);

    p.print();

    return 0;
}
