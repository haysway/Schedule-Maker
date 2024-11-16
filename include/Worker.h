#ifndef WORKER_H
#define WORKER_H

#pragma once

#include <vector>
#include <string>
using namespace std;

class Worker {
private:
    string name;

    int gender;     // 1 for boy 0 for girl

    float totalHoursWorked;

    int shiftsWorked { 0 };

    vector<int> requestedDaysOff;

public:
    Worker(string, int, vector<int>);

    string getName();

    int getGender();

    bool isAvailable(int);

    void seeDaysOff();

    void updateHours(float);

    void updateShiftsWorked();

    float getTotalHoursWorked() const;

    int getShiftsWorked() const;

    static void loadWorkers(const string&, vector<Worker*>&);

    vector<int> getDaysOff() const;
};

#endif