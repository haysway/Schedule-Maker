// #include <iostream>
// #include <vector>
// #include <string>
// #include <algorithm>
// #include <random>
// #include <chrono>
// #include <ctime>
// #include <iomanip>
// #include <cstdlib>

// using namespace std;
#include <iostream>
#include <random>
#include <chrono>
#include <algorithm>
#include <vector>

using std::cout;
using std::cin;
using std::endl;
using std::mt19937;
using std::random_device;
using std::shuffle;

#include "../include/Worker.h"
#include "../include/Shift.h"
#include "../include/Schedule.h"


enum ProgramState {
    MENU,
    LOAD_WORKERS,
    LOAD_SCHEDULE,
    LOAD_PRINT_SCHEDULE,
    EXIT
};

ProgramState handleMenu();
ProgramState handleLoadWorkers(vector<Worker*>&);
ProgramState handleLoadSchedule(Schedule*& masterSchedule);
ProgramState handlePrintSchedule(const Schedule* masterSchedule);

int main()
{
    // vector<Worker*> workers;

    // Worker::loadWorkers("C:/Users/swain/ScheduleMakerGit/Schedule-Maker/src/worker.txt", workers);

    // ////
    // // Create a Mersenne Twister engine
    // std::mt19937 rng(std::random_device{}());

    // // Seed the engine with a combination of system time and hardware randomness
    // auto now = std::chrono::high_resolution_clock::now();
    // auto seed = now.time_since_epoch().count() ^ rng();
    // rng.seed(seed);

    // // Shuffle the workers vector
    // shuffle(workers.begin(), workers.end(), rng); 
    // //// 

    // int startDay, daysInMonth, summerinput, holiday;
    // vector<int> holidays;
    // bool summer;

    // cout << "Enter starting day of month (0=Monday, 6=Sunday): ";
    // cin >> startDay;
    // cout << "Enter number of days in month: ";
    // cin >> daysInMonth;
    // while (true) {
    //     cout << "Enter a holiday day (1-31) (-1 to quit): ";
    //     cin >> holiday;

    //     if (holiday == -1) {
    //         break;
    //     }

    //     if (holiday >= 1 && holiday <= 31) {
    //         holidays.push_back(holiday);
    //     } else {
    //         cout << "Invalid entry. Enter a day between 1 and 31" << endl;
    //     }
    // }
    // cout << "Is this a summer month?: ";
    // cin >> summerinput;
    // if (summerinput == 1) {
    //     summer = true;
    // } else {
    //     summer = false;
    // }

    // system("cls");

    // Schedule schedule(daysInMonth, startDay, workers, summer, holidays);
    // schedule.assignWorkersToShifts();

    // schedule.printSchedule();
    // cout << endl;

    // for (int i = 0; i < workers.size(); i++) {
    //     cout << workers[i]->getName() << " is working " << workers[i]->getShiftsWorked() << " shifts and " << workers[i]->getTotalHoursWorked() << " hours this month" << endl; 
    // }
    // int totalShifts { 0 };
    // for (int i = 0; i < workers.size(); i++) {
    //     totalShifts = totalShifts + workers[i]->getShiftsWorked();
    // }
    // cout << "Total shifts this month: " << totalShifts << endl;
                                
    // schedule.printScheduleToCVS("C:/Users/swain/ScheduleMakerGit/Schedule-Maker/src/scheduleFile.csv");
    // for (Worker* worker : workers) {
    //     delete worker;
    // }

    vector<Worker*> workers;    //TODO: initialize with nullptr, then delete this
    Schedule* masterSchedule = nullptr;
        
    ProgramState currentState = MENU;
    while (currentState != EXIT) {
        switch (currentState) {
            case MENU:
                currentState = handleMenu();
                break;
            case LOAD_WORKERS:
                currentState = handleLoadWorkers(workers);
                break;
            case LOAD_SCHEDULE:
                currentState = handleLoadSchedule(masterSchedule);
                break;
            case LOAD_PRINT_SCHEDULE:
                currentState = handlePrintSchedule(masterSchedule);
                break;
            default:
                cout << "Invalid state. Exiting.\n";
                currentState = EXIT;
                break;
        }
    }

    delete masterSchedule;
    for (Worker* worker : workers) {
        delete worker;
    }

    return 0;
}

