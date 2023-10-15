### **Safety Scenario: ** Door Obstruction

- When A elevator `flagEmergency(EmergencyStatus::HELP)` 
- 

```mermaid
sequenceDiagram

	participant elevator1#colon;Elevator()
	participant display#colon;Display()
	participant ecs#colon;ElevatorControlSystem()


	activate elevator1#colon;Elevator()
	elevator1#colon;Elevator()->>	elevator1#colon;Elevator(): closeDoor()
	
 elevator1#colon;Elevator()->>elevator1#colon;Elevator(): flagEmergency(EmergencyStatus e)
	elevator1#colon;Elevator()->>elevator1#colon;Elevator(): setStatus(ElevatorStatus e)
	elevator1#colon;Elevator()->>ecs#colon;ElevatorControlSystem(): alertECS()
	activate ecs#colon;ElevatorControlSystem()
	
	
	
	
	
		
	elevator1#colon;Elevator()->>display#colon;Display(): displayWarning(EmergencyStatus e)
	deactivate elevator1#colon;Elevator()
	activate display#colon;Display()
	deactivate display#colon;Display()

	
	
	
	activate elevator1#colon;Elevator()
	ecs#colon;ElevatorControlSystem()->>elevator1#colon;Elevator(): clearEmergency(EmergencyStatus e)
	deactivate ecs#colon;ElevatorControlSystem()
	elevator1#colon;Elevator()->>elevator1#colon;Elevator(): setStatus(ElevatorStatus e)
	
	
	elevator1#colon;Elevator()->>display#colon;Display(): displayWarning(EmergencyStatus e)
	activate display#colon;Display()
	deactivate display#colon;Display()
	deactivate elevator1#colon;Elevator()
```
