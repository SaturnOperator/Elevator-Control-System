#ifndef QUPDONWINDICATOR_H
#define QUPDONWINDICATOR_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QFont>
#include <QList>

#include "defs.h"

class QUpDownIndicator : public QWidget
{
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

#endif // QUPDONWINDICATOR_H
