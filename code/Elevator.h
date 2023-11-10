#ifndef ELEVATOR_H
#define ELEVATOR_H

#include <QList>

#include "Display.h"
#include "QElevatorPanel.h"
#include "QElevatorModel.h"

class Elevator {
    public:
        Elevator();

        // User Actions
        bool closeDoors(); // Triggered by button or automatically, attempts to close door returns false and triggers obstruction if fails
        bool openDoors(); // Triggered by button or automatically
        bool requestFloor(int floor); // Floor f button pressed
        void helpButton(); // Help button pressed

        // System Actions
        bool fulfillRequest(); // Ascends/Descends one floor towards nearest floor requests 
        void alertECS();
        bool flagEmergency(EmergencyStatus e); // Appends emergency code to emergencyStatus
        bool clearEmergency(EmergencyStatus e);
        bool addFloorRequest(int floor);
        bool overrideGoToFloor(int floor); // Bypasses all requests and goes to floor f
        void updateDisplay(int floor);
        bool pollObstructionSensor(); // False if no obstruction, true otherwise

        // Getters
        int getFloor() const;
        Direction getDirection() const;
        DoorStatus getDoorStatus() const;
        ElevatorStatus getStatus() const;
        EmergencyStatus getEmergencyStatus() const;
        QElevatorPanel* getPanel();
        QElevatorModel* getModel();

        // Other
        bool underLimit(); // Checks if load is under the limit
        void kickPassengersOut();

    private:
        int floor;
        Direction direction;
        DoorStatus doorStatus;
        ElevatorStatus elevatorStatus;
        EmergencyStatus emergencyStatus;
        QList<int> requests; // Stores all the floor requests in order, fulfillRequest() completes these requests
        QElevatorPanel* panel;
        QElevatorModel* model;

        int load;
        int maxLoad;

        bool setStatus(ElevatorStatus e); // Idle, moving or error

};

#endif