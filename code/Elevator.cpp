#include "Elevator.h"

Elevator::Elevator(){
	maxLoad = MAX_LOAD;
	panel = new QElevatorPanel(this);
	model = new QElevatorModel();
}

int Elevator::getFloor() const{
	return floor;
}

QElevatorPanel* Elevator::getPanel() const{
	return panel;
}
QElevatorModel* Elevator::getModel() const{
	return model;
}

bool Elevator::requestFloor(int floor, Direction dir){
	requests[floor] = dir;

	model->clearIndicators();
	for (int i : requests.keys()){
		model->setFloorIndicator(i, true);
	}

	qInfo() << "Adding floor" << floor << "request to" << this << ":" << requests.keys();

	return true;
}