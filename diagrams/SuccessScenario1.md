### **Success Scenario 1: ** Passenger requests elevator and rides it to floor *f* 

- Passenger calls the elevator from an arbitrary floor *f*, the ECS will find the nearest available elevator `findElevator()` and add floor *f* to that elevator's requests array `vector<Floor> requests`. The ECS will instruct the elevator to move through `pollRequests()`, continuously calling this method until the request is complete. Each time this method is called the elevator will move one floor. A request is completed when the elevator arrives at the floor of the request, at this point the doors will opens. Note that `pollRequests()` will return False until all requests are completed, `pollRequests()` triggers the elevator's `fulfillRequest()` method which causes the elevator to move towards the floors in `requests` array. 
- When the elevator reaches the floor of which the button was pressed from, the passenger enters and the door closes after 10 seconds. At this point in time the elevator and ECS are idle until further action is done.
- When the passenger presses a floor button to go to a different (or same) arbitrary floor *f*, that floor is added to the `requests` array, the ECS instructs the elevator to start moving with `pollRequests()` again until the elevator reaches the requested floor.
- This design allows for a robust system that encompasses different scenarios as well without altering the flow of the system. For example an edge case would what if a passenger calls the elevator and the elevator is already on that floor? Or alternatively the passenger enters on floor 1, the door closes and passenger presses floor 1? In this system, the floor is added to the `request` array as normal, the ECS will try fulfill that request. When the elevator sees its already at the destination floor then the request is deemed complete, at which the doors will then open.

```mermaid
sequenceDiagram

	participant passenger1#colon;Passenger()
  	participant elevator1#colon;Elevator()
  	participant display#colon;Display()
 	participant ecs#colon;ElevatorControlSystem()
  
  
	passenger1#colon;Passenger()-)ecs#colon;ElevatorControlSystem(): callElevator(Floor f, Direction dir)
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
	
	
	passenger1#colon;Passenger()->>elevator1#colon;Elevator(): enterElevator(Elevator e)
	activate elevator1#colon;Elevator()
	opt Door Open Button Pressed
		elevator1#colon;Elevator()->>elevator1#colon;Elevator(): openDoors()
	end
	elevator1#colon;Elevator()->>elevator1#colon;Elevator(): closeDoors()
	deactivate elevator1#colon;Elevator()
	
	
	passenger1#colon;Passenger()-)elevator1#colon;Elevator(): pressFloorButton(Floor f)
	activate elevator1#colon;Elevator()
	elevator1#colon;Elevator()->>elevator1#colon;Elevator(): addFloorRequest(Floor f)
	elevator1#colon;Elevator()-->>ecs#colon;ElevatorControlSystem(): pollRequests()
	
	


	%% Move to floor f loop
	activate ecs#colon;ElevatorControlSystem()
	ecs#colon;ElevatorControlSystem()-)ecs#colon;ElevatorControlSystem(): updateButtons()
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
	
	passenger1#colon;Passenger()->>elevator1#colon;Elevator(): exitElevator()
	activate elevator1#colon;Elevator()
	elevator1#colon;Elevator()->>elevator1#colon;Elevator(): closeDoors()
	deactivate elevator1#colon;Elevator()
	
```







