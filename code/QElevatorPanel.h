#ifndef QELEVATORPANEL_H
#define QELEVATORPANEL_H

#include "defs.h"

#include <QGroupBox>
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

class QElevatorPanel : public QGroupBox {
    Q_OBJECT

    public:
        explicit QElevatorPanel(Elevator* elevator, QWidget *parent = nullptr);
        bool updateFloor(int floor);
        void clearButtons();
        void showErrors();
        void clear();

        QElevatorButton* getButton(int floor);

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

};

#endif // QELEVATORPANEL_H
