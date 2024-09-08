#include "../include/Schedule.h"

#include <iostream>
#include <algorithm>
#include <iomanip>
#include <unordered_map>
#include <unordered_set>
#include <fstream>


Schedule::Schedule(int daysInMonth, int startDay, vector<Worker*>& workers, bool summer, const vector<int>& holidays) 
: daysInMonth(daysInMonth), startDay(startDay), workers(workers), summer(summer)
{
    createShifts(holidays);
}

void Schedule::createShifts(const vector<int>& holidays) 
{   

    unordered_set<int> holidaysSet(holidays.begin(), holidays.end());


    for (int day = 1; day <= daysInMonth; day++) {
        int weekDay = (startDay + day - 1) % 7;                         // calculate the weekday for the given start day

        if (holidaysSet.find(day) != holidaysSet.end()) {
            continue;
        }

        if (weekDay == 6) {
            shifts.emplace_back(Shift(day, 7, 0));                      // set shift to 7 if day is Sunday (placeholder value)
        } else if (weekDay == 5) {                                      // all saturdays are the same (both shifts 4 hours)
            shifts.emplace_back(Shift(day, 1, 4));
            shifts.emplace_back(Shift(day, 2, 4));

        } else {                                                        // else weekday (summer is different)

            if (summer) {                                               // if summer, three shifts                        
                    shifts.emplace_back(Shift(day, 0, 1));          
                    shifts.emplace_back(Shift(day, 1, 4));              // THESE HOURS NEED UPDATED
                    shifts.emplace_back(Shift(day, 2, 4)); 
            } else {
                shifts.emplace_back(Shift(day, 2, 4.5));                // else school year - one shift (4 and a half hours)
            }

        }

    }
}

void Schedule::assignWorkersToShifts()
{
    // alternate having two boys or two girls in a shift
    bool prioritizeBoys = true;

    unordered_map<string, Worker*> workerMap;
    for (Worker* worker : workers) {
        workerMap[worker->getName()] = worker;
    }

    for (auto& shift : shifts) {                                            // for every shift in the shifts vector

        // get the day and the type (0-2)
        int shiftDay = shift.getDay();
        int shiftType = shift.getShiftType();

        if (shiftType != 7) {                                               // Skip if it's Sunday - no shifts

            // two vectors, one for boys one for girls
            vector<Worker*> boys, girls;                                           
            // vector to keep track of the workers of the previous shift
            vector<Worker*> previousShiftWorkers;

            if (shiftType > 0) {                                                                            // if not lapswim
                for (const auto& prevShift : shifts) {                                             

                    if (prevShift.getDay() == shiftDay && prevShift.getShiftType() == shiftType - 1) {      // if the previous shift is on the same day

                        // loop through the previous shift and add each worker to the previousShiftWorkers vector
                        for (const auto& workerName : prevShift.getWorkers()) {                             
                            auto it = workerMap.find(workerName);
                            if (it != workerMap.end()) {
                                previousShiftWorkers.emplace_back(it->second);
                            }
                        }
                        break;
                    }

                }
            }

            default_random_engine rng(static_cast<unsigned>(time(nullptr)));

            shuffle(workers.begin(), workers.end(), rng);  

            for (Worker* worker : workers) {                                        // for each worker
                if (worker->isAvailable(shiftDay) && find(previousShiftWorkers.begin(), previousShiftWorkers.end(), worker) == previousShiftWorkers.end()) {                                                                                 // if not requested off

                    if (worker->getGender() == 1) {                                 // add them to the boys vector
                        boys.emplace_back(worker);
                    } else {                                                        // or girls vector
                        girls.emplace_back(worker);
                    }

                }
            }

            // if not enough people (<3) or no girls or no boys, there are not enough of each gender. say so
            if (boys.size() + girls.size() < 3 || boys.empty() || girls.empty()) {                                                      
                cerr << "Not enough available workers of different genders for Shift " << shiftType << " on Day " << shiftDay << endl;
                for(int i = 0; i < boys.size(); i++) {
                    cout << boys[i]->getName();
                }
                for(int i = 0; i < girls.size(); i++) {
                    cout << girls[i]->getName();
                }
                if (boys.empty() && girls.empty()) {
                    cout << "Everyone requested this day off!!" << endl;
                }
                cout << endl;
                continue;
            }

            // Sort both boys and girls by the total hours worked in ascending order
            std::sort(boys.begin(), boys.end(), [](Worker* a, Worker* b) {
                return a->getTotalHoursWorked() < b->getTotalHoursWorked();
            });
            std::sort(girls.begin(), girls.end(), [](Worker* a, Worker* b) {
                return a->getTotalHoursWorked() < b->getTotalHoursWorked();
            });

            // Assign one girl and two boys, or two girls and one boy
            if (shiftType == 0) {                                                   // Shift 0 has 2 workers, so assign one of each
                addWorkers(shift, boys, 1);
                addWorkers(shift, girls, 1);
            } else {                                                                // Shifts 1 and 2 have 3 workers, so assign one girl and two boys (or vice versa)
                if ((boys.size() >= 2) && (girls.size() >= 2)) {                    // if enough of each gender

                    if (prioritizeBoys) {                                           // add two boys
                        addWorkers(shift, boys, 2);
                        addWorkers(shift, girls, 1);
                        prioritizeBoys = false;
                    } else {                                                        // or add two girls
                        addWorkers(shift, girls, 2);
                        addWorkers(shift, boys, 1);
                        prioritizeBoys = true;
                    }

                } else if (boys.size() >= 2) {                                      // else if enough boys but not enough girls
                    addWorkers(shift, boys, 2);
                    addWorkers(shift, girls, 1);
                } else {                                                            // else there are enough girls but not enough boys
                    addWorkers(shift, girls, 2);
                    addWorkers(shift, boys, 1);
                }
            }
        }
    }

}

