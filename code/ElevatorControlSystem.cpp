#include "ElevatorControlSystem.h"

ElevatorControlSystem::ElevatorControlSystem(int numberFloors, int numberElevators){
    numFloors = numberFloors;
    emergencyStatus = static_cast<int>(EmergencyStatus::NONE);
    /* Dynamically create and add each elevator */
    for (int i = 0; i < numberElevators; i++) {
        Elevator* e = new Elevator(this);
        elevators << e;

        // Put each elevator on its own thread
        QThread* thread = new QThread;
        elevatorThreads << thread;
        e->moveToThread(thread);
        thread->start();
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

    // Outage button
    outageTestButton = new QPushButton("Toggle Power Outage");
    adminButtons << outageTestButton;
    connect(outageTestButton, &QPushButton::clicked, [this]() {
        toggleEmergencyState(EmergencyStatus::OUTAGE);
    });

    // Fire button
    fireTestButton = new QPushButton("Toggle Fire Alarm");
    adminButtons << fireTestButton;
    connect(fireTestButton, &QPushButton::clicked, [this]() {
        toggleEmergencyState(EmergencyStatus::FIRE);
    });

    // Overload simulator picker
    obstructionSelector = new QComboBox();
    obstructionSelector->addItem("Select elevator", QVariant::fromValue(nullptr));
    for (int i = 0; i < getNumElevators(); i++) {
        obstructionSelector->addItem("Elevator " + QString::number(i+1), QVariant::fromValue(getElevator(i)));
    }

    connect(obstructionSelector, QOverload<int>::of(&QComboBox::currentIndexChanged), [this]() {

        for(Elevator* e : elevators){
            if(e->getEmergencyStatus() & static_cast<int>(EmergencyStatus::OBSTRUCTION)){
                e->setLoad(0);
            }
        }

        // // Get the selected elevator pointer from the combo box
        Elevator* e = qvariant_cast<Elevator*>(obstructionSelector->currentData());

        if (e) {
            e->setLoad(2*MAX_LOAD);
        }
    });

    // Overload simulator picker
    overloadSelector = new QComboBox();
    overloadSelector->addItem("Select elevator", QVariant::fromValue(nullptr));
    for (int i = 0; i < getNumElevators(); i++) {
        overloadSelector->addItem("Elevator " + QString::number(i+1), QVariant::fromValue(getElevator(i)));
    }

    connect(overloadSelector, QOverload<int>::of(&QComboBox::currentIndexChanged), [this]() {
        for(Elevator* e : elevators){
            if(e->getEmergencyStatus() & static_cast<int>(EmergencyStatus::OVERLOAD)){
                e->clearEmergency(EmergencyStatus::OVERLOAD);
                e->closeDoors();
            }
        }

        // // Get the selected elevator pointer from the combo box
        Elevator* e = qvariant_cast<Elevator*>(overloadSelector->currentData());

        if (e) {
            e->openDoors();
            e->flagEmergency(EmergencyStatus::OVERLOAD);
        }
    });

    // Create timer for help response 
    helpTimer = new QTimer(this);
    helpTimer->setSingleShot(true);
    helpLoop = new QEventLoop(this);
    connect(helpTimer, &QTimer::timeout, helpLoop, &QEventLoop::quit);

    // Create help response button
    helpResponseButton = new QPushButton("Respond to help call");
    adminButtons << helpResponseButton;
    connect(helpResponseButton, &QPushButton::clicked, [this]() {
        helpCallResponded = true;
        // Clear emergency state
        for(Elevator* e : elevators){
            if(e->getEmergencyStatus() & static_cast<int>(EmergencyStatus::HELP)){
                e->clearEmergency(EmergencyStatus::HELP);
            }
        }

        helpLoop->quit(); // Stop timer loop when button is pressed
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

QComboBox* ElevatorControlSystem::getOverloadSelector() const{
    return overloadSelector;
}

QComboBox* ElevatorControlSystem::getObstructionSelector() const{
    return obstructionSelector;
}

Elevator* ElevatorControlSystem::findBestElevator(int floor){
    if (elevators.isEmpty()) {
        return nullptr;
    }

    Elevator* best = elevators.at(0);
    int closestDistance = abs(best->getFloor() - floor);

    // If the first elevator isn't available, set this to an arbitrarily high floor count delta
    // So the next available elevator becomes best 
    if(best->getEmergencyStatus() != 0){
        closestDistance = 2*numFloors;
    }

    for(Elevator* e : elevators){
        if(e->getEmergencyStatus() != 0){
            continue;
        }

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

bool ElevatorControlSystem::helpSafetySequence(Elevator* e){
    helpCallResponded = false;
    qInfo() << "Help is required in" << e;
    e->flagEmergency(EmergencyStatus::HELP);

    helpTimer->start(5000); // 5s timer 
    helpLoop->exec();

    if (helpCallResponded == false) {
        // The timer timed out, 5 seconds have passed
        qInfo() << "No response after 5s, forwarding call to emergency services" << e;
        helpCall911();
        return false;
    } else {
        // helpResponseButton was pressed
        qInfo() << "Building services have responded to help call in " << e;
        return true;
    }

    return true;
}

void ElevatorControlSystem::helpCall911(){
    qInfo() << "Calling 911";
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