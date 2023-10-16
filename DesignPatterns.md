## Design Patterns Used

Throughout the design of the Elevator controller simulator's a couple  different design patterns were used to make the design more robust and organized.

The `ElevatorControlSystem` (ECS) is implemented as a Singleton Pattern, there is exactly one instance of the ECS class. This allows for a single point of control for all the elevators.

The way the elevators are controlled follows an Observer Pattern and a Command Pattern design. The ECS observes all the states of the different elevators, sensors, buttons etc and then commands each entity on the next instruction.