#include "../include/Shift.h"

#include <iostream>

using std::endl;
using std::cout;

Shift::Shift(int shiftType, float hours)
: shiftType(shiftType), hours(hours) {

}

void Shift::printInfo() {
    cout << "Shift: " << this->shiftType << endl;
    cout << "Hours: " << this->hours << endl << endl << endl;
}