FLAGS = -g -std=c++11

all: qt

qt:
	mkdir -p build
	qmake -o build/Makefile elevatorSimulator.pro
	cd build && $(MAKE)

run: qt
	./build/elevatorSimulator.app/Contents/MacOS/elevatorSimulator

clean:
	rm -rf build/*
	rm -rf build

# defs:
# 	g++ $(FLAGS) -c defs.h

# Display:
# 	g++ $(FLAGS) -c Display.h

# Elevator:
# 	g++ $(FLAGS) -c Elevator.h

# ElevatorControlSystem:
# 	g++ $(FLAGS) -c ElevatorControlSystem.h

# clean:
# 	rm -rf Display Elevator ElevatorControlSystem *.o