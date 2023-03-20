#ifndef COMMAND_PARSER_H
#define COMMAND_PARSER_H

#include "stdio.h"
#define MAXIMUM_SUBCOMMAND_LENGTH 64
#define MAXIMUM_NUMBER_OF_SUBCOMMANDS 20
#define MAXIMUM_RESPONSE_LENGTH 256
#define DELIMETER " "
typedef struct
{
	char* command;
	uint8_t number_of_subcommands;
	char subcommands[MAXIMUM_NUMBER_OF_SUBCOMMANDS][MAXIMUM_SUBCOMMAND_LENGTH];
	char* delimeter;
    char response[MAXIMUM_RESPONSE_LENGTH];
}commandTemplate;

uint8_t updateCommandStruct(char* command_str, commandTemplate* current_command);
uint8_t runCommand(commandTemplate* current_command);
#endif