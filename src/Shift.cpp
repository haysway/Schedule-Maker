#include "../include/Shift.h"

#include <iostream>
#include <algorithm>
#include <random>

using std::endl;
using std::cout;

Shift::Shift(int shiftType, float hours)
: shiftType(shiftType), hours(hours) {}

void Shift::decideWorkers(vector<Worker*>& boys, vector<Worker*>& girls, int day) {
    if (shiftType != -1) {  // if shift exists
        vector<Worker*> tempBoys = boys;
        vector<Worker*> tempGirls = girls;
        // check if they asked for the day off
        Worker::checkForDayOff(tempBoys, tempGirls, day);
        // sort the vectors by hours
        Worker::sortByHours(tempBoys, tempGirls);

        // if enough workers
        if (tempBoys.size() + tempGirls.size() >= 3) {
            if (tempBoys.size() == 1) {
                // in this case, shift must be the boy and first 2 girls
                this->staff.push_back(tempBoys[0]);
                this->staff.push_back(tempGirls[0]);
                this->staff.push_back(tempGirls[1]);

                tempBoys[0]->updateHours(this->hours);
                tempGirls[0]->updateHours(this->hours);
                tempGirls[1]->updateHours(this->hours);
                return;
            } else if (tempGirls.size() == 1) {
                // in this case, shift must be the girl and first 2 boys
                this->staff.push_back(tempGirls[0]);
                this->staff.push_back(tempBoys[0]);
                this->staff.push_back(tempBoys[1]);

                tempGirls[0]->updateHours(this->hours);
                tempBoys[0]->updateHours(this->hours);
                tempBoys[1]->updateHours(this->hours);
                return;
            } else {
                // else we have enough avaliable to base soley off of hours
                // 'zip' the two vectors together, by hours
                // parse from the front of the vector as long as the hours are equal
                // if we encounter a higher hour value before we get 3 deep, keep going until we get 3 deep
                // if there are more than 3 people with the same hours,
                //  shuffle them and select 3 at random
                vector<Worker*> allWorkers;
                allWorkers.insert(allWorkers.end(), tempBoys.begin(), tempBoys.end());
                allWorkers.insert(allWorkers.end(), tempGirls.begin(), tempGirls.end());

                Worker::sortByHours(allWorkers);

                vector<Worker*> sameHourWorkers;
                float prevHours = -1.0;

                for (auto& worker : allWorkers) {
                    if (worker->getHours() == prevHours) {
                        sameHourWorkers.push_back(worker);
                    } else {
                        if (sameHourWorkers.size() > 3) {
                            // shuffle the sameHourWorkers and pick 3 at random
                            shuffle(sameHourWorkers.begin(), sameHourWorkers.end(), std::mt19937{std::random_device{}()});
                            this->staff.insert(this->staff.end(), sameHourWorkers.begin(), sameHourWorkers.begin() + 3);
                            sameHourWorkers[0]->updateHours(this->hours);
                            sameHourWorkers[1]->updateHours(this->hours);
                            sameHourWorkers[2]->updateHours(this->hours);
                            return;
                        } else if (sameHourWorkers.size() == 0) {
                            sameHourWorkers.clear();
                            sameHourWorkers.push_back(worker);
                        } else {
                            this->staff.insert(this->staff.end(), allWorkers.begin(), allWorkers.begin() + 3);
                            sameHourWorkers[0]->updateHours(this->hours);
                            sameHourWorkers[1]->updateHours(this->hours);
                            sameHourWorkers[2]->updateHours(this->hours);
                            return;
                        }
                    }
                    prevHours = worker->getHours();
                }
                // shuffle the sameHourWorkers and pick 3 at random
                shuffle(sameHourWorkers.begin(), sameHourWorkers.end(), std::mt19937{std::random_device{}()});
                this->staff.insert(this->staff.end(), sameHourWorkers.begin(), sameHourWorkers.begin() + 3);
                sameHourWorkers[0]->updateHours(this->hours);
                sameHourWorkers[1]->updateHours(this->hours);
                sameHourWorkers[2]->updateHours(this->hours);
            }
        }
    }
}

void Shift::printInfo() {
    cout << "Shift: " << this->shiftType << endl;
    cout << "Hours: " << this->hours << endl;
    cout << "Workers:\n";
    for (auto& person : this->staff) {
        cout << "\t" << person->getName() << endl;
    }
    cout << "\n\n\n";
}