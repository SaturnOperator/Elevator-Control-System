#include "Elevator.h"
#include "ElevatorControlSystem.h" // Forward declaration

Elevator::Elevator(ElevatorControlSystem* ecs) : ecs(ecs){
    maxLoad = MAX_LOAD;
    load = 0;
    floor = 1;
    doorStatus = DoorStatus::CLOSE;
    emergencyStatus = static_cast<int>(EmergencyStatus::NONE);

    // Create elevator panel and elevator model that shows the elevator in the shaft
    panel = new QElevatorPanel(this);
    model = new QElevatorModel();

    // Always run this in a loop
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Elevator::fulfillRequest);
    timer->start(ELVATOR_MOVE_DELAY);
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
    if(emergencyStatus != static_cast<int>(EmergencyStatus::NONE)){
        return false;
    }

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

    // Do not fulfill requests if there is an emergency state
    // Exception for fire and power outage to move elevator to safe floor
    if(
        emergencyStatus & static_cast<int>(EmergencyStatus::OBSTRUCTION) || 
        emergencyStatus & static_cast<int>(EmergencyStatus::OVERLOAD) ||
        emergencyStatus & static_cast<int>(EmergencyStatus::HELP)
    ){
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

void Elevator::alertECS(EmergencyStatus e){
    if(e == EmergencyStatus::FIRE){
        ecs->activateFireSafetySequence();
    }
}

void Elevator::flagEmergency(EmergencyStatus e){
    // Set emergency status and update the screen to show the error
    emergencyStatus |= static_cast<int>(e);
    panel->showErrors();
    qInfo() << "Emergency flagged in" << this;
}

void Elevator::clearEmergency(EmergencyStatus e){
    // clear emergency status and update the screen to show the error
    emergencyStatus &= ~static_cast<int>(e);
    panel->showErrors();
    qInfo() << "Emergency cleared in" << this;
}

int Elevator::getEmergencyStatus() const{
    return emergencyStatus;
}

bool Elevator::overrideGoToFloor(int safeFloor){
    // Clear all requests, reset indicator and button states 
    ecs->resetButtons();
    panel->clearButtons();
    model->clearIndicators();
    requests.clear();
    // Send elevator to safe floor
    model->setFloorIndicator(safeFloor, true);
    requests << safeFloor;
}
