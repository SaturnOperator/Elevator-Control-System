#ifndef ELEVATORCONTROLSYSTEM_H
#define ELEVATORCONTROLSYSTEM_H

#include "Elevator.h"

class ElevatorControlSystem {
    public:
        ElevatorControlSystem();
        
        // User Actions
        bool requestFloor(Floor f, Direction dir);

        // System Actions
        Elevator* findElevator() const;
        void elevatorRequest(Elevator* e, Floor f);
        void updateButtons();

        // Emergency Actions
        void helpSafetySequence();
        bool helpReceiveResponse(Elevator* e);
        bool helpCallBuilding();
        void helpCall911();
        void addressEmergency(Elevator* e, EmergencyStatus e);

        void fireSafetySequence();
        void outageSafetySequence();

    private:
        std::vector<Elevator*> elevators;
};

#endif