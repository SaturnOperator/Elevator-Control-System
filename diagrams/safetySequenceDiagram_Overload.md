### **Safety Scenario: ** Overload

- Elevator will attempt to close the door, `closeDoor()` will check safety sensors such as the light curtain obstruction sensor, as well as the overload sensor. If any of these sensors are triggered `closeDoor()` fails and returns false, flagging an emergency and alerting the ECS. Elevator gets set to `ElevatorStatus::ERROR` and will remain non-operational. At this point the ECS will keep checking the obstruction sensor until the overload isn't present. The ECS will clear the emergency flags the elevator is deemed safe (no overload) and the elevator will return back to an operating state.

```mermaid
sequenceDiagram

	participant elevator1#colon;Elevator()
	participant display#colon;Display()
	participant ecs#colon;ElevatorControlSystem()


	activate elevator1#colon;Elevator()
	elevator1#colon;Elevator()->>	elevator1#colon;Elevator(): closeDoor()
	note right of elevator1#colon;Elevator(): when closeDoor() returns false, an overload is triggered
 elevator1#colon;Elevator()->>elevator1#colon;Elevator(): flagEmergency(EmergencyStatus e)
	elevator1#colon;Elevator()->>elevator1#colon;Elevator(): setStatus(ElevatorStatus e)
	elevator1#colon;Elevator()->>ecs#colon;ElevatorControlSystem(): alertECS()
	activate ecs#colon;ElevatorControlSystem()
	
	
	
	
	
		
	elevator1#colon;Elevator()->>display#colon;Display(): displayWarning(EmergencyStatus e)
	
	deactivate elevator1#colon;Elevator()
	activate display#colon;Display()
	deactivate display#colon;Display()
	
		activate elevator1#colon;Elevator()
	loop Until underLimit() returns false
		ecs#colon;ElevatorControlSystem()->>elevator1#colon;Elevator(): underLimit()
	end

	
	
	

	ecs#colon;ElevatorControlSystem()->>elevator1#colon;Elevator(): clearEmergency(EmergencyStatus e)
	deactivate ecs#colon;ElevatorControlSystem()
	elevator1#colon;Elevator()->>elevator1#colon;Elevator(): setStatus(ElevatorStatus e)
	
	
	elevator1#colon;Elevator()->>display#colon;Display(): displayWarning(EmergencyStatus e)
	activate display#colon;Display()
	deactivate display#colon;Display()
	deactivate elevator1#colon;Elevator()
```
