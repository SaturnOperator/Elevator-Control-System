#ifndef QELEVATORBUTTON_H
#define QELEVATORBUTTON_H

#include "defs.h"

#include <QPushButton>

#include "QCustomIconsFont.h"

class QElevatorButton : public QPushButton {
    Q_OBJECT

    public:
        explicit QElevatorButton(const QString &text, QWidget *parent = nullptr);
        void on();
        void off();
        void setSize(int size);

    private:
        void stylize();
        int size;
};

#endif // QELEVATORBUTTON_H
