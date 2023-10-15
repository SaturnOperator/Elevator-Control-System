#ifndef DISPLAY_H
#define DISPLAY_H

#include "defs.h"

class Display {
	public:
		Display();
		~Display();



		void ringBell();
		void updateFloor(Floor f);
 		void updateDirection(Direction d);
		
		void displayWarning(EmergencyStatus e);
		void clearDisplay();

	private:
		Floor floor;
		Direction direction;
		EmergencyStatus emergencyStatus;
 };

 #endif