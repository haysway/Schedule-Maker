#ifndef WORKER_H
#define WORKER_H

#pragma once

#include <string>
#include <vector>

using std::string;
using std::vector;

class Worker {
private:
    string name = "";
    float hours = 0.0;
    bool isMale = 1;    // true for boy false for girl
    vector<int> requestedDaysOff;
public:
    Worker(string, bool, vector<int>);

    float getHours();

    string getName();

    void updateHours(float);

    static bool readInWorkers(const string&, vector<Worker*>&);

    static void segregateWorkers(const vector<Worker*>&, vector<Worker*>&, vector<Worker*>&);

    static void sortByHours(vector<Worker*>&, vector<Worker*>&);

    static void sortByHours(vector<Worker*>&);

    static void checkForDayOff(vector<Worker*>&, vector<Worker*>&, int);

    static void printWorkers(const vector<Worker*>&);
};

#endif