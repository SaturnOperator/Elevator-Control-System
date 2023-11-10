#ifndef QERRORINDICATOR_H
#define QERRORINDICATOR_H

#include "defs.h"

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QList>

#include "QCustomIconsFont.h"

class QErrorIndicator : public QWidget {
    Q_OBJECT

    public:
        explicit QErrorIndicator(QWidget *parent = nullptr);
        void addError(EmergencyStatus e);
        void clearError(EmergencyStatus e);
        void clear();

        int getValue() const { return value; }

    private:
        int value;
        QLabel* errorMessage;
        QLabel* obstacleIcon;
        QLabel* overloadIcon;
        QLabel* helpIcon;
        QLabel* outageIcon;
        QLabel* fireIcon;
        QList<QLabel*> errorIcons;

        void updateScreen();
};

#endif // QERRORINDICATOR_H
