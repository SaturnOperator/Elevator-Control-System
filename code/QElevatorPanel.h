#ifndef QELEVATORPANEL_H
#define QELEVATORPANEL_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>

#include "defs.h"

class QElevatorPanel : public QWidget
{
    Q_OBJECT

public:
    explicit QElevatorPanel(QWidget *parent = nullptr);

private:
    QLabel *titleLabel;
    QPushButton *buttons[NUM_FLOORS]; // floor buttons
    QPushButton *buttonDoorOpen;
    QPushButton *buttonDoorClose;
    QPushButton *buttonHelp;
    QPushButton *buttonFire;
};

#endif // QELEVATORPANEL_H
