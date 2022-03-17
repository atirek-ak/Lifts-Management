#include <iostream>
#include <vector> 

using namespace std;

class Elevator 
{
	private:
        bool idle;
        int floor;
        bool open;
        vector<int> stopFloors;


	public:
        Elevator();
        bool checkIdle();
        int getFloor();
        bool checkOpen();
        int firstDestination();
        void appendRequests(int source, int destination);
        void setIdle(bool idleness);
        void setFloor(int num);
        void setOpen(bool openn);
        void removeDestination();
};