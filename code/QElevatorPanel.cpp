#include "QElevatorPanel.h"

QElevatorPanel::QElevatorPanel(QWidget *parent) : QWidget(parent){
    QVBoxLayout *layout = new QVBoxLayout;
    
    titleLabel = new QLabel("Elevator Panel", this);
    layout->addWidget(titleLabel);

    QHBoxLayout *displayLayout = new QHBoxLayout;
    QWidget *displayGroup = new QWidget;
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

    /* FLOOR BUTTONS */

    // Put floor buttons horizontally in HBox
    QHBoxLayout *controlButtonsLayout = new QHBoxLayout;
    QWidget *buttonGroup1 = new QWidget;
    buttonGroup1->setLayout(controlButtonsLayout);

    // Create control buttons, use custom glyphs for icons
    buttonDoorOpen = new QPushButton(" ", this);
    buttonDoorClose = new QPushButton(" ", this);
    buttonHelp = new QPushButton("", this);
    buttonFire = new QPushButton("", this);

    controlButtonsLayout->addWidget(buttonDoorOpen);
    controlButtonsLayout->addWidget(buttonDoorClose);
    controlButtonsLayout->addWidget(buttonHelp);
    controlButtonsLayout->addWidget(buttonFire);

    // Add all control buttons into controlButtons list
    controlButtons << buttonDoorOpen << buttonDoorClose << buttonHelp << buttonFire;

    QFont iconsFont;
    iconsFont.setFamily("Font Awesome 6 Free"); // Custom Icon Font
    iconsFont.setPointSize(12);

    // Stylize each button, add them each into the widget
    for (QPushButton *button : controlButtons) {
        button->setFont(iconsFont); // Apply font to each button
        button->setFixedWidth(26);
        controlButtonsLayout->addWidget(button);
    }

    // Put floor buttons horizontally in HBox
    QHBoxLayout *floorButtonsLayout = new QHBoxLayout;
    QWidget *buttonGroup2 = new QWidget;
    buttonGroup2->setLayout(floorButtonsLayout);

    // Create floor buttons, stylize them and add them to floorButton list
    for (int floor = 1; floor <= NUM_FLOORS; ++floor) {
        QPushButton *floorButton = new QPushButton(QString::number(floor), this);
        floorButton->setFixedWidth(26);
        floorButtonsLayout->addWidget(floorButton);
        floorButtons << floorButton; // Add button to floorButtons array
    
        // Connect floorButton's clicked() signal to update screen
        connect(floorButton, &QPushButton::clicked, this, [this, floor]() {
            // @@@@ Change this function to add to elevator queue
            updateFloor(floor);
        });
    }

    // Add each buttonGroup into the main view
    layout->addWidget(displayGroup);
    layout->addWidget(buttonGroup1);
    layout->addWidget(buttonGroup2);
    setLayout(layout);

    // Initialize at first floor
    floor = 1;
    updateFloor(1);
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