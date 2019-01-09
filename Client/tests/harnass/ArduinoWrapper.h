#ifndef ARDUINOWRAPPER_H
#define ARDUINOWRAPPER_H

#include <sys/timeb.h>

#define OUTPUT (0x1)
#define INPUT  (0x0)

#define HIGH   (0x1)
#define LOW    (0x0)

#include "String.h"

// Credit: https://stackoverflow.com/a/11437456
unsigned long millis();
void delay(unsigned long ms);

void pinMode(int pin, int mode);

#endif
