#include <QApplication>
#include <QMainWindow>
#include <QVBoxLayout>

#include "ElevatorControlSystem.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QMainWindow mainWindow;
    mainWindow.setWindowTitle("Elevator Panels");
    QVBoxLayout* mainLayout = new QVBoxLayout;


    ElevatorControlSystem *ecs = new ElevatorControlSystem(NUM_FLOORS, NUM_ELEVATORS);
    

    
    for (int i = 0; i < ecs->getNumElevators(); i++) {
        // Add the elevator's panel into the GUI
        Elevator* e = ecs->getElevator(i);
        mainLayout->addWidget(e->getModel());
        mainLayout->addWidget(e->getPanel());
    }

    // Create and show central widget
    QWidget* centralWidget = new QWidget;
    centralWidget->setLayout(mainLayout);
    mainWindow.setCentralWidget(centralWidget);
    mainWindow.show();

    return app.exec();
}
