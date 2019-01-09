#include "includes/hardware/StatusIndicator.h"

void StatusIndicator::Initialize()
{
    pinMode(OUTPUT_LED_RED, OUTPUT);
    pinMode(OUTPUT_LED_GREEN, OUTPUT);
    pinMode(OUTPUT_LED_BLUE, OUTPUT);
}
