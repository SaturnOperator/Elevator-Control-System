#ifndef QELEVATORPANEL_H
#define QELEVATORPANEL_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFont>
#include <QList>
#include <QLCDNumber>

#include "defs.h"

class QElevatorPanel : public QWidget
{
    Q_OBJECT

public:
    explicit QElevatorPanel(QWidget *parent = nullptr);

private:
    QLabel *titleLabel;
    QLCDNumber *screen; // Floor number indicator
    QList<QPushButton*> floorButtons; // Floor buttons
    QList<QPushButton*> controlButtons; // Control Buttons
    QPushButton *buttonDoorOpen;
    QPushButton *buttonDoorClose;
    QPushButton *buttonHelp;
    QPushButton *buttonFire;
};

#endif // QELEVATORPANEL_H
