#include "QElevatorButton.h"

QElevatorButton::QElevatorButton(const QString &text, QWidget *parent)
    : QPushButton(text, parent) {

    size = 26;

    QCustomIconsFont& iconsFont = QCustomIconsFont::instance();
    setFont(iconsFont);

    setSize(size);
}

void QElevatorButton::on(){
    setEnabled(false);
}

void QElevatorButton::off(){
    setEnabled(true);
}

void QElevatorButton::setSize(int diameter){
    if (diameter % 2 != 0) {
        diameter++; // Make number even
    }

    size = diameter;

    setFixedSize(diameter, diameter);
    stylize();
}

void QElevatorButton::stylize(){
    setStyleSheet( 
        QString(
            "QPushButton { "
            "    color: white; "
            "    background-color: #111111; "
            "    border-radius: %1px; "
            "    font-size: 10px;"
            "}"
            "QPushButton:hover { "
            "    background-color: #202020; "
            "}"
            "QPushButton:pressed { "
            "    background-color: #093eb8; "
            "}"
            "QPushButton:disabled { "
            "    background-color: #093eb8; "
            "    border: 2px solid #255fe6"
            "}"
        ).arg(size/2)
    );
}