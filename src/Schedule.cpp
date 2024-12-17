#include "../include/Schedule.h"

#include <iostream>
#include <algorithm>

using std::cout;
using std::endl;
using std::cin;
using std::pair;

// void Schedule::assignWorkersToShifts()
// {
//     // alternate having two boys or two girls in a shift
//     bool prioritizeBoys = true;

//     unordered_map<string, Worker*> workerMap;
//     for (Worker* worker : workers) {
//         workerMap[worker->getName()] = worker;
//     }

//     for (auto& shift : shifts) {                                            // for every shift in the shifts vector

//         // get the day and the type (0-2)
//         int shiftDay = shift.getDay();
//         int shiftType = shift.getShiftType();

//         if (shiftType != 7) {                                               // Skip if it's Sunday - no shifts

//             // two vectors, one for boys one for girls
//             vector<Worker*> boys, girls;                                           
//             // vector to keep track of the workers of the previous shift
//             vector<Worker*> previousShiftWorkers;

//             if (shiftType > 0) {                                                                            // if not lapswim
//                 for (const auto& prevShift : shifts) {                                             

//                     if (prevShift.getDay() == shiftDay && prevShift.getShiftType() == shiftType - 1) {      // if the previous shift is on the same day

//                         // loop through the previous shift and add each worker to the previousShiftWorkers vector
//                         for (const auto& workerName : prevShift.getWorkers()) {                             
//                             auto it = workerMap.find(workerName);
//                             if (it != workerMap.end()) {
//                                 previousShiftWorkers.emplace_back(it->second);
//                             }
//                         }
//                         break;
//                     }

//                 }
//             }

//             // Create a Mersenne Twister engine
//             std::mt19937 rng(std::random_device{}());

//             // Seed the engine with a combination of system time and hardware randomness
//             auto now = std::chrono::high_resolution_clock::now();
//             auto seed = now.time_since_epoch().count() ^ rng();
//             rng.seed(seed);

//             shuffle(workers.begin(), workers.end(), rng);  

//             for (Worker* worker : workers) {                                        // for each worker
//                 if (worker->isAvailable(shiftDay) && find(previousShiftWorkers.begin(), previousShiftWorkers.end(), worker) == previousShiftWorkers.end()) {                                                                   // if not requested off

//                     if (worker->getGender() == 1) {                                 // add them to the boys vector
//                         boys.emplace_back(worker);
//                     } else {                                                        // or girls vector
//                         girls.emplace_back(worker);
//                     }

//                 }
//             }

//             // if not enough people (<3) or no girls or no boys, there are not enough of each gender. say so
//             if (boys.size() + girls.size() < 3 || boys.empty() || girls.empty()) {                                                      
//                 cerr << "Not enough available workers of different genders for Shift " << shiftType << " on Day " << shiftDay << endl;
//                 for(int i = 0; i < boys.size(); i++) {
//                     cout << boys[i]->getName();
//                 }
//                 for(int i = 0; i < girls.size(); i++) {
//                     cout << girls[i]->getName();
//                 }
//                 if (boys.empty() && girls.empty()) {
//                     cout << "Everyone requested this day off!!" << endl;
//                 }
//                 cout << endl;
//                 continue;
//             }

//             // Sort both boys and girls by the total hours worked in ascending order
//             std::sort(boys.begin(), boys.end(), [](Worker* a, Worker* b) {
//                 return a->getTotalHoursWorked() < b->getTotalHoursWorked();
//             });
//             std::sort(girls.begin(), girls.end(), [](Worker* a, Worker* b) {
//                 return a->getTotalHoursWorked() < b->getTotalHoursWorked();
//             });

//             ////
//             // std::cout << "Sorted Boys List:\n";
//             // for (Worker* boy : boys) {
//             //     std::cout << boy->getName() << ": " << boy->getTotalHoursWorked() << " hours\n";
//             // }

//             // // Print the sorted girls list
//             // std::cout << "\nSorted Girls List:\n";
//             // for (Worker* girl : girls) {
//             //     std::cout << girl->getName() << ": " << girl->getTotalHoursWorked() << " hours\n";
//             // }
//             // cout << endl << endl;
//             ////


//             // Assign one girl and two boys, or two girls and one boy
//             if (shiftType == 0) {                                                   // Shift 0 has 2 workers, so assign one of each
//                 addWorkers(shift, boys, 1);
//                 addWorkers(shift, girls, 1);
//             } else {                                                                // Shifts 1 and 2 have 3 workers, so assign one girl and two boys (or vice versa)
//                 if ((boys.size() >= 2) && (girls.size() >= 2)) {                    // if enough of each gender

