#include "../include/Day.h"

#include <iostream>

using std::cout;
using std::endl;

Day::Day(int day, int weekDay) 
: day(day), weekDay(weekDay) {
    this->shifts.push_back(new Shift(-1, 0));
}

Day::Day(int day, int weekDay, int numShifts, vector<float> hours)
: day(day), weekDay(weekDay) {
    for (int i = 0; i < numShifts; i++) {
        this->shifts.push_back(new Shift(i + 1, hours[i]));
    }
}

void Day::scheduleShifts(vector<Worker*>& boyWorkers, vector<Worker*>& girlWorkers) {
    for (auto shift : this->shifts) {
        // for each shift in the day
        shift->decideWorkers(boyWorkers, girlWorkers, this->day);
    }
}

void Day::printInfo() const {
    for (auto shift : this->shifts) {
        // Array of weekday names
        const char* weekDays[] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};

        // Print the weekday corresponding to the weekDay number
        cout << weekDays[this->weekDay] << endl;
        shift->printInfo();
    }
}