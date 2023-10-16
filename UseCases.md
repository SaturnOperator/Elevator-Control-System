### **Part 3: Elevator Control System**

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

