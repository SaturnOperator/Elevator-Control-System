#include "QElevatorPanel.h"

QElevatorPanel::QElevatorPanel(QWidget *parent) : QWidget(parent) {
    QVBoxLayout* layout = new QVBoxLayout;
    
    titleLabel = new QLabel("Elevator Panel", this);
    layout->addWidget(titleLabel);

    // Custom Icons font for buttons and indicators
    QCustomIconsFont& iconsFont = QCustomIconsFont::instance();

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

    QString buttonStyleSheet = "QPushButton { "
    "    color: white; "
    "    background-color: #111111; "
    "    border-radius: 13px; "
    "}"
    "QPushButton:hover { "
    "    background-color: #202020; "
    "}"
    "QPushButton:pressed { "
    "    background-color: #093eb8; "
    "}"
    "QPushButton:disabled { "
    "    background-color: #093eb8; "
    "    border: 2px solid #255fe6"
    "}";

    // Put floor buttons horizontally in HBox
    QHBoxLayout* controlButtonsLayout = new QHBoxLayout;
    QWidget* buttonGroup1 = new QWidget;
    buttonGroup1->setLayout(controlButtonsLayout);

    // Create control buttons, use custom glyphs for icons
    buttonDoorOpen = new QPushButton(" ", this);
    buttonDoorClose = new QPushButton(" ", this);
    buttonHelp = new QPushButton("", this);
    buttonFire = new QPushButton("", this);

    controlButtonsLayout->addWidget(buttonDoorOpen);
    controlButtonsLayout->addWidget(buttonDoorClose);
    controlButtonsLayout->addWidget(buttonHelp);
    controlButtonsLayout->addWidget(buttonFire);

    // Add all control buttons into controlButtons list
    controlButtons << buttonDoorOpen << buttonDoorClose << buttonHelp << buttonFire;
    iconsFont.setPointSize(12);

    // Stylize each button, add them each into the widget
    for (QPushButton* button : controlButtons) {
        button->setFont(iconsFont); // Apply font to each button
        button->setFixedSize(26, 26);
        button->setStyleSheet(buttonStyleSheet);
        controlButtonsLayout->addWidget(button);
    }

    /* FLOOR BUTTONS */

    // Put floor buttons horizontally in HBox
    QHBoxLayout* floorButtonsLayout = new QHBoxLayout;
    QWidget* buttonGroup2 = new QWidget;
    buttonGroup2->setLayout(floorButtonsLayout);

    // Create floor buttons, stylize them and add them to floorButton list
    for (int floor = 1; floor <= NUM_FLOORS; ++floor) {
        QPushButton* floorButton = new QPushButton(QString::number(floor), this);
        floorButton->setFixedSize(26, 26);
        floorButtonsLayout->addWidget(floorButton);
        floorButtons << floorButton; // Add button to floorButtons array
        floorButton->setObjectName("floorButton");
        floorButton->setStyleSheet(buttonStyleSheet);
    
        // Connect floorButton's clicked() signal to update screen
        connect(floorButton, &QPushButton::clicked, this, [this, floor]() {
            // @@@@ Change this function to add to elevator queue
            updateFloor(floor);
        });
    }

    floorButtons[2]->setEnabled(false);

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

