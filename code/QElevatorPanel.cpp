#include "QElevatorPanel.h"
#include "Elevator.h" // Forward declaration

QElevatorPanel::QElevatorPanel(Elevator* elevator, QWidget *parent)
    : QWidget(parent), elevator(elevator) {
    QVBoxLayout* layout = new QVBoxLayout;
    
    titleLabel = new QLabel("Elevator Panel", this);
    layout->addWidget(titleLabel);

    /* FLOOR & DIRECTION INDICATORS */
    
    QHBoxLayout* displayLayout = new QHBoxLayout;
    QWidget* displayGroup = new QWidget;
    displayGroup->setLayout(displayLayout);

    // Create LCD screen to show floor number indicator
    screen = new QLCDNumber(this);
    displayLayout->addWidget(screen);
    screen->setSegmentStyle(QLCDNumber::Flat);
    screen->setFixedSize(75, 50);
    screen->setDigitCount(3);

    // Create an up down direction indicator
    upDownIndicator = new QUpDownIndicator();
    displayLayout->addWidget(upDownIndicator);


    /* ERROR INDICATOR */
    errors = new QErrorIndicator();

    /* CONTROL BUTTONS */

    // Put floor buttons horizontally in HBox
    QHBoxLayout* controlButtonsLayout = new QHBoxLayout;
    QWidget* buttonGroup1 = new QWidget;
    buttonGroup1->setLayout(controlButtonsLayout);

    // Create control buttons, use custom glyphs for icons
    buttonDoorOpen = new QElevatorButton(" ", this);
    buttonDoorClose = new QElevatorButton(" ", this);
    buttonHelp = new QElevatorButton("", this);
    buttonFire = new QElevatorButton("", this);

    controlButtonsLayout->addWidget(buttonDoorOpen);
    controlButtonsLayout->addWidget(buttonDoorClose);
    controlButtonsLayout->addWidget(buttonHelp);
    controlButtonsLayout->addWidget(buttonFire);

    // Add all control buttons into controlButtons list
    controlButtons << buttonDoorOpen << buttonDoorClose << buttonHelp << buttonFire;
    
    // Stylize each button, add them each into the widget
    for (QElevatorButton* button : controlButtons) {
        controlButtonsLayout->addWidget(button);
    }

    /* FLOOR BUTTONS */

    // Put floor buttons horizontally in HBox
    QHBoxLayout* floorButtonsLayout = new QHBoxLayout;
    QWidget* buttonGroup2 = new QWidget;
    buttonGroup2->setLayout(floorButtonsLayout);

    // Create floor buttons, stylize them and add them to floorButton list
    for (int floor = 1; floor <= NUM_FLOORS; ++floor) {
        QElevatorButton* floorButton = new QElevatorButton(QString::number(floor), this);
        floorButtonsLayout->addWidget(floorButton);
        floorButtons << floorButton; // Add button to floorButtons array
    
        // Connect floorButton's clicked() signal to update screen
        connect(floorButton, &QPushButton::clicked, this, [floorButton, elevator, floor]() {
            // @@@@ Change this function to add to elevator queue
            elevator->requestFloor(floor);
            floorButton->on();
        });
    }

    // Add each buttonGroup into the main view
    layout->addWidget(displayGroup);
    layout->addWidget(errors);
    layout->addWidget(buttonGroup1);
    layout->addWidget(buttonGroup2);
    setLayout(layout);

    // Initialize at first floor
    floor = 1;
    updateFloor(1);
    errors->clear();
    // addError(EmergencyStatus::FIRE);
    // addError(EmergencyStatus::OVERLOAD);
    // addError(EmergencyStatus::OBSTRUCTION);
    // clearError(EmergencyStatus::OVERLOAD);
}

bool QElevatorPanel::updateFloor(int floor){
    // Update direction indicator
    if(this->floor < floor){
        upDownIndicator->up();
    } else if(this->floor > floor){
        upDownIndicator->down();
    } else {
        upDownIndicator->clear();
    }

    // Set floor
    this->floor = floor;

    // Update display
    screen->display(floor);

    return true;
}

void QElevatorPanel::addError(EmergencyStatus e){
    errors->addError(e);
}

void QElevatorPanel::clearError(EmergencyStatus e){
    errors->clearError(e);
}

void QElevatorPanel::clear(){
    errors->clear();
}

void QElevatorPanel::clearButtons(){
    for(QElevatorButton* button: floorButtons){
        button->setEnabled(true);
    }
}

QElevatorButton* QElevatorPanel::getButton(int floor){
    if(floor < 0 || floor >= NUM_FLOORS){
        return nullptr;
    }
    return floorButtons.at(floor);
}
