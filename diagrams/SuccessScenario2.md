### **Success Scenario 2: ** Passenger *A* on 1st floor requests elevator to floor 4, at the same time Passenger *B* on 2nd floor requests elevator to go to floor 3.

- Note: This scenario builds off *Success Scenario 1*, please read description for that one first to have better understanding of how the system functions. 
- This scenario assumes both Passengers use the same elevator
- When Passenger *A* gets on the elevator and chooses to go to the 4th floor, that is added to the elevator's `requests` array. The ECS will then instruct the elevator to move floor by floor until it reaches the requested floor. `requests = [4]`
- During this time Passenger *B* calls the elevator from the 2nd floor. The ECS adds the second floor to the `requests` so now `requests = [2, 4]`.
- The elevator reaches the second floor so 2 is removed from the `requests` array as that floor request has now been fulfilled. `requests = [4]`
- When passenger three chooses to press the button to the third floor, that is also added to the requests array, so now `requests = [3, 4]`.
- Now the elevator ascends to the 3rd, then fourth floor fulfilling those two floor requests. 

```mermaid
sequenceDiagram

	participant passengerA#colon;Passenger()
	participant passengerB#colon;Passenger()
  	participant elevator1#colon;Elevator()
  	participant display#colon;Display()
  	participant ecs#colon;ElevatorControlSystem()
  
  	%% Passeneger A Requests elevator1#colon;Elevator()
	passengerA#colon;Passenger()-)ecs#colon;ElevatorControlSystem(): callElevator(Floor f, Direction dir)
	activate ecs#colon;ElevatorControlSystem()
	ecs#colon;ElevatorControlSystem()->>ecs#colon;ElevatorControlSystem(): requestFloor(Floor f, Direction dir)	
	ecs#colon;ElevatorControlSystem()-)ecs#colon;ElevatorControlSystem(): updateButtons()
	ecs#colon;ElevatorControlSystem()->>ecs#colon;ElevatorControlSystem(): findElevator()
	ecs#colon;ElevatorControlSystem()-)elevator1#colon;Elevator(): sendElevator(Elevator e, Floor f)
	activate elevator1#colon;Elevator()
	elevator1#colon;Elevator()->>elevator1#colon;Elevator(): addFloorRequest(Floor f)
	deactivate ecs#colon;ElevatorControlSystem()
	
	%% Move to floor f loop
	activate ecs#colon;ElevatorControlSystem()
	deactivate elevator1#colon;Elevator()
	activate elevator1#colon;Elevator()
	loop Move towards requested Floor f
		ecs#colon;ElevatorControlSystem()->>elevator1#colon;Elevator(): pollRequests()
		deactivate ecs#colon;ElevatorControlSystem()
    elevator1#colon;Elevator()->>elevator1#colon;Elevator(): fulfillRequest()
    elevator1#colon;Elevator()->>display#colon;Display(): updatedisplay#colon;Display()(Floor f)

    activate display#colon;Display()
    display#colon;Display()->>display#colon;Display(): updateFloor(Floor f)
    display#colon;Display()->>-display#colon;Display(): ringBell()
    elevator1#colon;Elevator()-->>ecs#colon;ElevatorControlSystem(): pollRequests()
    activate ecs#colon;ElevatorControlSystem()
	end
	elevator1#colon;Elevator()->>elevator1#colon;Elevator(): openDoors()
	deactivate elevator1#colon;Elevator()
	
	ecs#colon;ElevatorControlSystem()-)ecs#colon;ElevatorControlSystem(): updateButtons()
	deactivate ecs#colon;ElevatorControlSystem()
	
	%% Passenger A enters when elevator arrives on first floor
	passengerA#colon;Passenger()->>elevator1#colon;Elevator(): enterElevator(Elevator e)
	activate elevator1#colon;Elevator()
	opt Door Open Button Pressed
		elevator1#colon;Elevator()->>elevator1#colon;Elevator(): openDoors()
	end
	elevator1#colon;Elevator()->>elevator1#colon;Elevator(): closeDoors()
	deactivate elevator1#colon;Elevator()
	
	
	%% Passenger A requests floor
	passengerA#colon;Passenger()-)elevator1#colon;Elevator(): pressFloorButton(Floor f)
	activate elevator1#colon;Elevator()
	elevator1#colon;Elevator()->>elevator1#colon;Elevator(): addFloorRequest(Floor f)
	elevator1#colon;Elevator()-->>ecs#colon;ElevatorControlSystem(): pollRequest()
	
	activate ecs#colon;ElevatorControlSystem()
	ecs#colon;ElevatorControlSystem()-)ecs#colon;ElevatorControlSystem(): updateButtons()
	deactivate ecs#colon;ElevatorControlSystem()
	
	
	%% Passeneger B Requests elevator1#colon;Elevator()
	passengerB#colon;Passenger()-)ecs#colon;ElevatorControlSystem(): callElevator(Floor f, Direction dir)

	activate ecs#colon;ElevatorControlSystem()
	ecs#colon;ElevatorControlSystem()->>ecs#colon;ElevatorControlSystem(): requestFloor(Floor f, Direction dir)	
	ecs#colon;ElevatorControlSystem()-)ecs#colon;ElevatorControlSystem(): updateButtons()
	ecs#colon;ElevatorControlSystem()->>ecs#colon;ElevatorControlSystem(): findElevator()
	ecs#colon;ElevatorControlSystem()-)elevator1#colon;Elevator(): sendElevator(Elevator e, Floor f)

	elevator1#colon;Elevator()->>elevator1#colon;Elevator(): addFloorRequest(Floor f)
	deactivate ecs#colon;ElevatorControlSystem()
	


	%% Move to floor f loop
	activate ecs#colon;ElevatorControlSystem()
	deactivate elevator1#colon;Elevator()
	activate elevator1#colon;Elevator()
	loop Move towards requested Floor f
		ecs#colon;ElevatorControlSystem()->>elevator1#colon;Elevator(): pollRequests()
		deactivate ecs#colon;ElevatorControlSystem()
    elevator1#colon;Elevator()->>elevator1#colon;Elevator(): fulfillRequest()
    elevator1#colon;Elevator()->>display#colon;Display(): updatedisplay#colon;Display()(Floor f)

    activate display#colon;Display()
    display#colon;Display()->>display#colon;Display(): updateFloor(Floor f)
    display#colon;Display()->>-display#colon;Display(): ringBell()
    elevator1#colon;Elevator()-->>ecs#colon;ElevatorControlSystem(): pollRequests()
    activate ecs#colon;ElevatorControlSystem()
	end
	elevator1#colon;Elevator()->>elevator1#colon;Elevator(): openDoors()
	
	deactivate elevator1#colon;Elevator()
	
	ecs#colon;ElevatorControlSystem()-)ecs#colon;ElevatorControlSystem(): updateButtons()
	deactivate ecs#colon;ElevatorControlSystem()
	
	
	
	
	%% Passenger B enters
	passengerB#colon;Passenger()->>elevator1#colon;Elevator(): enterElevator(Elevator e)
	activate elevator1#colon;Elevator()
	opt Door Open Button Pressed
		elevator1#colon;Elevator()->>elevator1#colon;Elevator(): openDoors()
	end
	elevator1#colon;Elevator()->>elevator1#colon;Elevator(): closeDoors()
	deactivate elevator1#colon;Elevator()
	
	%% Passenger B requests floor
	passengerB#colon;Passenger()-)elevator1#colon;Elevator(): pressFloorButton(Floor f)
	activate elevator1#colon;Elevator()
	elevator1#colon;Elevator()->>elevator1#colon;Elevator(): addFloorRequest(Floor f)
	elevator1#colon;Elevator()-->>ecs#colon;ElevatorControlSystem(): pollRequest()
	
	activate ecs#colon;ElevatorControlSystem()
	ecs#colon;ElevatorControlSystem()-)ecs#colon;ElevatorControlSystem(): updateButtons()
	deactivate ecs#colon;ElevatorControlSystem()
	
	
	
	
	
	%% Move to floor f loop
	activate ecs#colon;ElevatorControlSystem()
	deactivate elevator1#colon;Elevator()
	activate elevator1#colon;Elevator()
	loop Move towards requested Floor f
		ecs#colon;ElevatorControlSystem()->>elevator1#colon;Elevator(): pollRequests()
		deactivate ecs#colon;ElevatorControlSystem()
    elevator1#colon;Elevator()->>elevator1#colon;Elevator(): fulfillRequest()
    elevator1#colon;Elevator()->>display#colon;Display(): updatedisplay#colon;Display()(Floor f)

    activate display#colon;Display()
    display#colon;Display()->>display#colon;Display(): updateFloor(Floor f)
    display#colon;Display()->>-display#colon;Display(): ringBell()
    elevator1#colon;Elevator()-->>ecs#colon;ElevatorControlSystem(): pollRequests()
    activate ecs#colon;ElevatorControlSystem()
	end
	elevator1#colon;Elevator()->>elevator1#colon;Elevator(): openDoors()
	
	deactivate elevator1#colon;Elevator()
	
	ecs#colon;ElevatorControlSystem()-)ecs#colon;ElevatorControlSystem(): updateButtons()
	deactivate ecs#colon;ElevatorControlSystem()
	
	
	passengerB#colon;Passenger()->>elevator1#colon;Elevator(): exitElevator()
	activate elevator1#colon;Elevator()
	elevator1#colon;Elevator()->>elevator1#colon;Elevator(): closeDoors()
	deactivate elevator1#colon;Elevator()
	
	
		%% Move to floor f loop
	activate ecs#colon;ElevatorControlSystem()
	activate elevator1#colon;Elevator()
	loop Move towards requested Floor f
		ecs#colon;ElevatorControlSystem()->>elevator1#colon;Elevator(): pollRequests()
		deactivate ecs#colon;ElevatorControlSystem()
    elevator1#colon;Elevator()->>elevator1#colon;Elevator(): fulfillRequest()
    elevator1#colon;Elevator()->>display#colon;Display(): updatedisplay#colon;Display()(Floor f)

    activate display#colon;Display()
    display#colon;Display()->>display#colon;Display(): updateFloor(Floor f)
    display#colon;Display()->>-display#colon;Display(): ringBell()
    elevator1#colon;Elevator()-->>ecs#colon;ElevatorControlSystem(): pollRequests()
    activate ecs#colon;ElevatorControlSystem()
	end
	elevator1#colon;Elevator()->>elevator1#colon;Elevator(): openDoors()
	
	deactivate elevator1#colon;Elevator()
	
	ecs#colon;ElevatorControlSystem()-)ecs#colon;ElevatorControlSystem(): updateButtons()
	deactivate ecs#colon;ElevatorControlSystem()
	
	passengerA#colon;Passenger()->>elevator1#colon;Elevator(): exitElevator()
	activate elevator1#colon;Elevator()
	elevator1#colon;Elevator()->>elevator1#colon;Elevator(): closeDoors()
	deactivate elevator1#colon;Elevator()
	
```







