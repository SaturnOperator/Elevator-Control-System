TEMPLATE = app
TARGET = elevatorSimulator
QT += widgets

FONT_PATH = assets/fonts
HEADERS += QCustomIconsFont.h

SOURCES += main.cpp Elevator.cpp
HEADERS +=  defs.h Elevator.h

SOURCES += QElevatorPanel.cpp QUpDownIndicator.cpp QErrorIndicator.cpp QElevatorModel.cpp
HEADERS += QElevatorPanel.h QUpDownIndicator.h QErrorIndicator.h QElevatorModel.h
