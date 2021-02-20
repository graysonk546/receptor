
#include "networking.h"
#include <Arduino.h>

static struct pt networkingThread;

receptor_status_t networking_init()
{
    pinMode(LED_BUILTIN, OUTPUT);

    PT_INIT(&networkingThread);
}

struct pt* networking_getThread()
{
    return &networkingThread;
}
