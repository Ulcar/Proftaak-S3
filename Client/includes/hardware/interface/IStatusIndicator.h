#ifndef ISTATUSINDICATOR_H
#define ISTATUSINDICATOR_H

#include "../../Enums.h"

class IStatusIndicator
{
public:
    virtual ~IStatusIndicator() { };

    virtual void Initialize() = 0;
    virtual void SetStatus(Status status) = 0;
    virtual void Update() = 0;

protected:
    Status _status;
};

#endif
