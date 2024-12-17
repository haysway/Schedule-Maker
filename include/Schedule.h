#ifndef SCHEDULE_H
#define SCHEDULE_H

#pragma once

#include "./Day.h"
#include <vector>

using std::vector;

class Schedule {
private:
    vector<Day> days;
    int numDays;
    int startDay;

public:
    //Schedule(int, int, vector<int>, float, float, vector<tuple<int,int, float>>);
    Schedule(int, int);

    void printInfo() const;
};

#endif