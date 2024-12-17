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
    LOAD_ASSIGN_WORKERS,
    LOAD_PRINT_SCHEDULE,
    EXIT
};

ProgramState handleMenu();
ProgramState handleLoadWorkers(vector<Worker*>&);
ProgramState handleLoadSchedule(Schedule*& masterSchedule);
ProgramState handleAssignWorkers();
ProgramState handlePrintSchedule(const Schedule* masterSchedule);

int main()
{
    vector<Worker*> workers;    //TODO: initialize with nullptr
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
            case LOAD_ASSIGN_WORKERS:
                currentState = handleAssignWorkers();
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
    cout << "3 - Assign Workers\n";
    cout << "4 - Print Schedule\n";
    cout << "5 - Exit\n";
    cout << "Choice? ";
    cin >> choice;

    switch (choice) {
        case 1: return LOAD_WORKERS;
        case 2: return LOAD_SCHEDULE;
        case 3: return LOAD_ASSIGN_WORKERS;
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

    cout << "Enter information about the month to create the calender.\n\n";
    cout << "Enter the number of days in the month: ";
    cin >> daysInMonth;
    cout << "Enter the starting day of the month (0 = Monday, 6 = Sunday): ";
    cin >> startDay;

    delete masterSchedule;
    masterSchedule = new Schedule(daysInMonth, startDay);
    cout << "Schedule created successfully.\n";

    return MENU;
}

ProgramState handleAssignWorkers() {
    // A state to assign all the workers to their shifts, completing the schedule
    // TODO: change all vectors of Workers to hold pointers: reducing copying
    // logic will be the same as previously

    return MENU;
}

ProgramState handlePrintSchedule(const Schedule* masterSchedule) {
    // prints out the schedule, and returns to MENU state
    if (masterSchedule) {
        masterSchedule->printInfo();
    } else {
        cout << "No schedule loaded. Load a schedule first.\n";
    }

    return MENU;
}