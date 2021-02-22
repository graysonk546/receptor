
#ifndef COMMAND
#define COMMAND

/*******************************************************************************
*                               Standard Includes
*******************************************************************************/

#include <pt.h>

/*******************************************************************************
*                               Header File Includes
*******************************************************************************/

#include "/home/graysonk546/Arduino/prototyping/receptor/receptor/utilities/util-vars.h"

/*******************************************************************************
*                               Static Functions
*******************************************************************************/

/*******************************************************************************
*                               Constants
*******************************************************************************/

#define COMMAND_PROMPT       "receptor> "
#define COMMAND_EOL          '\n'
#define STRING_EOL           '\0'
#define COMMAND_JSON         "JSON: "
#define COMMAND_BUFF_MAX_LEN 100

/*******************************************************************************
*                               Structures
*******************************************************************************/
typedef enum {
    COMMAND_OK,
    COMMAND_ERROR
} command_status_t;

typedef command_status_t (*command_func_t)(uint8_t argNumber, char* args[]);

typedef struct {
    command_func_t function;
    char *command;
    char *parameters;
    char *description;
    uint8_t minParam;
    uint8_t maxParam;
} command_t;

typedef struct {
    char line[COMMAND_BUFF_MAX_LEN];
    uint8_t index;
} command_line_t;

/*******************************************************************************
*                               Variables
*******************************************************************************/

/*******************************************************************************
*                               Function Declarations
*******************************************************************************/

command_status_t command_help(uint8_t argNumber, char* args[]);

receptor_status_t command_init();

bool command_readLine(char *byte);

char* command_parseCommand(char *line);

void command_echoCommand(command_line_t *command);

command_status_t command_processCommand();

struct pt* command_getThread();

command_line_t* command_getLine();

#define COMMAND_COMMANDS                                                       \
    {command_help, "help", "", "lists all supported commands", 0, 0},          \

#endif // COMMAND
