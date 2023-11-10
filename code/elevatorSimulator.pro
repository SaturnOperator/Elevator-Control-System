TEMPLATE = app
TARGET = elevatorSimulator
QT += widgets

FONT_PATH = assets/fonts
HEADERS += QCustomIconsFont.h

SOURCES += main.cpp Elevator.cpp ElevatorControlSystem.cpp
HEADERS +=  defs.h Elevator.h ElevatorControlSystem.h

SOURCES += QElevatorButton.cpp QElevatorPanel.cpp QUpDownIndicator.cpp QErrorIndicator.cpp QElevatorModel.cpp
HEADERS += QElevatorButton.h QElevatorPanel.h QUpDownIndicator.h QErrorIndicator.h QElevatorModel.h
