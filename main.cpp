#include <iostream>
#include <thread>
#include "Hospital.hpp"
#include "State.hpp"
#include <utility>
#include "VariadicTable.h"
#include "Driver.hpp"

int main() {
    Hospital* h = State::getHospital();
    std::thread f([&]()
             { h->update(); });

    // The main driver program
    Driver();

    f.join();
    return 0;
}
