# COMP 3004 Assignment 3

```
Name: Abdullah Mostafa
Student Number: 101008311
Date: Oct 15, 2023
```



## Table of Contents

[TOC]



## Elevator Control System Simulator

![newGUI](newGUI.png)



## UML Class Diagram

```mermaid
classDiagram
	ElevatorControlSystem "1" --> "*" Elevator: has 1 .. *
	ElevatorControlSystem "1" --> "*" QElevatorButton: has 1 .. *
	Elevator "1" --> "1" QElevatorPanel: has 1
	Elevator "1" --> "1" QElevatorModel: has 1
	QElevatorPanel "1" --> "1" QErrorIndicator: has 1
	QElevatorPanel "1" --> "1" QUpDownIndicator: has 1
	QElevatorPanel "1" --> "*" QElevatorButton: has 1 .. *
	Elevator --|> QObject
	ElevatorControlSystem --|> QObject
	QElevatorButton --|> QPushButton
	QElevatorModel --|> QWidget
	QElevatorPanel --|> QGroupBox
	QErrorIndicator --|> QWidget
	QUpDownIndicator --|> QWidget
	
	class Elevator{
	+closeDoors(): bool
+openDoors(): bool
+requestFloor(int floor, Direction dir): bool
+helpButton(): bool
+fulfillRequest(): bool
+moveUp(): bool
+moveDown(): bool
+updateFloorIndicators(): void
+updateElevatorButtons(): void
+alertECS(EmergencyStatus e): void
+flagEmergency(EmergencyStatus e): void
+clearEmergency(EmergencyStatus e): void
+addFloorRequest(int floor): bool
+overrideGoToFloor(int floor): bool
-floor: int
-direction: Direction
-doorStatus: DoorStatus
-elevatorStatus: ElevatorStatus
-emergencyStatus: int
-requests: QList<int>
-timer: QTimer*
-load: int
-maxLoad: int
-underLimit(): bool

	}
	
	class ElevatorControlSystem{
+findBestElevator(int floor): Elevator*
+resetButtons(): void
+helpSafetySequence(Elevator* e): bool
+helpCall911(): void
+addressEmergency(Elevator* e, EmergencyStatus status): void
+activateFireSafetySequence(): void
+clearFire(): void
+activateOutageSafetySequence(): void
+clearOutage(): void
-numFloors: int
-emergencyStatus: int
-outageTestButton: QPushButton*
-fireTestButton: QPushButton*
-helpResponseButton: QPushButton*
-overloadSelector: QComboBox*
-obstructionSelector: QComboBox*
-helpTimer: QTimer*
-helpLoop: QEventLoop*
-helpCallResponded: bool
-elevatorThreads: QList<QThread*>
-toggleEmergencyState(EmergencyStatus e): void
	}
	
class QElevatorButton{
	+on(): void
	+off(): void
	-size: int
	-stylize():void
}

class QElevatorModel{
+moveCar(int position): void
+moveUp(): void
+moveDown(): void
+clearIndicators(): void
-car: QScrollBar*
-indicators: QList<QLabel*>
}

class QElevatorPanel{
+updateFloor(int floor): bool
+clearButtons(): void
+showErrors(): void
+clear(): void
-floor: int
-titleLabel: QLabel*
-errors: QErrorIndicator*
-screen: QLCDNumber*
-buttonDoorOpen: QElevatorButton*
-buttonDoorClose: QElevatorButton*
-buttonHelp: QElevatorButton*
-buttonFire: QElevatorButton*
}

class QErrorIndicator{
-value: int
-errorMessage: QLabel*
-obstacleIcon: QLabel*
-overloadIcon: QLabel*
-helpIcon: QLabel*
-outageIcon: QLabel*
-fireIcon: QLabel*
}

class QUpDownIndicator{
+up(): void
+down(): void
-upIndicator: QLabel*
-downIndicator:QLabel*
}
```

<hr>

## Traceability Matrix

