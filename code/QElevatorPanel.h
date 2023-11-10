#ifndef QELEVATORPANEL_H
#define QELEVATORPANEL_H

#include "defs.h"

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QList>
#include <QLCDNumber>
#include <QDebug>

#include "QElevatorButton.h"
#include "QUpDownIndicator.h"
#include "QErrorIndicator.h"
#include "QCustomIconsFont.h"

class Elevator; // Forward declaration

class QElevatorPanel : public QWidget {
    Q_OBJECT

    public:
        explicit QElevatorPanel(Elevator* elevator, QWidget *parent = nullptr);
        void addError(EmergencyStatus e);
        void clearError(EmergencyStatus e);
        void clear();

    private:
        Elevator* elevator;
        int floor;
        QLabel* titleLabel;
        QErrorIndicator* errors;
        QLCDNumber* screen; // Floor number indicator
        QUpDownIndicator* upDownIndicator;
        QList<QElevatorButton*> floorButtons; // Floor buttons
        QList<QElevatorButton*> controlButtons; // Control Buttons
        QElevatorButton* buttonDoorOpen;
        QElevatorButton* buttonDoorClose;
        QElevatorButton* buttonHelp;
        QElevatorButton* buttonFire;

        bool updateFloor(int floor);
};

#endif // QELEVATORPANEL_H
