#include "commandParser.h"
#include "string.h"
#include "shiftRegisters.h"
#include "stdio.h"
#include "stdlib.h"
#include "multiplexers.h"
#include "globals.h"
#include "main.h"
#include "module80IOcard.h"



uint8_t runCommand(commandTemplate* current_command){
    //"""Implementation of commands"""
    if (current_command->command == NULL){
        strcpy(current_command->response,"ERROR:No command received\n");
        return 0;
    };

    if (strcmp(current_command->command,"HELP") == 0){
        sprintf(current_command->response,"OK:Help command received\n");
    }

    else if (strcmp(current_command->command,"*IDN?") == 0){
        sprintf(current_command->response,"OK:STM32 super board\n");
    }

    else if (strcmp(current_command->command,"80_IO_CARD") == 0){
        module80CardParser(current_command);

    }

    else{
        sprintf(current_command->response,"ERROR:No such command\n");
        return 0;
    }
    return 1;
}


uint8_t updateCommandStruct(char* command_str, commandTemplate* current_command){
	//takes command, splits it into subcommands and saves them into list_of_commands -> returns list_length
	current_command->number_of_subcommands = 0;
	char* token;
	char* saveptr[64];
	current_command->delimeter = DELIMETER;
	token = strtok_r(command_str, current_command->delimeter, saveptr);
	current_command->command = token;
	uint8_t i = 0;
	while (token != NULL){
		i++;
		token = strtok_r(NULL, current_command->delimeter, saveptr);
		strcpy(current_command->subcommands[i-1],token);
		
	}
	current_command->number_of_subcommands = i-1;
	return 1;
} 