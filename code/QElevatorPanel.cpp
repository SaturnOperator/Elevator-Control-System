#include "qelevatorpanel.h"
#include <QVBoxLayout>

QElevatorPanel::QElevatorPanel(QWidget *parent) : QWidget(parent)
{
    titleLabel = new QLabel("Elevator Panel", this);
    button1 = new QPushButton("Button 1", this);
    button2 = new QPushButton("Button 2", this);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(titleLabel);
    layout->addWidget(button1);
    layout->addWidget(button2);

    setLayout(layout);
}