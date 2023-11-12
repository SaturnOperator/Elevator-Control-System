#ifndef ELEVATOR_H
#define ELEVATOR_H

// #include <QMap>
#include <QList>
#include <QDebug>
#include <QTimer>

#include "QElevatorPanel.h"
#include "QElevatorModel.h"

class ElevatorControlSystem;

class Elevator : public QObject {
    Q_OBJECT

    public:
        Elevator(ElevatorControlSystem* ecs);

        // User Actions
        bool closeDoors(); // Triggered by button or automatically, attempts to close door returns false and triggers obstruction if fails
        bool openDoors(); // Triggered by button or automatically
        bool requestFloor(int floor, Direction dir = Direction::NONE); // Floor f button pressed
        bool helpButton(); // Help button pressed

        // System Actions
        bool fulfillRequest(); // Ascends/Descends one floor towards nearest floor requests 
        bool moveUp();
        bool moveDown();
        void updateFloorIndicators();
        void updateElevatorButtons();

        void alertECS(EmergencyStatus e);
        void flagEmergency(EmergencyStatus e); // Appends emergency code to emergencyStatus
        void clearEmergency(EmergencyStatus e);
        bool addFloorRequest(int floor);
        bool overrideGoToFloor(int floor); // Bypasses all requests and goes to floor f

        // Getters
        int getFloor() const;
        Direction getDirection() const;
        DoorStatus getDoorStatus() const;
        ElevatorStatus getStatus() const;
        int getEmergencyStatus() const;
        QElevatorPanel* getPanel() const;
        QElevatorModel* getModel() const;

        // Other
        bool underLimit(); // Checks if load is under the limit
        void kickPassengersOut();

    private:
        ElevatorControlSystem* ecs;
        int floor;
        Direction direction;
        DoorStatus doorStatus;
        ElevatorStatus elevatorStatus;
        int emergencyStatus;
        // QMap<int, Direction> requests; // Stores all the floor requests in order, fulfillRequest() completes these requests
        QList<int> requests; // Stores all the floor requests in order, fulfillRequest() completes these requests
        QElevatorPanel* panel;
        QElevatorModel* model;

        QTimer* timer;

        int load;
        int maxLoad;

        bool setStatus(ElevatorStatus e); // Idle, moving or error

};

#endif