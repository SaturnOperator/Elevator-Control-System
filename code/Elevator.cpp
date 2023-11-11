#include "Elevator.h"
#include "ElevatorControlSystem.h" // Forward declaration

Elevator::Elevator(ElevatorControlSystem* ecs) : ecs(ecs){
    maxLoad = MAX_LOAD;
    floor = 1;
    panel = new QElevatorPanel(this);
    model = new QElevatorModel();
}

int Elevator::getFloor() const{
    return floor;
}

QElevatorPanel* Elevator::getPanel() const{
    return panel;
}
QElevatorModel* Elevator::getModel() const{
    return model;
}

bool Elevator::requestFloor(int floor, Direction dir){
    requests << floor;
    updateFloorIndicators();
    qInfo() << "Adding floor" << floor << "request to" << this << ":" << requests;
    return true;
}

bool Elevator::fulfillRequest(){
    if (requests.isEmpty()) {
        return false; // No requests to fulfill
    }

    int nextFloor = requests.first();

    if (nextFloor > floor) {
        moveUp();
        direction = Direction::UP;
    } else if (nextFloor < floor) {
        moveDown();
        direction = Direction::DOWN;
    } else {
        requests.removeFirst(); // Pop request after completing it
        
        // Update buttons and panels
        updateElevatorButtons();
        updateFloorIndicators();
        ecs->getFloorButton(floor, Direction::UP)->setEnabled(true);
        ecs->getFloorButton(floor, Direction::DOWN)->setEnabled(true);
        direction = Direction::NONE;
        panel->updateFloor(floor);
    }
    return true;
}

bool Elevator::moveUp(){
    //@@ add conditional for errors
    floor++;
    panel->updateFloor(floor);
    model->moveUp();
    return true;
}

bool Elevator::moveDown(){
    //@@ add conditional for errors
    floor--;
    panel->updateFloor(floor);
    model->moveDown();
    return true;
}

void Elevator::updateFloorIndicators(){
    // Updates elevator requests indicators
    model->clearIndicators();
    for (int i : requests){
        model->setFloorIndicator(i, true);
    }
}

void Elevator::updateElevatorButtons(){
    // Updates elevator buttons on the elevator's panel
    panel->clearButtons();
    for (int i : requests){
        panel->getButton(i-1)->setEnabled(false);
    }
}