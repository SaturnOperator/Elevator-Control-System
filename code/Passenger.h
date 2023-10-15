#ifndef PASSENGER_H
#define PASSENGER_H

#include "Elevator.h"

class Passenger {
	public:
		Passenger();
		~Passenger();

		Floor enterElevator(Elevator e);
		Floor exitElevator();

		void callElevator(Floor f, Direction dir);
		void pressFloorButton(Floor f);
		
		// Emergency situations
		void pressHelpButton();
		void respond();

	private:
		Floor floor;
		Elevator* elevator;
};

#endif