| Id   | Requirement                                                  | Related Use Case                    | Fullfilled By                                                | Description                                                  | Tested By                                                    |
| ---- | ----------- | --- | ------------------------------------------------------------ | ------------------------------------------------------------ | ------------------------------------------------------------------------- |
| 01 | Elevator responds to external floor buttons                  | Passenger uses elevator             | `Elevator::requestFloor(int Floor, Direction d)`             | Allows the elevator to respond to external floor buttons     | Pressing an external button and seeing if the elevator comes to that floor |
| 02   | Elevator responds to internal floor buttons                  | Passenger uses elevator             | `Elevator::requestFloor(int Floor)`                          | Allows the elevator to respond to floor buttons in the elevator | Pressing a button on the elevator panel and seeing if the elevator goes to that floor |
| 03   | Elevator moves between floors                                | Passenger uses elevator             | `Elevator::fulfillRequest()`                                 | This ensures the elevator car can move between one floor to another by handling the requests | Engage with the elevator by calling it and go to a different floor to see if it moves |
| 04   | Elevator can open its doors                                  | Passenger uses elevator             | `Elevator::openDoors()`                                      | Ensures elevator can open its doors                          | - Call an elevator by pressing an external floor button. <br /><br />- Use the door open button. |
| 05   | Elevator can close its doors                                 | Passenger uses elevator             | `Elevator::closeDoors()`                                     | Ensures elevator can close its doors                         | - Engage with the elevator and see if the door closes after. <br /><br />- Use the door close button. |
| 06   | Elevator goes to ground floor during fire alarm              | Fire alarm from building            | `ElevatorControlSystem::activateFireSafetySequence()`        | Allows for proper safety protocol during a fire alarm        | - Press the fire button inside the elevator.<br /><br />- Trigger the building fire alarm through the ECS admin panel |
| 07   | Elevator goes to ground floor during power outage            | Power outage in the building        | `ElevatorControlSystem::activateOutageSafetySequence()`      | Allows for proper safety protocol during a fire outage       | Trigger building power outage through the ECS admin panel |
| 08   | Help button triggers emergency response                      | Control system receives Help signal | `ElevatorControlSystem::helpSafetySequence()`                | Allows the system to respond to help calls                   | Help button is pressed in the elevator panel.<br /><br />- Can test it by not responding to the call and seeing if the ECS dials 911.<br /><br />- You can also test it by responding to the call from the ECS panel to address the emergency |
| 09   | Door obstacle prevents door from closing                     | Door obstacle detected              | `Elevator::closeDoors()`                                     | Ensures doors don't close when there is something obstructing the door from closing | Engage with any operation that closes the elevator doors, i.e press door close button.<br /><br />- Trigger a simulated door obstacle in the ECS Admin Panel to see if doors don't close and the panel shows the error |
| 10   | Overload limit in elevator                                   | Overload detected                   | `Elevator::underLimit()`                                     | Ensures the elevator doesn't move when it surpasses the load limit | Engage in any elevator operation where the door closes.<br /><br />- Trigger a simulated overload in the ECS Admin Panel to see if the elevator responds accordingly and shows the error |
| 11   | Update display floor number                                  | Many                                | `QElevatorPanel::updateFloor(int floor)`                     | Ensures the elevator's display shows the according floor number | Engage with the elevator in any way that moves it up or down and see if the floor updates in the panel |
| 12   | Show warnings on the display                                 | many                                | `QErrorIndicator::setErrorCode(int error)`                   | Ensures elevator's display shows the appropriate warning to the car passengers | Trigger each of the different emergency scenarios in the ECS admin panel or from the elevator panel and see if the error shows in the elevator car |
| 13   | Ring bell                                                    | many                                | `Elevator::fulfillRequest()`                                 | Allows the elevator to ring a bell upon floor arrival        | Have the elevator move to any floor and see if it dings |
| 14   | Illuminate floor buttons when pressed                        | Passenger uses elevator             | `QElevatorButton::on()` and `QElevatorButton::off()`         | Allows for the system to indicate the request has been put in | Interact with any floor button and see if it illuminates |
| 15   | Turn off Illuminated floor buttons when request is fulfilled | Passenger uses elevator             | `Elevator::updateElevatorButtons()` and `Elevator::updateFloorIndicators()` | Allows for the system to clear fulfilled requests            | Have the elevator go to the floor of the pressed button and see if the button illumination turns off |



