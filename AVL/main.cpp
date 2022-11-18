#include <iostream>
#include <thread>
#include "State.hpp"
#include "Hospital.hpp"

using namespace std;

/*
 * TODO: finish update implementations (procedural generation of data)
 * TODO: make testing data set
 * TODO: make functions to import the data sets
 */

int main()
{
    Hospital* h = State::getHospital();

    thread f([&]()
             { h->update(); });






    // rest of code here


    // to wait for update() to finish before finishing the program's execution, prevents exiting the program while the thread is still running
    f.join();

    return 0;
}
