#ifndef IALGORITHM_H
#define IALGORITHM_H

#include <string>

class iAlgorithm
{
public:
    virtual ~iAlgorithm() {};

    virtual void Beat() = 0;

    //virtual void TurnLeft() = 0;
};

#endif
