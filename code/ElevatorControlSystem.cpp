#include "ElevatorControlSystem.h"

ElevatorControlSystem::ElevatorControlSystem(int numberFloors, int numberElevators){
    numFloors = numberFloors;

    // Dynamically create and add each elevator
    for (int i = 0; i < numberElevators; i++) {
        Elevator* e = new Elevator();
        elevators << e;
    }
}

Elevator* ElevatorControlSystem::getElevator(int i){
    if(i < 0 || i >= getNumElevators()){
        return nullptr;
    }

    return elevators[i];
}

int ElevatorControlSystem::getNumElevators(){
    return elevators.size();
}

int ElevatorControlSystem::getNumFloors(){
    return numFloors;
}