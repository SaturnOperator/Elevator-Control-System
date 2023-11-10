#include <QApplication>
#include <QMainWindow>
#include <QVBoxLayout>

#include "Elevator.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QMainWindow mainWindow;
    mainWindow.setWindowTitle("Elevator Panels");
    QVBoxLayout *mainLayout = new QVBoxLayout;



    // Dynamically create and add each elevator
    QList<Elevator*> elevators;
    // for (int i = 0; i < NUM_ELEVATORS; i++) {
    for (int i = 0; i < 1; i++) {
        Elevator* e = new Elevator();
        elevators << e;

        // Add the elevator's panel into the GUI
        mainLayout->addWidget(e->getModel());
        mainLayout->addWidget(e->getPanel());
    }

    // Create and show central widget
    QWidget *centralWidget = new QWidget;
    centralWidget->setLayout(mainLayout);
    mainWindow.setCentralWidget(centralWidget);
    mainWindow.show();

    return app.exec();
}
