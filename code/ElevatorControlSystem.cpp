#include "ElevatorControlSystem.h"

ElevatorControlSystem::ElevatorControlSystem(int numberFloors, int numberElevators){
    numFloors = numberFloors;

    // Dynamically create and add each elevator
    for (int i = 0; i < numberElevators; i++) {
        Elevator* e = new Elevator(this);
        elevators << e;
    }

    for (int i = 1; i <= numFloors; i++) {
        if(i == numFloors){
            floorButtons[i][Direction::UP] = new QElevatorButton("");
        } else {
            QElevatorButton* buttonUp = new QElevatorButton("");
            floorButtons[i][Direction::UP] = buttonUp;
            // Find best elevator and add floor to elevator's requests
            connect(buttonUp, &QPushButton::clicked, this, [this, i, buttonUp]() {
                Elevator* e = findBestElevator(i);
                e->requestFloor(i, Direction::UP);
                buttonUp->on();
            });
        }

        if(i == 1){
            floorButtons[i][Direction::DOWN] = new QElevatorButton("");
        } else {
            QElevatorButton* buttonDown = new QElevatorButton("");
            floorButtons[i][Direction::DOWN] = buttonDown;
            // Find best elevator and add floor to elevator's requests
            connect(buttonDown, &QPushButton::clicked, this, [this, i, buttonDown]() {
                Elevator* e = findBestElevator(i);
                e->requestFloor(i, Direction::DOWN);
                buttonDown->on();
            });
        }
    }
}

Elevator* ElevatorControlSystem::getElevator(int i){
    if(i < 0 || i > getNumElevators()){
        return nullptr;
    }
    return elevators[i];
}

int ElevatorControlSystem::getNumElevators() const{
    return elevators.size();
}

int ElevatorControlSystem::getNumFloors() const{
    return numFloors;
}

QElevatorButton* ElevatorControlSystem::getFloorButton(int floor, Direction dir){
    if(floor < 1 || floor > numFloors){
        return nullptr;
    }
    return floorButtons[floor][dir];
}


Elevator* ElevatorControlSystem::findBestElevator(int floor){
    if (elevators.isEmpty()) {
        return nullptr;
    }

    Elevator* best = elevators.at(0);
    int closestDistance = abs(best->getFloor() - floor);

    for(Elevator* e : elevators){
        int currentDistance = abs(e->getFloor() - floor);
        if (currentDistance < closestDistance) {
            best = e;
            closestDistance = currentDistance;
        }
    }

    return best;
}