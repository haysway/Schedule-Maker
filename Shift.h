#ifndef SHIFT_H
#define SHIFT_H

#pragma once

#include "./Worker.h"

#include <vector>
using namespace std;

class Shift
{
private:
    int day;

    int shiftType; // 0 for lap swim, 1 for 1st shift, 2 for 2nd shift

    int amountHours;

    vector<string> assignedWorkers;

public:
    Shift(int, int, int);

    int getDay() const;

    int getShiftType() const;

    int getAmountHours() const;

    void addWorker(const string& workerName);

    const vector<string>& getWorkers() const;
};

#endif