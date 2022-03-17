# Lifts-Management

## Description  
This is a simulation for managing the lifts in a building. The number of lifts and users are inputted by the user.  
  
While the code is running, a new request for a lift can be made at any time in the format: ```1 3```, where the numbers are the source and destination floors. Input ```-1``` to end the program.  
  
The status of all the lifts are printed every 4 seconds, & the algorithm is implemented such that the waiting time is minimised.

## Running the code  
```
g++ master.cpp elevator.cpp;   
./a.out  
```
