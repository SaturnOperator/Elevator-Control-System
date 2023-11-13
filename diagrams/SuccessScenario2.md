### **Success Scenario 2: ** Passenger *A* on 1st floor requests elevator to floor 4, at the same time Passenger *B* on 2nd floor requests elevator to go to floor 3.

- Note: This scenario builds off *Success Scenario 1*, please read description for that one first to have better understanding of how the system functions. 
- This scenario assumes both Passengers use the same elevator
- When Passenger *A* gets on the elevator and chooses to go to the 4th floor, that is added to the elevator's `requests` array. The Elevator will then instruct itself to move floor by floor until it reaches the requested floor. `requests = [4]`
- During this time Passenger *B* calls the elevator from the 2nd floor. The Elevator adds the second floor to the `requests` so now `requests = [2, 4]`.
- The elevator reaches the second floor so 2 is removed from the `requests` array as that floor request has now been fulfilled. `requests = [4]`
- When passenger three chooses to press the button to the third floor, that is also added to the requests array, so now `requests = [3, 4]`.
- Now the elevator ascends to the 3rd, then fourth floor fulfilling those two floor requests. 

```mermaid
sequenceDiagram
	

	participant floor4Button#colon;QElevatorButton()
	participant floor3Button#colon;QElevatorButton()
  participant panel#colon;QElevatorPanel()
  participant model#colon;QElevatorModel()
  participant elevator1#colon;Elevator()
 	participant ecs#colon;ElevatorControlSystem()
 	participant externalFloor1UpButton#colon;QElevatorButton()
 	participant externalFloor2UpButton#colon;QElevatorButton()

%% External floor button pressed
Note left of externalFloor1UpButton#colon;QElevatorButton(): Call button to go up pressed from floor 1 by passenger 1
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
%%loop while requests list is not empty, this happens asynchronously per elevator
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
  Note over elevator1#colon;Elevator(): Passenger 1 enters elevator from first floor
  %%%%%%%%%%%
  elevator1#colon;Elevator()->>elevator1#colon;Elevator(): closeDoors()
  deactivate elevator1#colon;Elevator()
%%end

%% Floor button pressed inside elevator
Note right of floor4Button#colon;QElevatorButton(): Passenger 1 presses floor 4 button inside elevator
floor4Button#colon;QElevatorButton()-)panel#colon;QElevatorPanel(): connect()
activate panel#colon;QElevatorPanel()
activate floor4Button#colon;QElevatorButton()
floor4Button#colon;QElevatorButton()->>floor4Button#colon;QElevatorButton(): on()
panel#colon;QElevatorPanel()->>elevator1#colon;Elevator(): requestFloor(4)
deactivate panel#colon;QElevatorPanel()
activate elevator1#colon;Elevator()
elevator1#colon;Elevator()->>elevator1#colon;Elevator(): updateFloorIndicators()
elevator1#colon;Elevator()->>model#colon;QElevatorModel(): clearIndicators()
activate model#colon;QElevatorModel()
elevator1#colon;Elevator()->>model#colon;QElevatorModel(): setFloorIndicator(1, true)
deactivate model#colon;QElevatorModel()
deactivate elevator1#colon;Elevator()

%% External floor button pressed by passenger 2
Note left of externalFloor2UpButton#colon;QElevatorButton(): Passenger 2 presses call button to go up from floor 2
externalFloor2UpButton#colon;QElevatorButton()-)ecs#colon;ElevatorControlSystem(): connect()
activate ecs#colon;ElevatorControlSystem()
ecs#colon;ElevatorControlSystem()->>ecs#colon;ElevatorControlSystem(): findBestElevator(1)
ecs#colon;ElevatorControlSystem()->>elevator1#colon;Elevator(): requestFloor(1)
activate elevator1#colon;Elevator()
ecs#colon;ElevatorControlSystem()->>externalFloor2UpButton#colon;QElevatorButton(): on()
activate externalFloor2UpButton#colon;QElevatorButton()
deactivate ecs#colon;ElevatorControlSystem()
elevator1#colon;Elevator()->>elevator1#colon;Elevator(): updateFloorIndicators()
elevator1#colon;Elevator()->>model#colon;QElevatorModel(): clearIndicators()
activate model#colon;QElevatorModel()
elevator1#colon;Elevator()->>model#colon;QElevatorModel(): setFloorIndicator(1, true)
deactivate model#colon;QElevatorModel()
deactivate elevator1#colon;Elevator()


%% Elevator move loop, button pressed from inside
Note over elevator1#colon;Elevator(): Start moving elevator
loop while requests list is not empty, this happens asynchronously per elevator
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
  %%activate panel#colon;QElevatorPanel()
  %%elevator1#colon;Elevator()->>panel#colon;QElevatorPanel(): getButton(i-1)
  %%panel#colon;QElevatorPanel()->>floor4Button#colon;QElevatorButton() : setEnabled(false)
  %%deactivate externalFloor2UpButton#colon;QElevatorButton()
  %%activate floor4Button#colon;QElevatorButton()
  %%deactivate floor4Button#colon;QElevatorButton()
  %%deactivate panel#colon;QElevatorPanel()
  elevator1#colon;Elevator()->>elevator1#colon;Elevator(): updateFloorIndicators()
  elevator1#colon;Elevator()->>model#colon;QElevatorModel(): clearIndicators()
  activate model#colon;QElevatorModel()
  elevator1#colon;Elevator()->>model#colon;QElevatorModel(): setFloorIndicator(i, true)
  deactivate model#colon;QElevatorModel()
  elevator1#colon;Elevator()->>ecs#colon;ElevatorControlSystem(): getFloorButton(floor, UP)
  activate ecs#colon;ElevatorControlSystem()
  ecs#colon;ElevatorControlSystem()->>externalFloor1UpButton#colon;QElevatorButton(): off()
  activate externalFloor1UpButton#colon;QElevatorButton()
  ecs#colon;ElevatorControlSystem()->>externalFloor2UpButton#colon;QElevatorButton(): off()

 
  elevator1#colon;Elevator()->>ecs#colon;ElevatorControlSystem(): getFloorButton(floor, DOWN)
  ecs#colon;ElevatorControlSystem()->>externalFloor1UpButton#colon;QElevatorButton(): off()
  ecs#colon;ElevatorControlSystem()->>externalFloor2UpButton#colon;QElevatorButton(): off()
  deactivate ecs#colon;ElevatorControlSystem()
  deactivate externalFloor1UpButton#colon;QElevatorButton()
  deactivate externalFloor2UpButton#colon;QElevatorButton()
  elevator1#colon;Elevator()->>panel#colon;QElevatorPanel(): updateFloor(floor)
  activate panel#colon;QElevatorPanel()
  deactivate panel#colon;QElevatorPanel()
  elevator1#colon;Elevator()->>elevator1#colon;Elevator(): openDoors()
  %%%%%%%%%%%
  Note over elevator1#colon;Elevator(): Passenger 2 enters elevator from 2nd floor 
  %%%%%%%%%%%
  elevator1#colon;Elevator()->>elevator1#colon;Elevator(): closeDoors()
  deactivate elevator1#colon;Elevator()
end

%%%%%%%%%%%%%%%%%%%%%%%%

%% Floor button pressed inside elevator
Note right of floor3Button#colon;QElevatorButton(): Passenger 2 presses floor 3 button inside elevator
floor3Button#colon;QElevatorButton()-)panel#colon;QElevatorPanel(): connect()
activate panel#colon;QElevatorPanel()
activate floor3Button#colon;QElevatorButton()
floor3Button#colon;QElevatorButton()->>floor3Button#colon;QElevatorButton(): on()
panel#colon;QElevatorPanel()->>elevator1#colon;Elevator(): requestFloor(4)
deactivate panel#colon;QElevatorPanel()
activate elevator1#colon;Elevator()
elevator1#colon;Elevator()->>elevator1#colon;Elevator(): updateFloorIndicators()
elevator1#colon;Elevator()->>model#colon;QElevatorModel(): clearIndicators()
activate model#colon;QElevatorModel()
elevator1#colon;Elevator()->>model#colon;QElevatorModel(): setFloorIndicator(1, true)
deactivate model#colon;QElevatorModel()
deactivate elevator1#colon;Elevator()



%% Elevator move loop, button pressed from outside
Note over elevator1#colon;Elevator(): Start moving elevator
loop while requests list is not empty, this happens asynchronously per elevator
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
  panel#colon;QElevatorPanel()->>floor3Button#colon;QElevatorButton() : setEnabled(false)
  %%activate floor3Button#colon;QElevatorButton()
  deactivate floor3Button#colon;QElevatorButton()
  deactivate panel#colon;QElevatorPanel()
  elevator1#colon;Elevator()->>elevator1#colon;Elevator(): updateFloorIndicators()
  elevator1#colon;Elevator()->>model#colon;QElevatorModel(): clearIndicators()
  activate model#colon;QElevatorModel()
  elevator1#colon;Elevator()->>model#colon;QElevatorModel(): setFloorIndicator(i, true)
  deactivate model#colon;QElevatorModel()
  elevator1#colon;Elevator()->>ecs#colon;ElevatorControlSystem(): getFloorButton(floor, UP)
  activate ecs#colon;ElevatorControlSystem()

  activate externalFloor1UpButton#colon;QElevatorButton()
  ecs#colon;ElevatorControlSystem()->>externalFloor1UpButton#colon;QElevatorButton(): off()
  elevator1#colon;Elevator()->>ecs#colon;ElevatorControlSystem(): getFloorButton(floor, DOWN)
  ecs#colon;ElevatorControlSystem()->>externalFloor1UpButton#colon;QElevatorButton(): off()
  deactivate ecs#colon;ElevatorControlSystem()
  deactivate externalFloor1UpButton#colon;QElevatorButton()

  activate externalFloor2UpButton#colon;QElevatorButton()
  ecs#colon;ElevatorControlSystem()->>externalFloor2UpButton#colon;QElevatorButton(): off()
  elevator1#colon;Elevator()->>ecs#colon;ElevatorControlSystem(): getFloorButton(floor, DOWN)
  ecs#colon;ElevatorControlSystem()->>externalFloor2UpButton#colon;QElevatorButton(): off()
  %%deactivate ecs#colon;ElevatorControlSystem()
  deactivate externalFloor2UpButton#colon;QElevatorButton()

  elevator1#colon;Elevator()->>panel#colon;QElevatorPanel(): updateFloor(floor)
  activate panel#colon;QElevatorPanel()
  deactivate panel#colon;QElevatorPanel()
  elevator1#colon;Elevator()->>elevator1#colon;Elevator(): openDoors()
  %%%%%%%%%%%
  Note over elevator1#colon;Elevator(): Passenger 2 exits on 3rd floor
  %%%%%%%%%%%
  elevator1#colon;Elevator()->>elevator1#colon;Elevator(): closeDoors()
  deactivate elevator1#colon;Elevator()
end

%%%%%%%%%%%%%%%%%%%%%%%%

%% Elevator move loop, button pressed from inside
Note over elevator1#colon;Elevator(): Start moving elevator
%%loop while requests list is not empty, this happens asynchronously per elevator
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
  %%activate floor4Button#colon;QElevatorButton()
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
  activate externalFloor1UpButton#colon;QElevatorButton()
  elevator1#colon;Elevator()->>ecs#colon;ElevatorControlSystem(): getFloorButton(floor, DOWN)
  ecs#colon;ElevatorControlSystem()->>externalFloor1UpButton#colon;QElevatorButton(): off()
  deactivate ecs#colon;ElevatorControlSystem()
  deactivate externalFloor1UpButton#colon;QElevatorButton()
  elevator1#colon;Elevator()->>panel#colon;QElevatorPanel(): updateFloor(floor)
  activate panel#colon;QElevatorPanel()
    deactivate panel#colon;QElevatorPanel()
  elevator1#colon;Elevator()->>elevator1#colon;Elevator(): openDoors()
  %%%%%%%%%%%
  Note over elevator1#colon;Elevator(): Passenger exits on 4th floor
  %%%%%%%%%%%
  elevator1#colon;Elevator()->>elevator1#colon;Elevator(): closeDoors()
  deactivate elevator1#colon;Elevator()
%%end



```







