#include "EXTports.h"
#include "stdio.h"
#include "stdlib.h"
#include "main.h"
#include "string.h"
#include "globals.h"
#include "multiplexers.h"
#include "shiftRegisters.h"

Multiplexer OPT_INPUTS_MUX = {
.A0_pin = OPTO_MUX_A0_Pin,
.A1_pin = OPTO_MUX_A1_Pin,
.A2_pin = OPTO_MUX_A2_Pin,
.data_out_pins = {OPTO_MUX_D_Pin},
.mux_length = 8,
.number_of_paralel_muxes = 1,
.noe_pin = OPTO_MUX_EN_Pin,
.A0_port = OPTO_MUX_A0_GPIO_Port,
.A1_port = OPTO_MUX_A1_GPIO_Port,
.A2_port = OPTO_MUX_A2_GPIO_Port,
.data_out_ports = {OPTO_MUX_D_GPIO_Port},
.noe_port = OPTO_MUX_EN_GPIO_Port,
.current_satus = 0,
.endianity = REGISTER_ENDIANITY_1_PIN_IS_MSB,
};


static uint8_t checkNumberOfSubcommands(uint8_t expected_number, uint8_t current_subcommand_index ,commandTemplate* current_command){
    //Function that check if the command has the correct number of subcommands
    if (current_command->number_of_subcommands-current_subcommand_index-1 != expected_number){
        sprintf(current_command->response,"ERROR;Wrong number of arguments after command: %s \
(Expected %d, got %d)\n",current_command->subcommands[current_subcommand_index] ,expected_number,current_command->number_of_subcommands-current_subcommand_index-1);
        return 0;
        }
    return 1;
}

static void readCommands(commandTemplate* current_command){

    if (current_command->number_of_subcommands == 1){
        sprintf(current_command->response, "ERROR;Subcommand is missing, received: %s %s\n", current_command->command, current_command->subcommands[0]);	
    return;
    }

    if(strcmp(current_command->subcommands[1],"MUX") == 0){
        if (checkNumberOfSubcommands(0,1,current_command) == 0) return;
            MUXreadAll(&OPT_INPUTS_MUX);
            sprintf(current_command->response,"OK;OPT_INPUTX_MUX:register Value:%d\n",(uint8_t)OPT_INPUTS_MUX.current_satus);
            //sprintf(current_command->response,"OK;Reading Register %s, value:%s\n",current_command->subcommands[2],uint64ToDecimal(IO1TO40_OUTPUTS.current_satus));
    }//muxValue

    else if(strcmp(current_command->subcommands[1],"PIN") == 0){
        if (checkNumberOfSubcommands(1,1,current_command) == 0) return;
        static uint8_t pin_number;
        pin_number = 7 - atoi(current_command->subcommands[2]);
        sprintf(current_command->response,"OK;Reading Optical Input %d, value:%d\n",pin_number,MUXreadAdress(pin_number,&OPT_INPUTS_MUX));
    }// PINNUMBER
}

void OptInputsParser(commandTemplate* current_command){
    //"""Implementation of commands"""
    if (current_command->number_of_subcommands == 0){
        sprintf(current_command->response, "ERROR; Subcommand is missing, received: %s\n", current_command->command);	
        return;
    }
 
    if (strcmp(current_command->subcommands[0],"SET") == 0){
        sprintf(current_command->response, "ERROR; SET command is not supported %s\n", current_command->subcommands[0]);
    }

    else if (strcmp(current_command->subcommands[0],"READ") == 0){
        readCommands(current_command);
    }

    else if (strcmp(current_command->subcommands[0],"MEASURE") == 0){
        sprintf(current_command->response, "ERROR; Measure command is not supported %s\n", current_command->subcommands[0]);
    }

    else{
        sprintf(current_command->response, "ERROR; Unknown command: %s\n", current_command->subcommands[0]);
    }
    

}