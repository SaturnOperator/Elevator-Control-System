#ifndef QELEVATORPANEL_H
#define QELEVATORPANEL_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>

class QElevatorPanel : public QWidget
{
    Q_OBJECT

public:
    explicit QElevatorPanel(QWidget *parent = nullptr);

private:
    QLabel *titleLabel;
    QPushButton *button1;
    QPushButton *button2;
};

#endif // QELEVATORPANEL_H