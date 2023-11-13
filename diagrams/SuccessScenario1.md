### **Success Scenario 1: ** Passenger requests elevator and rides it to floor *f* 

- Passenger calls the elevator from an arbitrary floor *f*, the ECS will find the nearest available elevator `findBestElevator()` and add floor *f* to that elevator's requests array `QList<int> requests`. The Elevator will instruct itself to move through `fulfillRequest()`, continuously calling this method until the request is complete. Each time this method is called the elevator will move one floor if there is a request. A request is completed when the elevator arrives at the floor of the request, at this point the doors will opens. 
- When the elevator reaches the floor of which the button was pressed from, the passenger enters and the door closes after 10 seconds. At this point in time the elevator and ECS is still polling `fulfillRequest()` however nothing is done as the requests queue is empty
- When the passenger presses a floor button to go to a different (or same) arbitrary floor *f*, that floor is added to the `requests` array, the elevator to start moving with `fulfillRequest()` again until the elevator reaches the requested floor.
- This design allows for a robust system that encompasses different scenarios as well without altering the flow of the system. For example an edge case would what if a passenger calls the elevator and the elevator is already on that floor? Or alternatively the passenger enters on floor 1, the door closes and passenger presses floor 1? In this system, the floor is added to the `request` array as normal, the Elevator will try fulfill that request. When the elevator sees its already at the destination floor then the request is deemed complete, at which the doors will then open.

```mermaid
sequenceDiagram
	

	participant floor4Button#colon;QElevatorButton()
  participant panel#colon;QElevatorPanel()
  participant model#colon;QElevatorModel()
  participant elevator1#colon;Elevator()
 	participant ecs#colon;ElevatorControlSystem()
 	participant externalFloor1UpButton#colon;QElevatorButton()

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
  elevator1#colon;Elevator()->>elevator1#colon;Elevator(): openDoors()
  %%%%%%%%%%%
  Note over elevator1#colon;Elevator(): Passenger enters elevator from first floor
  %%%%%%%%%%%
  elevator1#colon;Elevator()->>elevator1#colon;Elevator(): closeDoors()
  deactivate elevator1#colon;Elevator()
end


%% Floor button pressed inside elevator
Note right of floor4Button#colon;QElevatorButton(): Passenger pressed floor 4 button inside elevator
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
  elevator1#colon;Elevator()->>elevator1#colon;Elevator(): openDoors()
  %%%%%%%%%%%
  Note over elevator1#colon;Elevator(): Passenger exits on 4th floor
  %%%%%%%%%%%
  elevator1#colon;Elevator()->>elevator1#colon;Elevator(): closeDoors()
  deactivate elevator1#colon;Elevator()
end



```







