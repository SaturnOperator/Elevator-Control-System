#include "qelevatorpanel.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFont>

QElevatorPanel::QElevatorPanel(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout;
    
    titleLabel = new QLabel("Elevator Panel", this);
    layout->addWidget(titleLabel);
    
    // Create an array of buttons
    for (int i = 0; i < NUM_FLOORS; i++) {
        buttons[i] = new QPushButton(QString::number(i + 1), this);
        buttons[i]->setFixedWidth(26);
    }

    // Put main buttons horizontally in HBox
    QHBoxLayout *mainButtonsLayout = new QHBoxLayout;
    QWidget *mainButtons = new QWidget;
    mainButtons->setLayout(mainButtonsLayout);

    QFont iconsFont;
    iconsFont.setFamily("Font Awesome 6 Free"); // Custom Icon Font
    iconsFont.setPointSize(12); // 

    // Create main buttons, use custom glyphs for icons
    buttonDoorOpen = new QPushButton(" ", this);
    buttonDoorClose = new QPushButton(" ", this);
    buttonHelp = new QPushButton("", this);
    buttonFire = new QPushButton("", this);
    buttonDoorOpen->setFont(iconsFont);
    buttonDoorClose->setFont(iconsFont);
    buttonHelp->setFont(iconsFont);
    buttonFire->setFont(iconsFont);

    // buttonFire->setObjectName("fire-button");


    mainButtonsLayout->addWidget(buttonDoorOpen);
    mainButtonsLayout->addWidget(buttonDoorClose);
    mainButtonsLayout->addWidget(buttonHelp);
    mainButtonsLayout->addWidget(buttonFire);
    layout->addWidget(mainButtons);

    // Put floor buttons horizontally in HBox
    QHBoxLayout *floorButtonsLayout = new QHBoxLayout;
    QWidget *floorButtons = new QWidget;
    floorButtons->setLayout(floorButtonsLayout);

    // Add the buttons to the layout
    for (int i = 0; i < NUM_FLOORS; i++) {
        floorButtonsLayout->addWidget(buttons[i]);
    }
    layout->addWidget(floorButtons);

    setLayout(layout);
}
