#include "QErrorIndicator.h"

QErrorIndicator::QErrorIndicator(QWidget *parent) : QWidget(parent) {
    QHBoxLayout* layout = new QHBoxLayout;

    // Use custom fonts icons
    QCustomIconsFont& iconsFont = QCustomIconsFont::instance();
    iconsFont.setPointSize(20);

    // Icons for error indicator
    obstacleIcon = new QLabel("", this);
    overloadIcon = new QLabel("", this);
    helpIcon = new QLabel("", this);
    outageIcon = new QLabel("", this);
    fireIcon = new QLabel("", this);

    // Add all icons into list
    errorIcons << obstacleIcon << overloadIcon << helpIcon << outageIcon << fireIcon;

    // Stylize each and add to view
    for (QLabel* i : errorIcons) {
        layout->addWidget(i);
        i->setFont(iconsFont); // Apply font to each button
        i->setEnabled(false); // Disable indicators by default
        i->setObjectName("errorIcon");
        
        // Set CSS for labels to look differently when enabled and disabled
        i->setStyleSheet(
           "QLabel#errorIcon:enabled { color: red; }"
           "QLabel#errorIcon:disabled { color: rgba(128, 128, 128, 0.1);  }"
        );
    }

    // Message for error indicator
    errorMessage = new QLabel("", this);

    setLayout(layout);
}

void QErrorIndicator::updateScreen(){
    // Read value and update screen accordingly
    obstacleIcon->setEnabled(value & static_cast<int>(EmergencyStatus::OBSTRUCTION));
    overloadIcon->setEnabled(value & static_cast<int>(EmergencyStatus::OVERLOAD));
    helpIcon->setEnabled(value & static_cast<int>(EmergencyStatus::HELP));
    outageIcon->setEnabled(value & static_cast<int>(EmergencyStatus::OUTAGE));
    fireIcon->setEnabled(value & static_cast<int>(EmergencyStatus::FIRE));
}

void QErrorIndicator::setErrorCode(int errors){
    value = errors;
    updateScreen();
}

void QErrorIndicator::clear(){
    value = 0;
    updateScreen();
}
