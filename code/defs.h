#ifndef DEFS_H
#define DEFS_H

#define NUM_ELEVATORS  5
#define NUM_FLOORS 4

#define MAX_LOAD 5000

#define ELVATOR_MOVE_DELAY 1000

enum class Direction {
    NONE  = 0x0,
    DOWN  = 0x1,
    UP    = 0x2
};

enum class DoorStatus {
    CLOSE, OPEN
};

enum class ElevatorStatus {
    IDLE    = 0x0, 
    MOTION  = 0x1, 
    ERROR   = 0x2
};

// Bit flags as elevator can have multiple concurrent errors  
enum class EmergencyStatus {
    NONE         = 0x0,
    OBSTRUCTION  = 0x1,
    OVERLOAD     = 0x2,
    HELP         = 0x4,
    OUTAGE       = 0x8,
    FIRE         = 0x10,
};

enum class Floor {
    FLOOR_NONE, FLOOR_GROUND, FLOOR_2, FLOOR_3, FLOOR_4
};

#endif