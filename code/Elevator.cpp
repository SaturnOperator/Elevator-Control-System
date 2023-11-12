#include "Elevator.h"
#include "ElevatorControlSystem.h" // Forward declaration

#include <QTimer>

Elevator::Elevator(ElevatorControlSystem* ecs) : ecs(ecs){
    maxLoad = MAX_LOAD;
    floor = 1;
    doorStatus = DoorStatus::CLOSE;
    emergencyStatus = EmergencyStatus::NONE;

    // Create elevator panel and elevator model that shows the elevator in the shaft
    panel = new QElevatorPanel(this);
    model = new QElevatorModel();

    // Always run this in a loop
    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Elevator::fulfillRequest);
    timer->start(1000);
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
    if(floor < 1 || floor > NUM_FLOORS || requests.contains(floor)){
        return false;
    }
    requests << floor;
    updateFloorIndicators();
    qInfo() << "Adding floor" << floor << "request to" << this << ":" << requests;
    return true;
}

bool Elevator::fulfillRequest(){

    if (doorStatus != DoorStatus::CLOSE) {
        return false; // Door is open
    }

    if (emergencyStatus != EmergencyStatus::NONE) {
        return false; // Errors present
    }

    if (requests.isEmpty()) {
        return false; // No requests to fulfill
    }

    int nextFloor = requests.first();

    if (nextFloor == floor) {
        requests.removeFirst(); // Pop request after completing it, continue after if statement
    } else if (requests.contains(floor)) {
        requests.removeOne(floor);
    } else if (nextFloor > floor) {
        moveUp();
        direction = Direction::UP;
        return false;
    } else if (nextFloor < floor) {
        moveDown();
        direction = Direction::DOWN;
        return false;
    }

    // Ring bell
    // QApplication::beep();
    qInfo() << "Ding";
    qInfo() << this << "reached floor " << floor;

    // Update buttons and panels
    updateElevatorButtons();
    updateFloorIndicators();
    ecs->getFloorButton(floor, Direction::UP)->setEnabled(true);
    ecs->getFloorButton(floor, Direction::DOWN)->setEnabled(true);
    direction = Direction::NONE;
    panel->updateFloor(floor);
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