#ifndef ELEVATOR_H
#define ELEVATOR_H

#include <vector>

#include "Display.h"

class Elevator {
	public:
		Elevator();

		// User Actions
		bool closeDoors();
		bool openDoors();
		bool requestFloor(Floor f);
		void requestHelp();

		// System Actions
		bool fulfillRequest();
		void preFlightCheck(); // Checks sensors
		bool flagEmergency(EmergencyStatus e);
		bool clearEmergency(EmergencyStatus e);
		bool addFloorRequest(Floor f);
		bool overrideGoToFloor(Floor f);
		void updateDisplay(Floor f);

		// Getters
		Floor getFloor() const;
		Direction getDirection() const;
		DoorStatus getDoorStatus() const;
		ElevatorStatus getStatus() const;
		EmergencyStatus getEmergencyStatus() const;
		Display* getDisplay();

	private:
		Floor floor;
		Direction direction;
		DoorStatus doorStatus;
		ElevatorStatus elevatorStatus;
		EmergencyStatus emergencyStatus;
		std::vector<Floor> requests;
		Display* display;

		bool setStatus(ElevatorStatus e);

};

#endif