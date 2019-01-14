#ifndef ENUMS_H
#define ENUMS_H

enum MachineType
{
    MT_WASMACHINE = 0,
    MT_DROOGMACHINE = 1,
    MT_CENTRIFUGE = 2,
    MT_STOOMMACHINE = 3
};

enum MessageCode
{
    M_CONNECT = 0,
    M_MAY_TAKE_WATER = 1,
    M_STOP_TAKE_WATER = 2,
    M_MAY_HEAT_UP = 3,
    M_STOP_HEAT_UP = 4,
    M_PROGRAM_DONE = 5,
    M_PING = 6,
    M_PROGRAM_START = 7
};

enum HardwareState
{
    STATE_ON,
    STATE_OFF
};

enum Temperature
{
    TEMP_OFF,
    TEMP_COLD,
    TEMP_MEDIUM,
    TEMP_HOT
};

enum MotorDirection
{
    MD_LEFT,
    MD_RIGHT
};

enum MotorSpeed
{
    SPEED_OFF,
    SPEED_LOW,
    SPEED_MEDIUM,
    SPEED_HIGH
};

enum WaterLevel
{
    WL_EMPTY,
    WL_25,
    WL_50,
    WL_FULL
};

enum ProgramAction
{
    A_SOAP,
    A_BUZZER,
    A_DRAIN_WATER,
    A_HEAT,
    A_FILL_WATER,
    A_REQUEST_POWER,
    A_REQUEST_WATER,
    A_MOTOR_ROTATE,
    A_DELAY
};

#endif
