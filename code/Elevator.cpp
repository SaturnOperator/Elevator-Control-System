#include "Elevator.h"

Elevator::Elevator(){
	maxLoad = MAX_LOAD;
	panel = new QElevatorPanel();
	model = new QElevatorModel();
}

QElevatorPanel* Elevator::getPanel(){
	return panel;
}
QElevatorModel* Elevator::getModel(){
	return model;
}