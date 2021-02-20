
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
static char _networkingTask(struct pt *thread);

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
    _networkingTask(pt_networking);
    _commandTask(pt_command);
}

/*******************************************************************************
*                               Implementations
*******************************************************************************/

static PT_THREAD(_commandTask(struct pt *thread))
{
    // Variables to maintain value through context switches
    static char byte = "";

    PT_BEGIN(thread);
    while (true)
    {
        PT_WAIT_UNTIL(thread, Serial.available() > 0);
        flag = true;
        byte = (char) Serial.read();
        Serial.print(byte);
        flag = false;
    }
    PT_END(thread);
}

static PT_THREAD(_networkingTask(struct pt *thread))
{
    PT_BEGIN(thread);
    while (true)
    {
        PT_WAIT_WHILE(thread, flag);
        flag = true;
        digitalWrite(LED_BUILTIN, HIGH);
    }
    PT_END(thread);
}
