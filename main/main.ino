
#include "command.h"
#include <LibPrintf.h>
#include <HardwareSerial.h>

void setup()
{
    Serial.begin(9600);
}

void loop()
{
    int value = function();
    printf("prompt>\r\n");
}
