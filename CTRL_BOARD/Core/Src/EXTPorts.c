#include "EXTports.h"
#include "stdio.h"
#include "stdlib.h"
#include "main.h"
#include "string.h"
#include "globals.h"
#include "shiftRegisters.h"
#include "multiplexers.h"
#include "relayCards.h"

ShifRegister EXT_REG = {
.ser_pin = PORTS_SER_Pin,
.srclk_pin = PORTS_SRCLK_Pin,
.rclk_pin = PORTS_RCLK_Pin,
.srclr_pin = PORTS_SRCLR_Pin,
.noe_pin = PORTS_OE_Pin,
.ser_port = PORTS_SER_GPIO_Port,
.srclk_port = PORTS_SRCLK_GPIO_Port,
.rclk_port = PORTS_RCLK_GPIO_Port,
.srclr_port = PORTS_SRCLR_GPIO_Port,
.noe_port = PORTS_OE_GPIO_Port,
.current_satus = 0,
.shift_reg_length = 24,
.endianity = REGISTER_ENDIANITY_1_PIN_IS_LSB,
};


RelayCards RELAY32_EXT3 = {
    .SN74238_A_EXT_PORT_pin_number = 1,
    .SN74238_B_EXT_PORT_pin_number = 2,
    .SN74238_C_EXT_PORT_pin_number = 3,
    .SN74238_E3_EXT_PORT_pin_number = 4,
    .SN74AC175D_D1_EXT_PORT_pin_number = 5,
    .SN74AC175D_D2_EXT_PORT_pin_number = 6,
    .SN74AC175D_D3_EXT_PORT_pin_number = 7,
    .SN74AC175D_D4_EXT_PORT_pin_number = 8,
    .number_of_relays = 32,
    .ext_port_number = 3,
    .current_satus = 0,
    .shift_register = &EXT_REG,
};

RelayCards RELAY32_EXT2 = {
    .SN74238_A_EXT_PORT_pin_number = 1,
    .SN74238_B_EXT_PORT_pin_number = 2,
    .SN74238_C_EXT_PORT_pin_number = 3,
    .SN74238_E3_EXT_PORT_pin_number = 4,
    .SN74AC175D_D1_EXT_PORT_pin_number = 5,
    .SN74AC175D_D2_EXT_PORT_pin_number = 6,
    .SN74AC175D_D3_EXT_PORT_pin_number = 7,
    .SN74AC175D_D4_EXT_PORT_pin_number = 8,
    .number_of_relays = 32,
    .ext_port_number = 2,
    .current_satus = 0,
    .shift_register = &EXT_REG,
};

RelayCards RELAY32_EXT1 = {
    .SN74238_A_EXT_PORT_pin_number = 1,
    .SN74238_B_EXT_PORT_pin_number = 2,
    .SN74238_C_EXT_PORT_pin_number = 3,
    .SN74238_E3_EXT_PORT_pin_number = 4,
    .SN74AC175D_D1_EXT_PORT_pin_number = 5,
    .SN74AC175D_D2_EXT_PORT_pin_number = 6,
    .SN74AC175D_D3_EXT_PORT_pin_number = 7,
    .SN74AC175D_D4_EXT_PORT_pin_number = 8,
    .number_of_relays = 32,
    .ext_port_number = 1,
    .current_satus = 0,
    .shift_register = &EXT_REG,
};

static char bfr[20+1];
static char* uint64ToDecimal(uint64_t v) {
  char* p = bfr + sizeof(bfr);
  *(--p) = '\0';
  for (uint8_t first = 1; v || first; first = 0) {
    const uint32_t digit = v % 10;
    const char c = '0' + digit;
    *(--p) = c;
    v = v / 10;
  }
  return p;
}

static uint8_t checkNumberOfSubcommands(uint8_t expected_number, uint8_t current_subcommand_index ,commandTemplate* current_command){
    //Function that check if the command has the correct number of subcommands
    if (current_command->number_of_subcommands-current_subcommand_index-1 != expected_number){
        sprintf(current_command->response,"ERROR;Wrong number of arguments after command: %s \
(Expected %d, got %d)\n",current_command->subcommands[current_subcommand_index] ,expected_number,current_command->number_of_subcommands-current_subcommand_index-1);
        return 0;
        }
    return 1;
}

