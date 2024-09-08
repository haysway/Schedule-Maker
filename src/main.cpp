#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <ctime>
#include <iomanip>
#include <cstdlib>

using namespace std;

#include "../include/Worker.h"
#include "../include/Shift.h"
#include "../include/Schedule.h"


int main()
{
    vector<Worker*> workers;

    Worker::loadWorkers("C:/Users/swain/Schedule Maker/src/worker.txt", workers);

    default_random_engine rng(static_cast<unsigned>(time(nullptr)));
    shuffle(workers.begin(), workers.end(), rng);  

    int startDay, daysInMonth, summerinput, holiday;
    vector<int> holidays;
    bool summer;

    cout << "Enter starting day of month (0=Monday, 6=Sunday): ";
    cin >> startDay;
    cout << "Enter number of days in month: ";
    cin >> daysInMonth;
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
    cout << "Is this a summer month?: ";
    cin >> summerinput;
    if (summerinput == 1) {
        summer = true;
    } else {
        summer = false;
    }

    system("cls");

    Schedule schedule(daysInMonth, startDay, workers, summer, holidays);
    schedule.assignWorkersToShifts();

    schedule.printSchedule();
    cout << endl;

    for (int i = 0; i < workers.size(); i++) {
        cout << workers[i]->getName() << " is working " << workers[i]->getShiftsWorked() << " shifts and " << workers[i]->getTotalHoursWorked() << " hours this month" << endl; 
    }
    int totalShifts { 0 };
    for (int i = 0; i < workers.size(); i++) {
        totalShifts = totalShifts + workers[i]->getShiftsWorked();
    }
    cout << "Total shifts this month: " << totalShifts << endl;

    schedule.printScheduleToCVS("C:/Users/swain/Schedule Maker/src/scheduleFile.csv");

    for (Worker* worker : workers) {
        delete worker;
    }
        
}