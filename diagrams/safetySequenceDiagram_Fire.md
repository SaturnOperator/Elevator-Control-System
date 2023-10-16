### **Safety Scenario: ** Fire

- ECS invokes the Fire singal sequence. Both elevators are set into emergency mode with the fire signal flag.  This disables the elevators, updates the screen and plays a message telling passengers to disembark. The doors then close and make their way to the ground floor. This is done via the elevator's method `overrideGoToFloor(Floor::FLOOR_GROUND)` , overriding any requests in the `requests` array.
- The ECS then resets the elevators back into an operational state when the fire signal is addressed

```mermaid
sequenceDiagram

  	participant elevator1#colon;Elevator()
  	participant display1#colon;Display()
  	participant elevator2#colon;Elevator()
  	participant display2#colon;Display()
 		participant ecs#colon;ElevatorControlSystem()
  	
  	activate ecs#colon;ElevatorControlSystem()
  	ecs#colon;ElevatorControlSystem()-)ecs#colon;ElevatorControlSystem(): fireSafetySequence()
  	
  	ecs#colon;ElevatorControlSystem()-)elevator1#colon;Elevator(): flagEmergency(EmergencyStatus::FIRE)
  	  activate elevator1#colon;Elevator()
  	ecs#colon;ElevatorControlSystem()-)elevator2#colon;Elevator(): flagEmergency(EmergencyStatus::FIRE)

		activate elevator2#colon;Elevator()
  	elevator1#colon;Elevator()->>elevator1#colon;Elevator(): setStatus(ElevatorStatus e)
		elevator2#colon;Elevator()->>elevator2#colon;Elevator(): setStatus(ElevatorStatus e)
		
		elevator1#colon;Elevator()->>display1#colon;Display(): displayWarning(EmergencyStatus e)
	activate display1#colon;Display()
	
		elevator2#colon;Elevator()->>display2#colon;Display(): displayWarning(EmergencyStatus e)
	activate display2#colon;Display()
	
	ecs#colon;ElevatorControlSystem()->>elevator1#colon;Elevator(): kickPassengersOut()
	ecs#colon;ElevatorControlSystem()->>elevator2#colon;Elevator(): kickPassengersOut()
	
	display1#colon;Display()->>display1#colon;Display(): playDisembarkMessage()
	deactivate display1#colon;Display()
	
		display2#colon;Display()->>display2#colon;Display(): playDisembarkMessage()
	deactivate display2#colon;Display()
	
	
	elevator1#colon;Elevator()->>elevator1#colon;Elevator(): closeDoors()
	elevator2#colon;Elevator()->>elevator2#colon;Elevator(): closeDoors()
	
	ecs#colon;ElevatorControlSystem()->>elevator1#colon;Elevator(): overrideGoToFloor(Floor::FLOOR_GROUND)
	ecs#colon;ElevatorControlSystem()->>elevator2#colon;Elevator(): overrideGoToFloor(Floor::FLOOR_GROUND)
	
	
  	
  	deactivate elevator1#colon;Elevator()
		deactivate elevator2#colon;Elevator()
  	
  	deactivate ecs#colon;ElevatorControlSystem()
  	
  	
  	
  	opt Fire signal is addressed, reset elevators
  	 	activate ecs#colon;ElevatorControlSystem()
  		ecs#colon;ElevatorControlSystem()->>elevator1#colon;Elevator(): clearEmergency(EmergencyStatus e)
  		activate elevator1#colon;Elevator()
		ecs#colon;ElevatorControlSystem()->>elevator2#colon;Elevator(): clearEmergency(EmergencyStatus e)
		activate elevator2#colon;Elevator()
	
			deactivate ecs#colon;ElevatorControlSystem()
elevator1#colon;Elevator()->>elevator1#colon;Elevator(): setStatus(ElevatorStatus e)


      elevator1#colon;Elevator()->>display1#colon;Display(): displayWarning(EmergencyStatus e)
      activate display1#colon;Display()
      deactivate display1#colon;Display()
      deactivate elevator1#colon;Elevator()
      
      elevator2#colon;Elevator()->>elevator2#colon;Elevator(): setStatus(ElevatorStatus e)
      elevator2#colon;Elevator()->>display2#colon;Display(): displayWarning(EmergencyStatus e)
      activate display2#colon;Display()
      deactivate display2#colon;Display()
      deactivate elevator2#colon;Elevator()
  	end
```
