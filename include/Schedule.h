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

protected:
    void addTwoBoys(Shift&, vector<Worker*>, vector<Worker*>);

    void addTwoGirls(Shift&, vector<Worker*>, vector<Worker*>);

    void addOneBoy(Shift&, vector<Worker*>, vector<Worker*>);

    void addOneGirl(Shift&, vector<Worker*>, vector<Worker*>);

};

#endif