//                     if (prioritizeBoys) {                                           // add two boys
//                         addWorkers(shift, boys, 2);
//                         addWorkers(shift, girls, 1);
//                         prioritizeBoys = false;
//                     } else {                                                        // or add two girls
//                         addWorkers(shift, girls, 2);
//                         addWorkers(shift, boys, 1);
//                         prioritizeBoys = true;
//                     }

//                 } else if (boys.size() >= 2) {                                      // else if enough boys but not enough girls
//                     addWorkers(shift, boys, 2);
//                     addWorkers(shift, girls, 1);
//                 } else {                                                            // else there are enough girls but not enough boys
//                     addWorkers(shift, girls, 2);
//                     addWorkers(shift, boys, 1);
//                 }
//             }
//         }
//     }

// }

// void Schedule::addWorkers(Shift& shift, vector<Worker*> workerVector, int amountToAdd) {
//     for(int i = 0; i < amountToAdd; i++) {
//         shift.addWorker(workerVector[i]->getName());
//         workerVector[i]->updateHours(shift.getAmountHours());
//         workerVector[i]->updateShiftsWorked();
//     }
// }

// void Schedule::printScheduleToCVS(const string& scheduleFile) const
// {
//     // very similar to print schedule, just printing to a csv file, so some delimiters are added/removed

//     vector<string> daysOfWeek = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};

//     // // Open a file in write mode
//     ofstream outfile(scheduleFile);

//     if (!outfile.is_open()) {
//         cerr << "Error opening file!" << endl;
//         return;
//     }

//     // Write the days of the week as the header row
//     for (const auto& day : daysOfWeek) {
//         outfile << day << ",";
//     }
//     outfile << endl;

//     // organize shifts into a map by day and shift type
//     unordered_map<int, vector<Shift>> shiftsByDay;
//     for (const auto& shift : shifts) {
//         shiftsByDay[shift.getDay()].emplace_back(shift);
//     }

//     int currentDay = 1;
//     int weekDay = startDay;

//     for(int i = 0; i < startDay; i++) {
//         outfile << "NULL,";
//     }


//     while (currentDay <= daysInMonth) {

//         if (weekDay == 6) {                                                                         // Check if it's a Sunday (no shifts)
//             outfile << "No shifts Sunday," << endl;
//         } else {
//             auto dayShiftsIt = shiftsByDay.find(currentDay);

//             if (dayShiftsIt != shiftsByDay.end()) {
//                 bool hasShifts = false;                                                             // Flag to check if any shifts are present

//                 const auto& dayShifts = dayShiftsIt->second;

//                 for (int shiftType = 0; shiftType <= 2; ++shiftType) {                              // Print shifts for the current day
//                     bool shiftPrinted = false;

//                     for (const auto& shift : dayShifts) {

//                         if (shift.getShiftType() == shiftType) {                                    // check to make sure we're in the right spot

//                             if (!shiftPrinted) {
//                                 outfile << "Shift " << shiftType << " ";
//                                 shiftPrinted = true;                                 
//                             }

//                             const auto& workersList = shift.getWorkers();                           // store the assigned workers to workersList (carefully)
//                             outfile << "[";
//                             for (size_t i = 0; i < workersList.size(); ++i) {                       // for each name in the list print it
//                                 if (i > 0) outfile << " ";
//                                 outfile << workersList[i];
//                             }
//                             outfile << "]";

//                             hasShifts = true;                                                       // that day has shifts
//                         }
//                     }
//                 }

//                 if (!hasShifts) {
//                     outfile << "No shifts a";
//                 }

//                 outfile << ",";

//             } else {
//                 outfile << "No shifts b,";
//             }
//         }                                                 

//         // Move to the next day and weekday
//         ++currentDay;
//         weekDay = (weekDay + 1) % 7;

//     }
    
//     for(int i = weekDay; i < 7; i++) {
//         outfile << "NULL,";
//     }

//     outfile << endl;
//     outfile.close();

//     cout << "Schedule written to " << scheduleFile << endl;

// }


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
            this->days.push_back(Day(day, weekDay));
        } else if (itCustomDay != customDays.end()) {
            const auto& customShiftHours = itCustomDay->second;
            this->days.push_back(Day(day, weekDay, customShiftHours.size(), customShiftHours));
        } else if (weekDay <= 4) {
            // normal weekday
            this->days.push_back(Day(day, weekDay, numShiftsWeekday, weekdayHours));
        } else {
            // normal weekend
            this->days.push_back(Day(day, weekDay, numShiftsWeekend, weekendHours));
        }

    }
}

void Schedule::printInfo() const {
    int dayOfMonth = 1;
    for (auto day : this->days) {
        cout << dayOfMonth++ << endl;
        day.printInfo();
    }
}