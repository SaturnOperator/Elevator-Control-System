#include "QElevatorButton.h"

QElevatorButton::QElevatorButton(const QString &text, QWidget *parent)
    : QPushButton(text, parent) {

    setObjectName("floorButton");
    setStyleSheet(
        "QPushButton { "
        "    color: white; "
        "    background-color: #111111; "
        "    border-radius: 13px; "
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
    );

    QCustomIconsFont& iconsFont = QCustomIconsFont::instance();
    setFont(iconsFont);
    setFixedSize(26, 26);
}

void QElevatorButton::on(){
    setEnabled(false);
}

void QElevatorButton::off(){
    setEnabled(true);
}