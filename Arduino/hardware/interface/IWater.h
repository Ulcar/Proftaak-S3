#ifndef IWATER_H
#define IWATER_H

class IWater
{
public:
    virtual int GetLevel() = 0;
    virtual bool GetPressure() = 0;
};

#endif
