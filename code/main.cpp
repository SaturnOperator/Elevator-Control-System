#include <QApplication>
#include <QMainWindow>
#include <QVBoxLayout>
#include "qelevatorpanel.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QMainWindow mainWindow;
    mainWindow.setWindowTitle("Elevator Panels");
    QVBoxLayout *mainLayout = new QVBoxLayout;


    // Dynamically create and add each elevator
    QElevatorPanel elevatorPanels[NUM_ELEVATORS];
    for (int i = 0; i < NUM_ELEVATORS; i++) {
        elevatorPanels[i].setWindowTitle("Elevator Panel " + QString::number(i + 1));
        elevatorPanels[i].setParent(&mainWindow);
        mainLayout->addWidget(&elevatorPanels[i]);
    }

    // Create and show central widget
    QWidget *centralWidget = new QWidget;
    centralWidget->setLayout(mainLayout);
    mainWindow.setCentralWidget(centralWidget);
    mainWindow.show();

    return app.exec();
}
