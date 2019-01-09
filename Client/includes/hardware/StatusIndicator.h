#ifndef STATUSINDICATOR_H
#define STATUSINDICATOR_H

#include "interface/IStatusIndicator.h"

#define OUTPUT_LED_RED   (44)
#define OUTPUT_LED_GREEN (45)
#define OUTPUT_LED_BLUE  (46)

class StatusIndicator : public IStatusIndicator
{
public:
    void Initialize();
};

#endif