<hr>

## Design Patterns Used


Throughout the design of the Elevator controller simulator's a couple  different design patterns were used to make the design more robust and organized.

The `ElevatorControlSystem` (ECS) is implemented as a Singleton Pattern, there is exactly one instance of the ECS class. This allows for a single point of control for all the elevators.

The way the elevators are controlled follows an Observer Pattern and a Command Pattern design. The ECS observes all the states of the different elevators, sensors, buttons etc and then commands each entity on the next instruction.

<hr>

## Use Case for Elevator Control System

**Use case: Using an Elevator**  

<u>**Primary Actor**</u>: Passenger 

<u>**Scope**</u>: Elevator control system

<u>**Level**</u>: User goal

<u>**Stakeholders and interests**</u>:

- <u>Passenger</u>: Wants to ride the elevator to a different floor 
- <u>Control System</u>: Responds to the elevator requests and overlooks safety systems
- <u>Building management</u>: Ensures the elevator operates safely and handles emergencies if they were to occur
- <u>Safety service</u>: Provides help in emergency situations

<u>**Pre-conditions**</u>: 

- The elevator is operational

<u>**Post-conditions**</u>: 

- The elevator arrives at the floor that the passenger requested

<u>**Minimal Guarantees**</u>: 

<u>**Success Guarantees**</u>:

<u>**Trigger**</u>: The passenger calls the elevator with the Up/Down button on the floor they want to move away from

<u>**Main Success Scenario**</u>:

1. The passenger presses Up/Down button on the floor to request the elevator

    ​	a. The pressed button illuminates

    ​	b. A request signal is sent to the control system to bring the car down to that floor

2. The elevator starts moving to the requested floor if it is not already there

    ​	a. The bell rings when the elevator car arrives

    ​	b. The floor indicator on the screen updates to the current floor

    ​	c. The elevator announces what floor it is on

    ​	d. The up/down button light on the floor to request the elevator turns off

    ​	e. The doors on the elevator's car opens and remains open for 10 seconds

3. The passenger enters the elevator

    ​	a. The passenger presses the floor they want to go to 

    ​	b. The light on the pressed floor illuminates

    ​	c.  The bell rings and the doors close

4. The elevator moves to the requested floor

    ​	a. The bell rings when the elevator car arrives

    ​	b. The floor indicator on the screen updates to the current floor

    ​	c. The elevator announces what floor it is on

    ​	d. The floor button light that was pressed turns off

    ​	e. The doors on the elevator's car opens and remains open for 10 seconds

5. The passenger exits on the floor they wanted to go to

<u>**Extensions**</u>:

6. Help button is pressed

    ​	a. Control system receives a help request

    ​	b. Passenger is connected to the safety service through a voice connection

    ​	c. If no response from the passenger or safety service within 5 seconds, 911 is called

7. Door obstacle is detected 

    ​	a. An audible alert is played

    ​	b. The door is prevented from closing until the obstacle is clear from the door

8. Fire alarm was set off in the building or in the elevator

    ​	a.  The control system instructs the elevator to go to the nearest safest floor

    ​	b. The elevator plays a warning message and shows it on the screen

9. Overload is detected 

    ​	a. An audible alert is played and the screen updates

    ​	b. The door is prevented from closing until the overload sensor detects a safe load

10. Door open button is pressed

    ​	a. The doors remain open for another 10 seconds or until the button isn't being pressed anymore

11. Door close button is pressed

    ​	a. The doors attempt to close right away
    
    

<hr>


## Sequence Diagrams

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









<hr>



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











<hr>

### Safety Scenario: Fire

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


<hr>

### Safety Scenario: Help button is pressed

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


<hr>

### Safety Scenario: Door Obstruction

