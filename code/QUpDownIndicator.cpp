#include "QUpDownIndicator.h"

QUpDownIndicator::QUpDownIndicator(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *layout = new QVBoxLayout;
    
    // Create indicators
    upIndicator = new QLabel("", this);
    downIndicator = new QLabel("", this);
    indicators << upIndicator << downIndicator;

    // Use custom fonts icons
    QFont iconsFont;
    iconsFont.setFamily("Font Awesome 6 Free"); // Custom Icon Font
    iconsFont.setPointSize(20);

    // Stylize each and add to view
    for (QLabel *i : indicators) {
        i->setFont(iconsFont); // Apply font to each button
        i->setEnabled(false); // Disable indicators by default
        layout->addWidget(i);
    }

    setLayout(layout);
}

void QUpDownIndicator::clear(){
    upIndicator->setEnabled(false);
    downIndicator->setEnabled(false);
}

void QUpDownIndicator::up(){
    clear();
    upIndicator->setEnabled(true);
}

void QUpDownIndicator::down(){
    clear();
    downIndicator->setEnabled(true);
}
