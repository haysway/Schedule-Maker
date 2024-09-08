#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "../include/Worker.h"

Worker::Worker(string name, int gender, vector<int> daysOff) : name(name), gender(gender), requestedDaysOff(daysOff), totalHoursWorked(0), shiftsWorked(0)
{}

string Worker::getName()
{
    return name;
}

int Worker::getGender()
{
    return gender;
}

bool Worker::isAvailable(int day) 
{
    return std::find(requestedDaysOff.begin(), requestedDaysOff.end(), day) == requestedDaysOff.end();
}

void Worker::seeDaysOff() 
{
    cout << "Worker " << name << " requested the following days off: ";
    for (int day : requestedDaysOff) {
        cout << day << " ";
    }
    cout << endl;
}

void Worker::updateHours(int shiftHours) 
{
    totalHoursWorked += shiftHours;
}

void Worker::updateShiftsWorked() 
{
    shiftsWorked++;
}

int Worker::getTotalHoursWorked() const
{
    return totalHoursWorked;
}

int Worker::getShiftsWorked() const
{
    return shiftsWorked;
}

void Worker::loadWorkers(const string& workerFile, vector<Worker*>& workers)
{
    ifstream file(workerFile);
    if (!file.is_open()) {
        cerr << "Error opening file: " << workerFile << endl;
        return;
    }

    string line;
    while(getline(file, line)) {
        istringstream iss(line);
        string name;
        int gender;
        vector<int> daysOff;
        int day;

        iss >> name >> gender;
        while (iss >> day) {
            daysOff.push_back(day);
        }

        workers.emplace_back(new Worker(name, gender, daysOff));
    }

    file.close();
}



vector<int> Worker::getDaysOff() const {
    return requestedDaysOff;
}