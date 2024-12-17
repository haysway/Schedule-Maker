#ifndef DAY_H
#define DAY_H

#pragma once

#include "./Shift.h"
#include <vector>

using std::vector;

class Day {
private:
    vector<Shift> shifts;
    int day;
    int weekDay;
public:
    Day(int, int);
    
    Day(int, int, int, vector<float>);

    void printInfo() const;
};

#endif