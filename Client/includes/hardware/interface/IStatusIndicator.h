#ifndef ISTATUSINDICATOR_H
#define ISTATUSINDICATOR_H

class IStatusIndicator
{
public:
    virtual ~IStatusIndicator() { }

    virtual void Initialize() = 0;
};

#endif
