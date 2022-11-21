/** Mohammed Iyad Benkhaled **/

#pragma once

#include <chrono>
#include <cassert>
#include <random>

// Utils class
//
// Used for utilities functions
//
class Utils
{
public:

    /**
     * @returns a random number between 0 and a
     * @param int a: upper bound
     * */
    static int rng(int a)
    {
        // assert aborts the program if the condition is not true
        assert(a > 0);

        auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();

        std::mt19937 num(seed);
        std::uniform_int_distribution<int> distr(0, a);

        return static_cast<int>(distr(num));
    }


    /**
     * @returns a random number in a certain range
     * @param int a: lower bound
     * @param int b: upper bound
     * */
    static int rng(int a, int b)
    {
        // assert aborts the program if the condition is not true
        assert(a < b);

        auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();

        std::mt19937 num(seed);
        std::uniform_int_distribution<int> distr(a, b);

        return static_cast<int>(distr(num));
    }


    /**
    * @returns a random number in a an indefinite range
    */
    static uint64_t rng()
    {
        auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();

        std::mt19937 num(seed);

        uint64_t n = num();

        return static_cast<uint64_t>(n);
    }

};
