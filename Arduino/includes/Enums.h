#ifndef ENUMS_H
#define ENUMS_H

enum MachineType
{
    MT_WASMACHINE = 0,
    MT_DROOGMACHINE = 1,
    MT_CENTRIFUGE = 2,
    MT_STOOMMACHINE = 3
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

#endif
