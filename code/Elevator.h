#ifndef ELEVATOR_H
#define ELEVATOR_H

#include <vector>

#include "Display.h"

class Elevator {
    public:
        Elevator(int maxLoad);

        // User Actions
        bool closeDoors(); // Triggered by button or automatically, attempts to close door returns false and triggers obstruction if fails
        bool openDoors(); // Triggered by button or automatically
        bool requestFloor(Floor f); // Floor f button pressed
        void helpButton(); // Help button pressed

        // System Actions
        bool fulfillRequest(); // Ascends/Descends one floor towards nearest floor requests 
        void alertECS();
        bool flagEmergency(EmergencyStatus e); // Appends emergency code to emergencyStatus
        bool clearEmergency(EmergencyStatus e);
        bool addFloorRequest(Floor f);
        bool overrideGoToFloor(Floor f); // Bypasses all requests and goes to floor f
        void updateDisplay(Floor f);
        bool pollObstructionSensor(); // False if no obstruction, true otherwise

        // Getters
        Floor getFloor() const;
        Direction getDirection() const;
        DoorStatus getDoorStatus() const;
        ElevatorStatus getStatus() const;
        EmergencyStatus getEmergencyStatus() const;
        Display* getDisplay();

        // Other
        bool underLimit(); // Checks if load is under the limit
        void kickPassengersOut();

    private:
        Floor floor;
        Direction direction;
        DoorStatus doorStatus;
        ElevatorStatus elevatorStatus;
        EmergencyStatus emergencyStatus;
        std::vector<Floor> requests;
        Display* display;

        int load;
        int maxLoad;

        bool setStatus(ElevatorStatus e); // Idle, moving or error

};

#endif