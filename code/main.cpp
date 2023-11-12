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

    // Instantiate ECS
    ElevatorControlSystem *ecs = new ElevatorControlSystem(NUM_FLOORS, NUM_ELEVATORS);
    
    /* Get floor buttons from ECS and put them in the grid layout */
    int colFloorButton = 0;
    int rowFloorButton = 1;
    mainLayout->addWidget(new QLabel("Floors"), rowFloorButton-1, colFloorButton, 1, 1);
    for (int i = 1; i <= ecs->getNumFloors(); i++) {
        QGroupBox* floorButtonBox = new QGroupBox(" " + QString::number(i));
        floorButtonBox->setAlignment(Qt::AlignCenter);
        floorButtonBox->setLayout(new QVBoxLayout());
        floorButtonBox->layout()->setContentsMargins(2, 2, 2, 2);
        floorButtonBox->setMaximumWidth(28);

        // Add floor buttons to the main grid
        floorButtonBox->layout()->addWidget(ecs->getFloorButton(i, Direction::UP));
        floorButtonBox->layout()->addWidget(ecs->getFloorButton(i, Direction::DOWN));
        mainLayout->addWidget(floorButtonBox, 2 * (ecs->getNumFloors() - i) + rowFloorButton, colFloorButton);    }

    /* Add elevator buttons and elevator models into the view */
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

    /* Create test buttons for toggling emergency states */
    QGroupBox* testGroup = new QGroupBox();
    QGridLayout* testGrid = new QGridLayout();
    testGroup->setLayout(testGrid);

    int colTestGroup = 0;
    int rowTestGroup = rowElevatorModels+ecs->getNumFloors()*2+1;
    mainLayout->addWidget(testGroup, rowTestGroup, colTestGroup);

    testGrid->addWidget(new QLabel("ECS Admin Panel"));

    // Button for running 1 ECS cycle, overrides the timer
    QPushButton* runEcsButton = new QPushButton("ECS Run Cycle");
    testGrid->addWidget(runEcsButton);
    QObject::connect(runEcsButton, &QPushButton::clicked, [ecs]() {
        for (int i = 0; i < ecs->getNumElevators(); i++) {
            Elevator* e = ecs->getElevator(i);
            e->fulfillRequest();
        }
    });

    for(QPushButton* button : ecs->getAdminButtons()){
        testGrid->addWidget(button);
    }

    testGrid->addWidget(new QLabel("Simulate Obstruction"));
    testGrid->addWidget(ecs->getObstructionSelector());

    testGrid->addWidget(new QLabel("Simulate Overload"));
    testGrid->addWidget(ecs->getOverloadSelector());

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
