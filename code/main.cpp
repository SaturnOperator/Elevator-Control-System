#include <QApplication>
#include <QMainWindow>
#include <QGridLayout>
#include <QDebug>
#include <QScrollArea>

#include "ElevatorControlSystem.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QMainWindow mainWindow;
    mainWindow.setWindowTitle("Elevator Panels");

    QGridLayout* mainLayout = new QGridLayout;

    ElevatorControlSystem *ecs = new ElevatorControlSystem(NUM_FLOORS, NUM_ELEVATORS);
    
    int colFloorButton = 0;
    int rowFloorButton = 1;
    mainLayout->addWidget(new QLabel("Floors"), rowFloorButton-1, colFloorButton, 1, 1);
    for (int i = 1; i <= ecs->getNumFloors(); i++) {
        QGroupBox* floorButtonBox = new QGroupBox(" " + QString::number(i));
        floorButtonBox->setAlignment(Qt::AlignCenter);
        floorButtonBox->setLayout(new QVBoxLayout());
        floorButtonBox->layout()->setContentsMargins(2, 2, 2, 2);
        floorButtonBox->setMaximumWidth(28);

        // Get floor buttons
        QElevatorButton* upButton = ecs->getFloorButton(i, Direction::UP);
        QElevatorButton* downButton = ecs->getFloorButton(i, Direction::DOWN);
        upButton->setSize(18);
        downButton->setSize(18);
        
        floorButtonBox->layout()->addWidget(upButton);
        floorButtonBox->layout()->addWidget(downButton);
        mainLayout->addWidget(floorButtonBox, 2 * (ecs->getNumFloors() - i) + rowFloorButton, colFloorButton);


        // mainLayout->addWidget(upButton, 2 * (ecs->getNumFloors() - i) + rowFloorButton, colFloorButton);
        // mainLayout->addWidget(downButton, 2 * (ecs->getNumFloors() - i)+1 + rowFloorButton, colFloorButton);
    }

    // Add elevator buttons and elevator models into the view
    int colElevatorModels = colFloorButton+1;
    int rowElevatorModels = rowFloorButton;
    for (int i = 0; i < ecs->getNumElevators(); i++) {
        // Add elevator label
        mainLayout->addWidget(new QLabel("Elevator " + QString::number(i)), rowElevatorModels-1, i+colElevatorModels, 1, 1);
        
        // Add the elevator's panel into the GUI
        Elevator* e = ecs->getElevator(i);
        mainLayout->addWidget(e->getModel(), rowElevatorModels, i+colElevatorModels, ecs->getNumFloors()*2, 1);
        mainLayout->addWidget(e->getPanel(), rowElevatorModels+ecs->getNumFloors()*2+1, i+colElevatorModels);

    }

    // Testing buttons
    QWidget* testGroup = new QWidget();
    QGridLayout* testGrid = new QGridLayout();
    testGroup->setLayout(testGrid);
    int colTestGroup = colElevatorModels+ecs->getNumElevators();
    int rowTestGroup = rowElevatorModels;

    QPushButton* runEcsButton = new QPushButton("ECS Run Cycle");

    QObject::connect(runEcsButton, &QPushButton::clicked, [ecs]() {
        for (int i = 0; i < ecs->getNumElevators(); i++) {
            Elevator* e = ecs->getElevator(i);
            e->fulfillRequest();
        }
    });

    testGrid->addWidget(runEcsButton);
    mainLayout->addWidget(testGroup, rowTestGroup, colTestGroup);


    // Create and show central widget
    QWidget* centralWidget = new QWidget;
    centralWidget->setLayout(mainLayout);

    // Put everything in a scrollable area
    QScrollArea* scrollArea = new QScrollArea(&mainWindow);
    scrollArea->setWidget(centralWidget);
    mainWindow.setCentralWidget(scrollArea);

    // Resize to fit everything
    mainWindow.resize(centralWidget->sizeHint());

    // Show window and run app
    mainWindow.show();
    return app.exec();
}
