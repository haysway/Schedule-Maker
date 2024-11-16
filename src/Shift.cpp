#include "../include/Shift.h"

Shift::Shift(int day, int shiftType, float amountHours) : day(day), shiftType(shiftType), amountHours(amountHours)
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

float Shift::getAmountHours() const
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