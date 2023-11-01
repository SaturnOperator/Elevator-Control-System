#include <QApplication>
#include <QMainWindow>
#include <QVBoxLayout>
#include "qelevatorpanel.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QMainWindow mainWindow;
    mainWindow.setWindowTitle("Elevator Panels");

    QElevatorPanel panel1;
    panel1.setWindowTitle("Elevator Panel 1");
    panel1.setParent(&mainWindow);

    QElevatorPanel panel2;
    panel2.setWindowTitle("Elevator Panel 2");
    panel2.setParent(&mainWindow);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(&panel1);
    mainLayout->addWidget(&panel2);

    QWidget *centralWidget = new QWidget;
    centralWidget->setLayout(mainLayout);

    mainWindow.setCentralWidget(centralWidget);
    mainWindow.show();

    return app.exec();
}
