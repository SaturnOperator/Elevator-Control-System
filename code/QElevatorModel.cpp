#include "QElevatorModel.h"


QElevatorModel::QElevatorModel(QWidget *parent) : QWidget(parent) {
    QGridLayout* layout = new QGridLayout;
    this->setStyleSheet(
        "QLabel { "
        "   padding: 5px; "
        // "   border: 1px solid gray; "
        "}"
    );

    car = new QScrollBar(Qt::Vertical);
    layout->addWidget(car, 0, 0, NUM_FLOORS*2, 1);
    
    car->setMinimumHeight(40*NUM_FLOORS);

    car->setMinimum(1);
    car->setMaximum(NUM_FLOORS);
    car->setPageStep(1);
    car->setEnabled(false);

    car->setValue(car->maximum()); // Move to bottom

    for (int i = 0; i < NUM_FLOORS; ++i){
        QLabel* floorLabel = new QLabel("•");
        floorLabel->setEnabled(false);
        floorLabel->setStyleSheet(
           "QLabel:enabled { color: #255fe6; }"
           "QLabel:disabled { color: rgba(128, 128, 128, 0.1);  }"
        );

        indicators << floorLabel;
        layout->addWidget(floorLabel, i*2, 1, 2, 1);
    }

    setLayout(layout);
}


void QElevatorModel::moveCar(int position){
    if(position < 1 || position > NUM_FLOORS){
        return;
    }

    car->setValue(NUM_FLOORS-position+1);
}


void QElevatorModel::moveUp(){
    int floor = car->value();
    if(floor > 1){
        car->setValue(floor-1);
    }
}

void QElevatorModel::moveDown(){
    int floor = car->value();
    if(floor < NUM_FLOORS){
        car->setValue(floor+1);
    }
}

void QElevatorModel::setFloorIndicator(int floor, bool enable){
    if(floor >= 0 && floor <= NUM_FLOORS){
        indicators[floor]->setEnabled(enable);
    }
}