#ifndef STATUSINDICATOR_H
#define STATUSINDICATOR_H

#include "interface/IStatusIndicator.h"

#define BLINKING_DELAY   (500)

#define OUTPUT_LED_RED   (44)
#define OUTPUT_LED_GREEN (45)
#define OUTPUT_LED_BLUE  (46)

class StatusIndicator : public IStatusIndicator
{
public:
    void Initialize();
    void Update();
    void SetStatus(Status status);

private:
    unsigned long _startMs;
    HardwareState _lightState;

    void SetColor(int red, int green, int blue);
};

#endif
