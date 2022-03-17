#include <iostream>
#include <vector> 
#include "elevator.h"

using namespace std;

Elevator::Elevator()
{
    idle = true;
    floor = 0;
    open  = false;
}

bool Elevator::checkIdle()
{
    return idle;
}

void Elevator::setIdle(bool idleness)
{
    idle = idleness;
}

int Elevator::getFloor()
{
    return floor;
}

void Elevator::setFloor(int num)
{
    floor = num;
}

bool Elevator::checkOpen()
{
    return open;
}

void Elevator::setOpen(bool openn)
{
    open = openn;
}

int Elevator::firstDestination()
{
    if(stopFloors.size() > 0)
        return stopFloors[0];
    return -1;
}

void Elevator::appendRequests(int source, int destination)
{
    stopFloors.push_back(source);
    stopFloors.push_back(destination);
    if(source < destination)
        sort(stopFloors.begin(),stopFloors.end());
    else
        sort(stopFloors.begin(),stopFloors.end(), greater<int>());
}

void Elevator::removeDestination()
{
    stopFloors.erase(stopFloors.begin());
}
