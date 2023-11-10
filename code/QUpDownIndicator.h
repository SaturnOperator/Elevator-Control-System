#ifndef QUPDOWNINDICATOR_H
#define QUPDOWNINDICATOR_H

#include "defs.h"

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QList>

#include "QCustomIconsFont.h"

class QUpDownIndicator : public QWidget {
    Q_OBJECT

    public:
        explicit QUpDownIndicator(QWidget *parent = nullptr);
        void up();
        void down();
        void clear();

    private:
        QLabel *upIndicator;
        QLabel *downIndicator;
        QList<QLabel*> indicators;
};

#endif // QUPDOWNINDICATOR_H
