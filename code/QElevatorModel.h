#ifndef QELEVATORMODEL_H
#define QELEVATORMODEL_H

#include <QWidget>
#include <QLabel>
#include <QGridLayout>
#include <QScrollBar>
#include <QList>


#include "defs.h"

class QElevatorModel : public QWidget {
    Q_OBJECT

    public:
        explicit QElevatorModel(QWidget *parent = nullptr);

        void moveCar(int position);
        void moveUp();
        void moveDown();
        void setFloorIndicator(int floor, bool enable);

    private:
        QScrollBar* car;
         QList<QLabel*> indicators; // Displays if elevator is coming or not

        void updateScreen();
};

#endif // QELEVATORMODEL_H
