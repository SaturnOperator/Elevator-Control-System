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



    private:
        QScrollBar *car;
         QList<QLabel*> indicator; // Displays if elevator is coming or not

        void updateScreen();
};

#endif // QELEVATORMODEL_H
