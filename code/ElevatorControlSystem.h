#ifndef ELEVATORCONTROLSYSTEM_H
#define ELEVATORCONTROLSYSTEM_H

#include "Elevator.h"

class ElevatorControlSystem : public QObject {
    Q_OBJECT

    public:
        ElevatorControlSystem(int numFloors, int numElevators);
        
        // User Actions
        bool requestFloor(Floor f, Direction dir);

        // System Actions
        Elevator* findBestElevator(int floor = 1);
        void elevatorRequest(Elevator* e, Floor f);
        void updateButtons();

        // Emergency Actions
        void helpSafetySequence();
        bool helpReceiveResponse(Elevator* e);
        bool helpCallBuilding();
        void helpCall911();
        void addressEmergency(Elevator* e, EmergencyStatus status);

        void fireSafetySequence();
        void outageSafetySequence();

        Elevator* getElevator(int i);
        int getNumElevators();
        int getNumFloors();
        QElevatorButton* getFloorButton(int floor, Direction dir);

    private:
        QList<Elevator*> elevators;
        QMap<int, QMap<Direction, QElevatorButton*>> floorButtons;
        int numFloors;
};

#endif