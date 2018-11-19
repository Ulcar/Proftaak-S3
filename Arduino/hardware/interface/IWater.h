#ifndef IWATER_H
#define IWATER_H

enum WaterLevel
{
    WL_EMPTY,
    WL_33,
    WL_66,
    WL_FULL
};

class IWater
{
public:
    virtual WaterLevel GetLevel() = 0;
    virtual bool GetPressure() = 0;
};

#endif