void Schedule::addWorkers(Shift& shift, vector<Worker*> workerVector, int amountToAdd) {
    for(int i = 0; i < amountToAdd; i++) {
        shift.addWorker(workerVector[i]->getName());
        workerVector[i]->updateHours(shift.getAmountHours());
        workerVector[i]->updateShiftsWorked();
    }
}

void Schedule::printSchedule() const
{
    vector<string> daysOfWeek = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};

    // organize shifts into a map by day and shift type
    unordered_map<int, vector<Shift>> shiftsByDay;
    for (const auto& shift : shifts) {
        shiftsByDay[shift.getDay()].emplace_back(shift);
    }

    int currentDay = 1;
    int weekDay = startDay;

    while (currentDay <= daysInMonth) {
        cout << daysOfWeek[weekDay] << " " << currentDay << endl;                                   // Print the day of the week and day number

        if (weekDay == 6) {                                                                         // Check if it's a Sunday (no shifts)
            cout << "No shifts" << endl;
        } else {
            auto dayShiftsIt = shiftsByDay.find(currentDay);

            if (dayShiftsIt != shiftsByDay.end()) {
                bool hasShifts = false;                                                             // Flag to check if any shifts are present

                const auto& dayShifts = dayShiftsIt->second;

                for (int shiftType = 0; shiftType <= 2; ++shiftType) {                              // Print shifts for the current day
                    bool shiftPrinted = false;

                    for (const auto& shift : dayShifts) {

                        if (shift.getShiftType() == shiftType) {                                    // check to make sure we're in the right spot

                            if (!shiftPrinted) {
                                cout << "Shift " << shiftType << " ";
                                shiftPrinted = true;                                 
                            }

                            const auto& workersList = shift.getWorkers();                           // store the assigned workers to workersList (carefully)
                            cout << "[";
                            for (size_t i = 0; i < workersList.size(); ++i) {                       // for each name in the list print it
                                if (i > 0) cout << ", ";
                                    cout << workersList[i];
                            }
                            cout << "]" << endl;

                            hasShifts = true;                                                       // that day has shifts

                        }

                    }

                    if (shiftPrinted) {
                        cout << endl;
                    }

                }

                if (!hasShifts) {
                    cout << "No shifts" << endl;
                }

            } else {
                cout << "No shifts" << endl;
            }
        }

        cout << endl;                                                   

        // Move to the next day and weekday
        ++currentDay;
        weekDay = (weekDay + 1) % 7;
    }

}

void Schedule::printScheduleToCVS(const string& scheduleFile) const
{

    vector<string> daysOfWeek = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};

    // // Open a file in write mode
    ofstream outfile(scheduleFile);

    if (!outfile.is_open()) {
        cerr << "Error opening file!" << endl;
        return;
    }

    // Write the days of the week as the header row
    for (const auto& day : daysOfWeek) {
        outfile << day << ",";
    }
    outfile << endl;

    // organize shifts into a map by day and shift type
    unordered_map<int, vector<Shift>> shiftsByDay;
    for (const auto& shift : shifts) {
        shiftsByDay[shift.getDay()].emplace_back(shift);
    }

    int currentDay = 1;
    int weekDay = startDay;
    for(int i = 0; i < startDay; i++) {
        outfile << "No shifts,";
    }

    while (currentDay <= daysInMonth) {

        if (weekDay == 6) {                                                                         // Check if it's a Sunday (no shifts)
            outfile << "No shifts," << endl;
        } else {
            auto dayShiftsIt = shiftsByDay.find(currentDay);

            if (dayShiftsIt != shiftsByDay.end()) {
                bool hasShifts = false;                                                             // Flag to check if any shifts are present

                const auto& dayShifts = dayShiftsIt->second;

                for (int shiftType = 0; shiftType <= 2; ++shiftType) {                              // Print shifts for the current day
                    bool shiftPrinted = false;

                    for (const auto& shift : dayShifts) {

                        if (shift.getShiftType() == shiftType) {                                    // check to make sure we're in the right spot

                            if (!shiftPrinted) {
                                outfile << "Shift " << shiftType << " ";
                                shiftPrinted = true;                                 
                            }

                            const auto& workersList = shift.getWorkers();                           // store the assigned workers to workersList (carefully)
                            outfile << "[";
                            for (size_t i = 0; i < workersList.size(); ++i) {                       // for each name in the list print it
                                if (i > 0) outfile << " ";
                                outfile << workersList[i];
                            }
                            outfile << "]";

                            hasShifts = true;                                                       // that day has shifts

                        }

                    }

                }

                if (!hasShifts) {
                    outfile << "No shifts" << endl;
                }

                outfile << ",";

            } else {
                outfile << "No shifts," << endl;
            }
        }                                                 

        // Move to the next day and weekday
        ++currentDay;
        weekDay = (weekDay + 1) % 7;

    }
    
    for(int i = weekDay; i < 7; i++) {
        outfile << "No shifts,";
    }


    outfile << endl;
    outfile.close();

    cout << "Schedule written to " << scheduleFile << endl;





}