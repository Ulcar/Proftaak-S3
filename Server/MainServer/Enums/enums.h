#ifndef ENUMS_H
#define ENUMS_H

enum Type
{
    ControlPanel = -1,
    Wasmachine,
    Stomer,
    Centrifuge,
    Droogmachine
};

enum Temperature
{
    Cold,
    Medium,
    Hot
};

enum Color
{
    Red, 
    Blue, 
    White
};

enum Program
{
    PROGRAM_NONE = 0,
    PROGRAM_XX,
    PROGRAM_YY
};
//No enums

#endif