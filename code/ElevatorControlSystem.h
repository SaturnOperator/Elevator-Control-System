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
        void resetButtons();

        // Emergency Actions
        void helpSafetySequence();
        bool helpReceiveResponse(Elevator* e);
        bool helpCallBuilding();
        void helpCall911();
        void addressEmergency(Elevator* e, EmergencyStatus status);

        void activateFireSafetySequence();
        void clearFire();
        void activateOutageSafetySequence();
        void clearOutage();

        int getNumElevators() const;
        int getNumFloors() const;
        Elevator* getElevator(int i);
        QElevatorButton* getFloorButton(int floor, Direction dir);
        QList<QPushButton*> getAdminButtons() const;

    private:
        int numFloors;
        QList<Elevator*> elevators;
        QMap<int, QMap<Direction, QElevatorButton*>> floorButtons;
        int emergencyStatus;
        QPushButton* outageTestButton;
        QPushButton* fireTestButton;
        QPushButton* helpResonseButton;
        QList<QPushButton*> adminButtons;

        void toggleEmergencyState(EmergencyStatus e);
};

#endif