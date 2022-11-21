#include <iostream>
#include <iostream>
#include <string>
#include <iomanip>
// Functions found in https://stackoverflow.com/questions/14765155/how-can-i-easily-format-my-data-table-in-c
// They were lightly modified for our purpose


// Prints a double value with a specified precision
std::string printDouble(const double x, const int decDigits, const int width) {
    std::stringstream ss;
    ss << std::fixed << std::right;
    ss.fill(' ');        // fill space around displayed #
    ss.width(width);     // set  width around displayed #
    ss.precision(decDigits); // set # places after decimal
    ss << x;
    return ss.str();
}

/*! Center-aligns string within a field of width w. Pads with blank spaces
    to enforce alignment. */
std::string center(const std::string s, const int w) {
    std::stringstream ss;
    std::stringstream spaces;
    int padding = w - s.size();                 // count excess room to pad
    for(int i=0; i<padding/2; ++i)
        spaces << " ";
    ss << spaces.str() << s << spaces.str();    // format with padding
    if(padding>0 && padding%2!=0)               // if odd #, add 1 space
        ss << " ";
    return ss.str();
}
