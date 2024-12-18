#include "../include/Schedule.h"

#include <iostream>
#include <algorithm>

using std::cout;
using std::endl;
using std::cin;
using std::pair;

Schedule::Schedule(int numDays, int startDay)
: numDays(numDays), startDay(startDay) {
    int numShiftsWeekday, numShiftsWeekend;
    vector<float> weekdayHours, weekendHours;
    vector<int> holidays;
    vector<pair<int, vector<float>>> customDays;

    int holiday;
    while (true) {
        cout << "Enter a holiday day (1-31) (-1 to quit): ";
        cin >> holiday;

        if (holiday == -1) {
            break;
        }

        if (holiday >= 1 && holiday <= 31) {
            holidays.push_back(holiday);
        } else {
            cout << "Invalid entry. Enter a day between 1 and 31" << endl;
        }
    }

    cout << "How many shifts on a normal weekday?: ";
    cin >> numShiftsWeekday;
    cout << "How many shifts on a normal weekend?: ";
    cin >> numShiftsWeekend;

    float tempHours;
    for (int i = 0; i < numShiftsWeekday; i++) {
        cout << "How many hours for shift " << i + 1 << " on weekdays?: ";
        cin >> tempHours;
        weekdayHours.push_back(tempHours);
    }
    for (int i = 0; i < numShiftsWeekend; i++) {
        cout << "How many hours for shift " << i + 1 << " on weekends?: ";
        cin >> tempHours;
        weekendHours.push_back(tempHours);
    }

    int customDay;
    int customShifts;
    int customShiftHour;
    while (true) {
        cout << "Enter a day to be customized (-1 to quit): ";
        cin >> customDay;

        if (customDay == -1) {
            break;
        }

        if (customDay >= 1 && customDay <= 31) {
            cout << "How many shifts are on day " << customDay << ": ";
            cin >> customShifts;    

            vector<float> shiftHours;
            for (int i = 0; i < customShifts; i++) {
                cout << "How many hours is shift " << i + 1 << " on day " << customDay << ": ";
                cin >> customShiftHour;
                shiftHours.push_back(customShiftHour);
            }

            customDays.push_back(make_pair(customDay, shiftHours));
        } else {
            cout << "Invalid entry. Enter a day between 1 and 31" << endl;
        }
    }

    // create schedule frame here
    for (int day = 1; day <= numDays; day++) {
        int weekDay = (startDay + day - 1) % 7;                         // calculate the weekday for the given start day

        auto itHoliday = find(holidays.begin(), holidays.end(), day);
        auto itCustomDay = find_if(customDays.begin(), customDays.end(), 
            [day](const pair<int, vector<float>>& p) { return p.first == day; }); // Check if the day is customized

        if (weekDay == 6 || itHoliday != holidays.end()) {
            // if sunday or holiday
            this->days.push_back(new Day(day, weekDay));
        } else if (itCustomDay != customDays.end()) {
            const auto& customShiftHours = itCustomDay->second;
            this->days.push_back(new Day(day, weekDay, customShiftHours.size(), customShiftHours));
        } else if (weekDay <= 4) {
            // normal weekday
            this->days.push_back(new Day(day, weekDay, numShiftsWeekday, weekdayHours));
        } else {
            // normal weekend
            this->days.push_back(new Day(day, weekDay, numShiftsWeekend, weekendHours));
        }

    }
}

void Schedule::assignWorkers(vector<Worker*>& boyWorkers, vector<Worker*>& girlWorkers) {
    for (auto dayPtr : this->days) {
        dayPtr->scheduleShifts(boyWorkers, girlWorkers);
    }
}

void Schedule::printInfo() const {
    int dayOfMonth = 1;
    for (auto dayPtr : this->days) {
        cout << dayOfMonth++ << endl;
        dayPtr->printInfo();
    }
}