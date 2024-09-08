#include "../include/Shift.h"

Shift::Shift(int day, int shiftType, int amountHours) : day(day), shiftType(shiftType), amountHours(amountHours)
{

}

int Shift::getDay() const
{
    return day;
}

int Shift::getShiftType() const
{
    return shiftType;
}

int Shift::getAmountHours() const
{
    return amountHours;
}

void Shift::addWorker(const string& workerName)
{
    assignedWorkers.emplace_back(workerName);
}

const vector<string>& Shift::getWorkers() const
{
    return assignedWorkers;
}