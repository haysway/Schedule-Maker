#include "../include/Worker.h"

#include <fstream>
#include <sstream>
#include <iostream>

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

        file.close();
    }
    return true;
}