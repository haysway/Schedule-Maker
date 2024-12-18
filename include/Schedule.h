#ifndef SCHEDULE_H
#define SCHEDULE_H

#pragma once

#include "./Day.h"
#include <vector>

using std::vector;

class Schedule {
private:
    vector<Day*> days;
    int numDays;
    int startDay;

public:
    Schedule(int, int);

    void assignWorkers(vector<Worker*>&, vector<Worker*>&);

    void printInfo() const;
};

#endif