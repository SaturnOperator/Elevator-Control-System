#include "ElevatorControlSystem.h"

ElevatorControlSystem::ElevatorControlSystem(int numberFloors, int numberElevators){
    numFloors = numberFloors;
    emergencyStatus = static_cast<int>(EmergencyStatus::NONE);

    /* Dynamically create and add each elevator */
    for (int i = 0; i < numberElevators; i++) {
        Elevator* e = new Elevator(this);
        elevators << e;
    }

    /* Create all floor request buttons */
    for (int i = 1; i <= numFloors; i++) {
        // Create button to request an elevator up, ignore if on topmost floor
        if(i == numFloors){
            floorButtons[i][Direction::UP] = new QElevatorButton("");
        } else {
            QElevatorButton* buttonUp = new QElevatorButton("");
            floorButtons[i][Direction::UP] = buttonUp;
            // Find best elevator and add that floor to elevator's requests queue
            connect(buttonUp, &QPushButton::clicked, this, [this, i, buttonUp]() {
                Elevator* e = findBestElevator(i);
                if(e->requestFloor(i, Direction::UP)){
                    buttonUp->on(); // Illuminate button if request is accepted
                }
            });
        }

        // Create button to request an elevator down, ignore if on first floor
        if(i == 1){
            floorButtons[i][Direction::DOWN] = new QElevatorButton("");
        } else {
            QElevatorButton* buttonDown = new QElevatorButton("");
            floorButtons[i][Direction::DOWN] = buttonDown;
            // Find best elevator and add floor to elevator's requests
            connect(buttonDown, &QPushButton::clicked, this, [this, i, buttonDown]() {
                Elevator* e = findBestElevator(i);
                if(e->requestFloor(i, Direction::DOWN)){
                    buttonDown->on(); // Illuminate button if request is accepted
                }
            });
        }

        // Resize floor buttons to be more compact;
        floorButtons[i][Direction::UP]->setSize(18);
        floorButtons[i][Direction::DOWN]->setSize(18);
    }

    /*Create ECS Admin buttons for testing and clearing error statuses */
    outageTestButton = new QPushButton("Toggle Power Outage");
    adminButtons << outageTestButton;
    QObject::connect(outageTestButton, &QPushButton::clicked, [this]() {
        toggleEmergencyState(EmergencyStatus::OUTAGE);
    });

    fireTestButton = new QPushButton("Toggle Fire Alarm");
    adminButtons << fireTestButton;
    QObject::connect(fireTestButton, &QPushButton::clicked, [this]() {
        toggleEmergencyState(EmergencyStatus::FIRE);
    });

    helpResonseButton = new QPushButton("Respond to help call");
    adminButtons << helpResonseButton;
    QObject::connect(helpResonseButton, &QPushButton::clicked, [this]() {
        for (int i = 0; i < this->getNumElevators(); i++) {
            Elevator* e = this->getElevator(i);
            e->fulfillRequest();
        }
    });


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

QList<QPushButton*> ElevatorControlSystem::getAdminButtons() const{
    return adminButtons;
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

void ElevatorControlSystem::activateFireSafetySequence(){
    // Set fire flag
    emergencyStatus |= static_cast<int>(EmergencyStatus::FIRE);
    fireTestButton->setDown(true);
    qInfo() << "Fire alarm has been pulled, elevators are now inoperable";

    // Set emergency status in all elevators
    for(Elevator* e: elevators){
        e->flagEmergency(EmergencyStatus::FIRE);
    }
    // Move elevators to first floor
    for(Elevator* e: elevators){
        e->overrideGoToFloor(1);
    }
}

void ElevatorControlSystem::clearFire(){
    // Unset fire flag, restore elevators to operatoional state
    emergencyStatus &= ~static_cast<int>(EmergencyStatus::FIRE);
    fireTestButton->setDown(false);
    qInfo() << "Fire alarm has been addressed, elevators are back to  an operational state";

    // clear the emergency status in all elevators
    for(Elevator* e: elevators){
        e->clearEmergency(EmergencyStatus::FIRE);
    }
}


void ElevatorControlSystem::activateOutageSafetySequence(){
    // Set Outage flag
    emergencyStatus |= static_cast<int>(EmergencyStatus::OUTAGE);
    outageTestButton->setDown(true);
    qInfo() << "Power outage detected, elevators are now inoperable";

    // Set emergency status in all elevators
    for(Elevator* e: elevators){
        e->flagEmergency(EmergencyStatus::OUTAGE);
    }
    // Move elevators to first floor
    for(Elevator* e: elevators){
        e->overrideGoToFloor(1);
    }
}
void ElevatorControlSystem::clearOutage(){
    // Unset Outage flag, restore elevators to operatoional state
    emergencyStatus &= ~static_cast<int>(EmergencyStatus::OUTAGE);
    outageTestButton->setDown(false);
    qInfo() << "Power outage has been addressed, elevators are back to  an operational state";

    // clear the emergency status in all elevators
    for(Elevator* e: elevators){
        e->clearEmergency(EmergencyStatus::OUTAGE);
    }
}

void ElevatorControlSystem::toggleEmergencyState(EmergencyStatus e){
    if(emergencyStatus & static_cast<int>(e)){
        if(e == EmergencyStatus::FIRE){
            clearFire();
        } else if (e == EmergencyStatus::OUTAGE){
            clearOutage();
        }
    } else {
        if(e == EmergencyStatus::FIRE){
            activateFireSafetySequence();
        } else if (e == EmergencyStatus::OUTAGE){
            activateOutageSafetySequence();
        }
    }
}

void ElevatorControlSystem::resetButtons(){
    for(int f : floorButtons.keys()){
        floorButtons[f][Direction::UP]->off();
        floorButtons[f][Direction::DOWN]->off();
    }
}