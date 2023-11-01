#ifndef QELEVATORPANEL_H
#define QELEVATORPANEL_H

#include "defs.h"

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFont>
#include <QList>
#include <QLCDNumber>

#include "QUpDownIndicator.h"

class QElevatorPanel : public QWidget
{
    Q_OBJECT

public:
    explicit QElevatorPanel(QWidget *parent = nullptr);

private:
    int floor;
    QLabel *titleLabel;
    QLCDNumber *screen; // Floor number indicator
    QUpDownIndicator *upDownIndicator;
    QList<QPushButton*> floorButtons; // Floor buttons
    QList<QPushButton*> controlButtons; // Control Buttons
    QPushButton *buttonDoorOpen;
    QPushButton *buttonDoorClose;
    QPushButton *buttonHelp;
    QPushButton *buttonFire;

    bool updateFloor(int floor);
};

#endif // QELEVATORPANEL_H
