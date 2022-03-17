#include <iostream>
#include "elevator.h"
#include <string> 
#include <vector> 
#include <thread>
#include <iterator>
#include <set>


using namespace std;

class Request
{
    public:
        int source, destination;
        Request(int src, int dest)
        {
            source = src;
            destination = dest;
        }

        bool operator< (const Request &left) const
        {
            return source < left.source;
        }

};

bool inputContinue = true;
int num_elev, num_floors;
set<Request> requests;

void inputFunc()
{    
    while(true)
    {
        int source, destination;
        cin >> source;
        if(source == -1)
        {
            inputContinue = false;
            return;
        }
        cin >> destination;
        if(source < 0 || source >= num_floors || destination < 0 || destination >= num_floors || source == destination)
        {
            cout << "Invalid input!" << endl;
            continue;
        }
        Request temp(source, destination);
        requests.insert(temp);
    }
}

int main()
{
	cout << "Input number of floors: ";
	cin >> num_floors;
	cout << "Input number of elevators: ";
	cin >> num_elev;
	// Lobby l = Lobby(num_elev, num_floors);
    vector<Elevator> lifts(num_elev, Elevator());
    cout << "Input source and destination. Input -1 to end program." << endl;
    thread inputThread(inputFunc);
    int time = 0;
	while(inputContinue)
    {
        cout << "T=" << time << endl;
        for(int i=1;i<=num_elev;i++)
        {
            cout << "Lift " << i << "-->" << lifts[i-1].getFloor() << " (" << (lifts[i-1].checkOpen()?"Open":"Close") << "),";
        }
        cout << endl;
        this_thread::sleep_for(chrono::milliseconds(4000) );
        time++;
        
        // check if any requests can be fulfilled
        for(auto it=requests.begin();it!=requests.end();)
        {
            Request cur = *it;
            int min_time_taken = INT_MAX;
            int lift_number = -1;
            for(int i=0;i<num_elev;i++)
            {
                if(lifts[i].checkIdle() || (cur.source > lifts[i].getFloor() && lifts[i].getFloor() < lifts[i].firstDestination() && cur.source < cur.destination) 
                || (cur.source > cur.destination && cur.source < lifts[i].getFloor() && lifts[i].getFloor() > lifts[i].firstDestination()))
                {
                    int time_taken = abs(cur.source - lifts[i].getFloor());
                    if(time_taken < min_time_taken)
                    {
                        min_time_taken = time_taken;
                        lift_number = i;
                    }
                }
            }
            if(lift_number != -1)
            {
                lifts[lift_number].appendRequests(cur.source, cur.destination);
                lifts[lift_number].setIdle(false);
                it = requests.erase(it);
            }
            else 
                it++;
        }

        // update lifts for next iteration
        for(int i=0;i<num_elev;i++)
        {
            if(!lifts[i].checkIdle())
            {
                if(lifts[i].checkOpen())
                {
                    lifts[i].setOpen(false);
                    lifts[i].removeDestination();
                    if(lifts[i].firstDestination() == -1)
                        lifts[i].setIdle(true);
                }
                else
                {
                    if(lifts[i].getFloor() == lifts[i].firstDestination())
                    {
                        lifts[i].setOpen(true);
                    }
                    else
                    {
                        if(lifts[i].getFloor() < lifts[i].firstDestination())
                            lifts[i].setFloor(lifts[i].getFloor() + 1);
                        else
                            lifts[i].setFloor(lifts[i].getFloor() - 1);
                    }
                }

            }
        }


	}
    inputThread.join();
	return 0;
}