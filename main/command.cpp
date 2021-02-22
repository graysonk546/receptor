
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
#include "/home/graysonk546/Arduino/prototyping/receptor/receptor/main/cli-commands/receptor-commands.h"

/*******************************************************************************
*                               Static Functions
*******************************************************************************/

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
static command_line_t commandLine = {
    commandLine.index = 0
};

/*******************************************************************************
*                               Implementations
*******************************************************************************/

receptor_status_t command_init()
{
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

    // Initialize pt structure
    PT_INIT(&commandThread);
}

bool command_readLine(char *byte)
{
    if (byte == '\n')
    {
        commandLine.line[commandLine.index] = '\0';
        commandLine.index = 0;
        return true;
    }
    else
    {
        commandLine.line[commandLine.index++] = byte;
        return false;
    }
}

char* command_parseCommand(char *line)
{
    // Change this to parse the command
    return line;
}

void command_echoCommand(command_line_t *command)
{
    uint8_t i = 0;
    while (command->line[i] != '\0')
    {
        Serial.print(command->line[i]);
        i++;
    }
    Serial.print(COMMAND_EOL);
}

command_status_t command_processCommand()
{
    return COMMAND_OK;
}

struct pt* command_getThread()
{
    return &commandThread;
}

command_line_t* command_getLine()
{
    return &commandLine;
}

command_status_t command_help(uint8_t argNumber, char* args[])
{
    Serial.println(commandArr[0].command);
    return COMMAND_OK;
}
