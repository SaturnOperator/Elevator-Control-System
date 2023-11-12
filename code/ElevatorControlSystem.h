#ifndef ELEVATORCONTROLSYSTEM_H
#define ELEVATORCONTROLSYSTEM_H

#include <QThread>
#include <QEventLoop>
#include <QComboBox>


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
        bool helpSafetySequence(Elevator* e);
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
        QComboBox* getOverloadSelector() const;
        QComboBox* getObstructionSelector() const;

    private:
        int numFloors;
        QList<Elevator*> elevators;
        QMap<int, QMap<Direction, QElevatorButton*>> floorButtons;
        int emergencyStatus;
        QPushButton* outageTestButton;
        QPushButton* fireTestButton;
        QPushButton* helpResponseButton;
        QList<QPushButton*> adminButtons;
        QComboBox* overloadSelector;
        QComboBox* obstructionSelector;

        QTimer* helpTimer;
        QEventLoop* helpLoop;
        bool helpCallResponded;

        QList<QThread*> elevatorThreads; // Run each elevator on its own thread

        void toggleEmergencyState(EmergencyStatus e);
};

#endif