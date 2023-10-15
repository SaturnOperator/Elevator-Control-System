### **Safety Scenario: ** Help button is pressed

- When A passenger presses the help button, an emergency procedure is initiated.  elevator flags the error with `flagEmergency(EmergencyStatus::HELP)`, this value gets added to the elevator's `emergencyStatus` (rather than set). The elevator's `alertECS()` method then alerts the ECS.
- When the  `emergencyStatus` is changed and the value isn't zero, the `elevatorStatus` value is set to error mode and becomes inoperative until the problem has been addressed. `emergencyStatus` can only be cleared by the ECS when conditions are deemed safe.
- *Note*: Each EmergencyStatus is a different bit value so you can set multiple emergency statuses at once. (For example `EmegencyStatus::OBSTRUCTION|EmegencyStatus::OVERLOAD = 0x6 ` This value can also be decoded to find out which emergency statuses have been set.) 

```mermaid
sequenceDiagram

	participant passengerA#colon;Passenger()
	participant elevator1#colon;Elevator()
	participant display#colon;Display()
	participant ecs#colon;ElevatorControlSystem()
	participant Building Safety Service
	participant #nbsp;911
	
	passengerA#colon;Passenger()-)elevator1#colon;Elevator(): pressHelpButton()
	activate passengerA#colon;Passenger()
	activate elevator1#colon;Elevator()
	
	

	elevator1#colon;Elevator()->>elevator1#colon;Elevator(): helpButton()
	elevator1#colon;Elevator()->>elevator1#colon;Elevator(): flagEmergency(EmergencyStatus e)
	elevator1#colon;Elevator()->>elevator1#colon;Elevator(): setStatus(ElevatorStatus e)
	elevator1#colon;Elevator()->>ecs#colon;ElevatorControlSystem(): alertECS()
	activate ecs#colon;ElevatorControlSystem()
	elevator1#colon;Elevator()->>display#colon;Display(): displayWarning(EmergencyStatus e)
	activate display#colon;Display()
	deactivate display#colon;Display()
	deactivate elevator1#colon;Elevator()
	
	
	alt Response from Building Safety and Passenger within 5 s
		ecs#colon;ElevatorControlSystem()->>+Building Safety Service: helpCallBuilding()
		ecs#colon;ElevatorControlSystem()->>+elevator1#colon;Elevator(): helpReceiveResponse(Elevator* e)
		passengerA#colon;Passenger()->>elevator1#colon;Elevator(): respond()
		Building Safety Service->>-ecs#colon;ElevatorControlSystem(): addressEmergency(Elevator* e, EmergencyStatus e)
	else No response from either
		ecs#colon;ElevatorControlSystem()->>+#nbsp;911: helpCall911()
		#nbsp;911->>-ecs#colon;ElevatorControlSystem(): addressEmergency(Elevator* e, EmergencyStatus e)
	end
	deactivate elevator1#colon;Elevator()
	
	
	deactivate passengerA#colon;Passenger()
	
	activate elevator1#colon;Elevator()
	ecs#colon;ElevatorControlSystem()->>elevator1#colon;Elevator(): clearEmergency(EmergencyStatus e)
	deactivate ecs#colon;ElevatorControlSystem()
	elevator1#colon;Elevator()->>elevator1#colon;Elevator(): setStatus(ElevatorStatus e)
	
	
	elevator1#colon;Elevator()->>display#colon;Display(): displayWarning(EmergencyStatus e)
	activate display#colon;Display()
	deactivate display#colon;Display()
	deactivate elevator1#colon;Elevator()
```
