#ifndef SCHEDULE_H
#define SCHEDULE_H

#pragma once

#include "./Shift.h"
#include "./Worker.h"

#include <vector>
#include <random>
#include <ctime>
using namespace std;

class Schedule
{
private:
    vector<Shift> shifts;

    vector<Worker*>& workers;

    int startDay;

    int daysInMonth;

    bool summer;
public:
    Schedule(int, int, vector<Worker*>&, bool, const vector<int>&);

    void createShifts(const vector<int>&);

    void assignWorkersToShifts();

    void printSchedule() const;

    void printScheduleToCVS(const string&) const;

protected:
    void addWorkers(Shift&, vector<Worker*>, int);

};

#endif