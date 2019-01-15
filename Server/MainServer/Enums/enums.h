#ifndef ENUMS_H
#define ENUMS_H

enum Type
{
    ControlPanel = -1,
    WashingMachine,
    Dryer,
    Centrifuge,
};

enum Temperature
{
    Cold,
    Medium,
    Hot
};

enum Color
{
    Light,
    Dark, 
    Colored
};

enum Program
{
    PROGRAM_NONE = -1,
    PROGRAM_COLD,
    PROGRAM_WARM,
    PROGRAM_HOT
};
//No enums

#endif