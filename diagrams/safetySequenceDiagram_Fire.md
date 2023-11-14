### **Safety Scenario: ** Fire

- ECS invokes the Fire signal sequence. Both elevators are set into emergency mode with the fire signal flag.  This disables the elevators, updates the screen and plays a message telling passengers to disembark. The doors then close and make their way to the ground floor. This is done via the elevator's method `overrideGoToFloor(int floor)` , overriding any requests in the `requests` array.
- The ECS then resets the elevators back into an operational state when the fire signal is addressed

```mermaid
sequenceDiagram
	

	participant fireButton#colon;QElevatorButton()
  participant panel#colon;QElevatorPanel()
  participant model#colon;QElevatorModel()
  participant elevator1#colon;Elevator()
 	participant ecs#colon;ElevatorControlSystem()
 	participant externalFloor1UpButton#colon;QElevatorButton()
 	

activate ecs#colon;ElevatorControlSystem()
alt Fire alarm triggered externally
	ecs#colon;ElevatorControlSystem()-)ecs#colon;ElevatorControlSystem(): toggleEmergencyState(EmergencyStatus::FIRE)
else
	fireButton#colon;QElevatorButton()-)panel#colon;QElevatorPanel(): connect
	activate panel#colon;QElevatorPanel()
	panel#colon;QElevatorPanel()->>elevator1#colon;Elevator(): alertECS(EmergencyStatus::FIRE)
	deactivate panel#colon;QElevatorPanel()
	%%%eleevator to ecs
end
 	
deactivate ecs#colon;ElevatorControlSystem()

%% External floor button pressed
Note left of externalFloor1UpButton#colon;QElevatorButton(): Call button to go up pressed from floor 1
externalFloor1UpButton#colon;QElevatorButton()-)ecs#colon;ElevatorControlSystem(): connect()
activate ecs#colon;ElevatorControlSystem()
ecs#colon;ElevatorControlSystem()->>ecs#colon;ElevatorControlSystem(): findBestElevator(1)
ecs#colon;ElevatorControlSystem()->>elevator1#colon;Elevator(): requestFloor(1)
activate elevator1#colon;Elevator()
ecs#colon;ElevatorControlSystem()->>externalFloor1UpButton#colon;QElevatorButton(): on()
activate externalFloor1UpButton#colon;QElevatorButton()
deactivate ecs#colon;ElevatorControlSystem()
elevator1#colon;Elevator()->>elevator1#colon;Elevator(): updateFloorIndicators()
elevator1#colon;Elevator()->>model#colon;QElevatorModel(): clearIndicators()
activate model#colon;QElevatorModel()
elevator1#colon;Elevator()->>model#colon;QElevatorModel(): setFloorIndicator(1, true)
deactivate model#colon;QElevatorModel()
deactivate elevator1#colon;Elevator()


%% Elevator move loop, button pressed from outside
Note over elevator1#colon;Elevator(): Start moving elevator
  activate elevator1#colon;Elevator()
  elevator1#colon;Elevator()-)elevator1#colon;Elevator(): fulfillRequest()
  loop Move towards requested Floor 1
    elevator1#colon;Elevator()->>elevator1#colon;Elevator(): underLimit()
    elevator1#colon;Elevator()->>elevator1#colon;Elevator(): moveUp() / moveDown()
    elevator1#colon;Elevator()->>panel#colon;QElevatorPanel(): updateFloor(floor)
    activate panel#colon;QElevatorPanel()
    deactivate panel#colon;QElevatorPanel()
    elevator1#colon;Elevator()->>model#colon;QElevatorModel(): moveUp() / moveDown()
    activate model#colon;QElevatorModel()
    deactivate model#colon;QElevatorModel()
  end
  elevator1#colon;Elevator()->>elevator1#colon;Elevator(): updateElevatorButtons()
  elevator1#colon;Elevator()->>panel#colon;QElevatorPanel(): clearButtons()
  activate panel#colon;QElevatorPanel()
  elevator1#colon;Elevator()->>panel#colon;QElevatorPanel(): getButton(i-1)
  panel#colon;QElevatorPanel()->>floor4Button#colon;QElevatorButton() : setEnabled(false)
  activate floor4Button#colon;QElevatorButton()
  deactivate floor4Button#colon;QElevatorButton()
  deactivate panel#colon;QElevatorPanel()
  elevator1#colon;Elevator()->>elevator1#colon;Elevator(): updateFloorIndicators()
  elevator1#colon;Elevator()->>model#colon;QElevatorModel(): clearIndicators()
  activate model#colon;QElevatorModel()
  elevator1#colon;Elevator()->>model#colon;QElevatorModel(): setFloorIndicator(i, true)
  deactivate model#colon;QElevatorModel()
  elevator1#colon;Elevator()->>ecs#colon;ElevatorControlSystem(): getFloorButton(floor, UP)
  activate ecs#colon;ElevatorControlSystem()
  ecs#colon;ElevatorControlSystem()->>externalFloor1UpButton#colon;QElevatorButton(): off()
  elevator1#colon;Elevator()->>ecs#colon;ElevatorControlSystem(): getFloorButton(floor, DOWN)
  ecs#colon;ElevatorControlSystem()->>externalFloor1UpButton#colon;QElevatorButton(): off()
  deactivate ecs#colon;ElevatorControlSystem()
  deactivate externalFloor1UpButton#colon;QElevatorButton()
  elevator1#colon;Elevator()->>panel#colon;QElevatorPanel(): updateFloor(floor)
  activate panel#colon;QElevatorPanel()
    deactivate panel#colon;QElevatorPanel()
  elevator1#colon;Elevator()->>elevator1#colon;Elevator(): openDoors()
  %%%%%%%%%%%
  Note over elevator1#colon;Elevator(): Passenger enters elevator from first floor
  %%%%%%%%%%%
  elevator1#colon;Elevator()->>elevator1#colon;Elevator(): closeDoors()
  deactivate elevator1#colon;Elevator()



```