ProgramState handleMenu() {
    int choice;
    cout << "Choose from the following:\n";
    cout << "1 - Load Workers\n";
    cout << "2 - Load Schedule\n";
    cout << "4 - Print Schedule\n";
    cout << "5 - Exit\n";
    cout << "Choice? ";
    cin >> choice;

    switch (choice) {
        case 1: return LOAD_WORKERS;
        case 2: return LOAD_SCHEDULE;
        case 4: return LOAD_PRINT_SCHEDULE;
        case 5: return EXIT;
        default:
            cout << "Invalid choice. Try again.\n";
            return MENU;
    }
}

ProgramState handleLoadWorkers(vector<Worker*>& workers) {
    // A state that loads in workers from the txt file
    // workers are read in line by line and stored in a 
    // vector of pointers to Worker objects

    cout << "Loading workers...\n";

    bool readIsGood = Worker::readInWorkers("C:/Users/swain/ScheduleMakerGit/Schedule-Maker/src/worker.txt", workers);

    if (readIsGood) {
        cout << "Workers loaded successfully. Returning to menu\n";
        ////
        // Create a Mersenne Twister engine
        std::mt19937 rng(std::random_device{}());

        // Seed the engine with a combination of system time and hardware randomness
        auto now = std::chrono::high_resolution_clock::now();
        auto seed = now.time_since_epoch().count() ^ rng();
        rng.seed(seed);

        // Shuffle the workers vector
        shuffle(workers.begin(), workers.end(), rng); 
        //// 

        for (auto worker : workers) {
            cout << worker << endl;
        }
    } else {
        cout << "Error loading workers. Returning to menu\n";
    }
    
    return MENU;
}

ProgramState handleLoadSchedule(Schedule*& masterSchedule) {
    // A state that loads in info to create an empty month schedule
    // Needs info such as days in month, starting day, holidays,
    // normal hours, special hours

    int daysInMonth, startDay, numShiftsWeekday, numShiftsWeekend;
    vector<int> holidays;
    float weekdayNormalHours, weekendNormalHours;
    // vector<tuple<int, int, float>> customHours; // day, shift number, hours

    cout << "Enter information about the month to create the calender.\n\n";
    cout << "Enter the number of days in the month: ";
    cin >> daysInMonth;
    cout << "Enter the starting day of the month (0 = Monday, 6 = Sunday): ";
    cin >> startDay;

    // int specialDay, shiftNumber;
    // float specialHours;
    // while (true) {
    //     cout << "Enter a special day (1-31) with its new hours (-1 to quit): ";
    //     cin >> specialDay;
    //     if (specialDay == -1) {
    //         break;
    //     }

    //     cout << "Enter shift number for this day: ";
    //     cin >> shiftNumber;

    //     cout << "Enter the new hours for day " << specialDay << ": ";
    //     cin >> specialHours;
    //     if (specialDay >= 1 && specialDay <= 31) {
    //         customHours.push_back(make_tuple(specialDay, shiftNumber, specialHours));
    //     } else {
    //         cout << "Invalid entry.\n";
    //     }
    // }



    delete masterSchedule;
    // masterSchedule = new Schedule(daysInMonth, startDay, holidays, weekdayNormalHours, weekendNormalHours, customHours);
    masterSchedule = new Schedule(daysInMonth, startDay);
    cout << "Schedule created successfully.\n";

    return MENU;
}

ProgramState handlePrintSchedule(const Schedule* masterSchedule) {
    if (masterSchedule) {
        masterSchedule->printInfo();
    } else {
        cout << "No schedule loaded. Load a schedule first.\n";
    }

    return MENU;
}