- Elevator will attempt to close the door, `closeDoor()` will check safety sensors such as the light curtain obstruction sensor, as well as the overload sensor. If any of these sensors are triggered `closeDoor()` fails and returns false, flagging an emergency and alerting the ECS. Elevator gets set to `ElevatorStatus::ERROR` and will remain non-operational. At this point the ECS will keep checking the obstruction sensor until the obstruction has been cleared. The ECS will clear the emergency flags the elevator is deemed safe (obstruction cleared) and the elevator will return back to an operating state.

```mermaid
sequenceDiagram

	participant elevator1#colon;Elevator()
	participant display#colon;Display()
	participant ecs#colon;ElevatorControlSystem()


	activate elevator1#colon;Elevator()
	elevator1#colon;Elevator()->>	elevator1#colon;Elevator(): closeDoor()
	note right of elevator1#colon;Elevator(): when closeDoor() returns false door obstruction is triggered
 elevator1#colon;Elevator()->>elevator1#colon;Elevator(): flagEmergency(EmergencyStatus e)
	elevator1#colon;Elevator()->>elevator1#colon;Elevator(): setStatus(ElevatorStatus e)
	elevator1#colon;Elevator()->>ecs#colon;ElevatorControlSystem(): alertECS()
	activate ecs#colon;ElevatorControlSystem()
	
	
	
	
	
		
	elevator1#colon;Elevator()->>display#colon;Display(): displayWarning(EmergencyStatus e)
	
	deactivate elevator1#colon;Elevator()
	activate display#colon;Display()
	deactivate display#colon;Display()
	
		activate elevator1#colon;Elevator()
	loop Until checkObstruction() returns false
		ecs#colon;ElevatorControlSystem()->>elevator1#colon;Elevator(): pollObstructionSensor()
	end

	
	
	

	ecs#colon;ElevatorControlSystem()->>elevator1#colon;Elevator(): clearEmergency(EmergencyStatus e)
	deactivate ecs#colon;ElevatorControlSystem()
	elevator1#colon;Elevator()->>elevator1#colon;Elevator(): setStatus(ElevatorStatus e)
	
	
	elevator1#colon;Elevator()->>display#colon;Display(): displayWarning(EmergencyStatus e)
	activate display#colon;Display()
	deactivate display#colon;Display()
	deactivate elevator1#colon;Elevator()
```


<hr>

### Safety Scenario: Power Outage

- ECS invokes the power outage sequence. Both elevators are set into emergency mode with the power outage flag.  This disables the elevators, updates the screen and plays a message telling passengers to disembark. The doors then close and make their way to the ground floor. This is done via the elevator's method `overrideGoToFloor(Floor::FLOOR_GROUND)` , overriding any requests in the `requests` array.
- The ECS then resets the elevators back into an operational state when the power outage is addressed

```mermaid
sequenceDiagram

  	participant elevator1#colon;Elevator()
  	participant display1#colon;Display()
  	participant elevator2#colon;Elevator()
  	participant display2#colon;Display()
 		participant ecs#colon;ElevatorControlSystem()
  	
  	activate ecs#colon;ElevatorControlSystem()
  	ecs#colon;ElevatorControlSystem()-)ecs#colon;ElevatorControlSystem(): outageSafetySequence()
  	
  	ecs#colon;ElevatorControlSystem()-)elevator1#colon;Elevator(): flagEmergency(EmergencyStatus::OUTAGE)
  	  activate elevator1#colon;Elevator()
  	ecs#colon;ElevatorControlSystem()-)elevator2#colon;Elevator(): flagEmergency(EmergencyStatus::OUTAGE)

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
  	
  	
  	
  	opt Outage is addressed, reset elevators
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

<hr>

### Safety Scenario: Overload

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

<hr>


## GUI Prototype


![GUI](GUI.png)



<hr>



## State Diagrams

### Elevator State Diagram

```mermaid
stateDiagram-v2
    [*] --> IDLE
    

    IDLE --> MOTION
    MOTION --> IDLE
    
```