static void setCommands(commandTemplate* current_command){
    //Function that handle SET Type commands
    if (current_command->number_of_subcommands == 1){
    sprintf(current_command->response, "ERROR;Subcommand is missing, received: %s %s\n", current_command->command, current_command->subcommands[0]);	
    return;
    }

    // -------------------------- RELAY CARDS -----------------------------
    
    if(strcmp(current_command->subcommands[1],"RELAY") == 0){
        static RelayCards* relay_card_ptr;
        if(strcmp(current_command->subcommands[2],"EXT1_32_RELAY") == 0){
            relay_card_ptr = &RELAY32_EXT1;
        }

        else if(strcmp(current_command->subcommands[2],"EXT2_32_RELAY") == 0){
            relay_card_ptr = &RELAY32_EXT2;
        }

        else if(strcmp(current_command->subcommands[2],"EXT3_32_RELAY") == 0){
            relay_card_ptr = &RELAY32_EXT3;
        }

        else{
            sprintf(current_command->response,"ERROR;Unknown Relay Card %s\n",current_command->subcommands[1]);
            return;
        }

        // --------------------- Whole port or single relay ? ---------------------
        if(strcmp(current_command->subcommands[3],"VALUE") == 0){
            //relayCardSetAllRelays(strtoull(current_command->subcommands[4],NULL,10),relay_card_ptr);
            loadDataToShiftReg(strtoull(current_command->subcommands[4],NULL,10),relay_card_ptr->shift_register);
            sprintf(current_command->response,"OK;Setting all relays to:%s\n",uint64ToDecimal(relay_card_ptr->current_satus));
        }

        else{
            relayCardSetSingleRelay(atoi(current_command->subcommands[3]),atoi(current_command->subcommands[4]),relay_card_ptr);
            sprintf(current_command->response,"OK;Setting Relay:%s to:%s\n",current_command->subcommands[3],current_command->subcommands[4]);
        }

        
    }



    // -------------------------- REGISTER AS EXT PORT -----------------------------
    else if(strcmp(current_command->subcommands[1],"SHIFT_REGISTER") == 0){
        if (checkNumberOfSubcommands(3,1,current_command) == 0) return;
        static ShifRegister* register_ptr;

        //SELECT REGISTER
        if (strcmp(current_command->subcommands[2],"EXT") == 0){
            register_ptr = &EXT_REG;
        }
        else{
            sprintf(current_command->response,"ERROR;Unknown Register %s\n",current_command->subcommands[2]);
            return;
        }
        //UPDATE REGISTER
        if (strcmp(current_command->subcommands[3],"VALUE") == 0)
        {
            uint64_t data = strtoull(current_command->subcommands[4],NULL,10);
            loadDataToShiftReg(data,register_ptr);
            sprintf(current_command->response,"OK;Setting Register:%s to:%s\n",current_command->subcommands[2],uint64ToDecimal(data));
        }

        else if(strcmp(current_command->subcommands[3],"DO_N_SHIFTS") == 0)
        {
            shiftRegNtimesShift((uint8_t)atoi(current_command->subcommands[4]),register_ptr);
            sprintf(current_command->response,"OK;Register: %s number of shifts:%d\n",current_command->subcommands[2],(uint8_t)atoi(current_command->subcommands[4]));
        }

        else
        {
            shiftRegSetSinglePin((uint8_t)atoi(current_command->subcommands[3]),(uint8_t)atoi(current_command->subcommands[4]),register_ptr);
            sprintf(current_command->response,"OK;Register: %s setting PIN:%s to:%s\n",current_command->subcommands[2],\
            current_command->subcommands[3],current_command->subcommands[4]);
        }


        //else{
        //    sprintf(current_command->response,"ERROR;Unknown Operation with Register: %s\n",current_command->subcommands[2]);
        //    return;
        //}

    }// REGISTER

    else{
        sprintf(current_command->response,"ERROR;Unknown command: %s\n",current_command->subcommands[1]);
    }
}

static void readCommands(commandTemplate* current_command){

    if (current_command->number_of_subcommands == 1){
        sprintf(current_command->response, "ERROR;Subcommand is missing, received: %s %s\n", current_command->command, current_command->subcommands[0]);	
    return;
    }

    if(strcmp(current_command->subcommands[1],"CONFIGURATION") == 0){
        if (checkNumberOfSubcommands(1,1,current_command) == 0) return;
        if (strcmp(current_command->subcommands[2],"SHIFT_REGISTERS") == 0)
        {
            static char EXT_REG_value[21];
            memcpy(EXT_REG_value,uint64ToDecimal(EXT_REG.current_satus),21);
            sprintf(current_command->response,"OK;EXT:(length:%d,endianity:%d,value:%s);\n",\
            EXT_REG.shift_reg_length,EXT_REG.endianity,EXT_REG_value);
            //sprintf(current_command->response,"OK;Reading Register %s, value:%s\n",current_command->subcommands[2],uint64ToDecimal(IO1TO40_OUTPUTS.current_satus));
        }
        else{
            sprintf(current_command->response,"ERROR;Unknown Configuration: %s\n",current_command->subcommands[2]);
            return;
            } 
    }//CONFIGURATION

    else if(strcmp(current_command->subcommands[1],"SHIFT_REGISTER") == 0){
        if (checkNumberOfSubcommands(1,1,current_command) == 0) return;
        static ShifRegister* register_ptr;

        //SELECT REGISTER
        if (strcmp(current_command->subcommands[2],"EXT") == 0){
            register_ptr = &EXT_REG;
        }

        else{
            sprintf(current_command->response,"ERROR; Unknown Register: %s\n",current_command->subcommands[2]);
            return;
        }
        //SEND BACK VALUE:
        sprintf(current_command->response,"OK;Reading Register %s, value:%s\n",current_command->subcommands[2],uint64ToDecimal(register_ptr->current_satus));
    }// REGISTER
}

void ExtPortsParser(commandTemplate* current_command){
    //"""Implementation of commands"""
    if (current_command->number_of_subcommands == 0){
        sprintf(current_command->response, "ERROR; Subcommand is missing, received: %s\n", current_command->command);	
        return;
    }
 
    if (strcmp(current_command->subcommands[0],"SET") == 0){
        setCommands(current_command);
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