#ifndef SHIFT_H
#define SHIFT_H

#pragma once

#include "./Worker.h"
#include <vector>

using std::vector;

class Shift {
private:
    float hours;
    int shiftType;
    vector<Worker> staff;
public:
    Shift(int, float);

    void printInfo();
};

#endif