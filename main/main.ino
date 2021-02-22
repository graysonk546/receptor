
/*******************************************************************************
*                               Standard Libraries
*******************************************************************************/

/*******************************************************************************
*                               Header Files
*******************************************************************************/

#include "command.h"
#include "networking.h"

/*******************************************************************************
*                               Static Functions
*******************************************************************************/

static char _commandTask(struct pt *thread);
// static char _networkingTask(struct pt *thread);

/*******************************************************************************
*                               Constants
*******************************************************************************/

/*******************************************************************************
*                               Structures
*******************************************************************************/

/*******************************************************************************
*                               Variables
*******************************************************************************/
// Pointers for task threads
static struct pt* pt_command;
static struct pt* pt_networking;

// Flags
static bool flag;

/*******************************************************************************
*                               Setup and Loop
*******************************************************************************/

void setup()
{
    // Initilize flags
    flag = true;

    // Initialize peripherals
    command_init();
    networking_init();

    // Get thread references
    pt_command = command_getThread();
    pt_networking = networking_getThread();
}

void loop()
{
    // Looping achieves thread scheduling
    _commandTask(pt_command);
    _networkingTask(pt_networking);
}

/*******************************************************************************
*                               Implementations
*******************************************************************************/

static PT_THREAD(_commandTask(struct pt *thread))
{
    // Variables to maintain value through context switches
    PT_BEGIN(thread);
    while (true)
    {
        PT_WAIT_UNTIL(thread, Serial.available() > 0);
        if (command_readLine(Serial.read()))
        {
            command_echoCommand(command_getLine());
            Serial.print(COMMAND_PROMPT);
        }
    }
    PT_END(thread);
}

static PT_THREAD(_networkingTask(struct pt *thread))
{
    PT_BEGIN(thread);
    while (true)
    {
        PT_WAIT_UNTIL(thread, flag == false);
    }
    PT_END(thread);
}
