
/*******************************************************************************
*                               Standard Libraries
*******************************************************************************/

#include <pt.h>
#include <Arduino.h>
#include <HardwareSerial.h>

/*******************************************************************************
*                               Header Files
*******************************************************************************/

#include "command.h"

/*******************************************************************************
*                               Static Functions
*******************************************************************************/

// static void _commandTask(struct pt *thread);
static int _commandTask(struct pt *thread);

/*******************************************************************************
*                               Constants
*******************************************************************************/

#define SERIAL_TIMEOUT_MS 5000

/*******************************************************************************
*                               Structures
*******************************************************************************/

/*******************************************************************************
*                               Variables
*******************************************************************************/

static struct pt commandThread;

/*******************************************************************************
*                               Functions
*******************************************************************************/

receptor_status_t command_init()
{
    // Initialize pt structure
    PT_INIT(&commandThread);

    // Begin the serial connection
    Serial.begin(9600);
    long time;
    while(!Serial)
    {
        if (millis() > SERIAL_TIMEOUT_MS)
        {
            return RECEPTOR_ERR;
        }
    }
    Serial.println("Initialized serial port!");

    // Start thread for handling CLI
    _commandTask(&commandThread);
}

command_status_t command_help(uint8_t argNumber, char* args[])
{
    Serial.println("Command successful!");
    return COMMAND_OK;
}

static int _commandTask(struct pt *thread)
{
    // Variablles to maintain value through context switches
    static char byte = "\0";

    PT_BEGIN(thread);
    while (true)
    {
        // if (Serial.available() > 0)
        // {
        //     byte = (char) Serial.read();
        //     Serial.println(byte);
        // }
        PT_WAIT_UNTIL(thread, Serial.available() > 0);
        byte = (char) Serial.read();
        Serial.print(byte);
    }
    PT_END(thread)
}
