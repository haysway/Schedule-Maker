#include "../include/Worker.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

using std::cout;
using std::endl;
using std::cerr;
using std::ifstream;
using std::istringstream;

Worker::Worker(string name, bool gender, vector<int> daysOff) : name(name), isMale(gender), requestedDaysOff(daysOff)
{}

bool Worker::readInWorkers(const string& workerFile, vector<Worker*>& workers)
{
    ifstream file(workerFile);
    if (!file.is_open()) {
        cerr << "Error opening file: " << workerFile << endl;
        return false;
    }

    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        string name;
        bool gender;
        vector<int> daysOff;
        int day;

        iss >> name >> gender;
        while (iss >> day) {
            daysOff.push_back(day);
        }

        workers.emplace_back(new Worker(name, gender, daysOff));
    }
    file.close();
    return true;
}

float Worker::getHours() {
    return this->hours;
}

string Worker::getName() {
    return this->name;
}

void Worker::updateHours(float hours) {
    this->hours += hours;
}

void Worker::segregateWorkers(const vector<Worker*>& workers, vector<Worker*>& boys, vector<Worker*>& girls) {
    for (const auto& worker : workers) {
        if (worker->isMale) {
            boys.push_back(worker);
        } else {
            girls.push_back(worker);
        }
    }
}

void Worker::sortByHours(vector<Worker*>& boys, vector<Worker*>& girls) {
    auto compareByHours = [](Worker* a, Worker* b) {
        return a->hours < b->hours;
    };

    sort(boys.begin(), boys.end(), compareByHours);
    sort(girls.begin(), girls.end(), compareByHours);
}

void Worker::sortByHours(vector<Worker*>& workers) {
    auto compareByHours = [](Worker* a, Worker* b) {
        return a->hours < b->hours;
    };
    sort(workers.begin(), workers.end(), compareByHours);
}

void Worker::checkForDayOff(vector<Worker*>& boys, vector<Worker*>& girls, int day) {
    auto hasRequestedDayOff = [day](Worker* worker) {
        return find(worker->requestedDaysOff.begin(), worker->requestedDaysOff.end(), day) 
               != worker->requestedDaysOff.end();
    };

    // Remove workers from boys who requested the day off
    boys.erase(remove_if(boys.begin(), boys.end(), hasRequestedDayOff), boys.end());

    // Remove workers from girls who requested the day off
    girls.erase(remove_if(girls.begin(), girls.end(), hasRequestedDayOff), girls.end());
}

void Worker::printWorkers(const vector<Worker*>& workers) {
    for (auto worker : workers) {
        cout << worker->hours << " - ";
        if (worker->isMale) {
            cout << "M ";
        } else {
            cout << "F ";
        }
        cout << worker->name;
        for (auto day : worker->requestedDaysOff) {
            cout << " " << day;
        }
        cout << endl;
    }
}