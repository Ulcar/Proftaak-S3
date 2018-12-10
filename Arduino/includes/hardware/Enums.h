#ifndef ENUMS_H
#define ENUMS_H

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
