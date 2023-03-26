#include "module80IOcard.h"
#include "stdio.h"
#include "stdlib.h"
#include "main.h"
#include "string.h"
#include "globals.h"
#include "shiftRegisters.h"
#include "multiplexers.h"
#include <inttypes.h>

/// SHIFT REGISTER PINS MUST BE CHANGED ACCCORDINGLY ---------
ShifRegister IO1TO40_OUTPUTS = {
.ser_pin = NMOS_SHFT_1TO5_SER_Pin,
.srclk_pin = NMOS_SHFT_1TO5_SRCLK_Pin,
.rclk_pin = NMOS_SHFT_1TO5_RCLK_Pin,
.srclr_pin = NMOS_SHFT_1TO5_SRCLR_Pin,
.noe_pin = NMOS_SHFT_1TO5_NOE_Pin,
.ser_port = NMOS_SHFT_1TO5_SER_GPIO_Port,
.srclk_port = NMOS_SHFT_1TO5_SRCLK_GPIO_Port,
.rclk_port = NMOS_SHFT_1TO5_RCLK_GPIO_Port,
.srclr_port = NMOS_SHFT_1TO5_SRCLR_GPIO_Port,
.noe_port = NMOS_SHFT_1TO5_NOE_GPIO_Port,
.current_satus = 0,
.shift_reg_length = 40,
};


ShifRegister IO41TO80_OUTPUTS = {
.ser_pin = NMOS_SHFT_1TO5_SER_Pin,
.srclk_pin = NMOS_SHFT_1TO5_SRCLK_Pin,
.rclk_pin = NMOS_SHFT_1TO5_RCLK_Pin,
.srclr_pin = NMOS_SHFT_1TO5_SRCLR_Pin,
.noe_pin = NMOS_SHFT_1TO5_NOE_Pin,
.ser_port = NMOS_SHFT_1TO5_SER_GPIO_Port,
.srclk_port = NMOS_SHFT_1TO5_SRCLK_GPIO_Port,
.rclk_port = NMOS_SHFT_1TO5_RCLK_GPIO_Port,
.srclr_port = NMOS_SHFT_1TO5_SRCLR_GPIO_Port,
.noe_port = NMOS_SHFT_1TO5_NOE_GPIO_Port,
.current_satus = 0,
.shift_reg_length = 40,
};

ShifRegister IO1TO40_IMPEDANCES = {
.ser_pin = NMOS_SHFT_1TO5_SER_Pin,
.srclk_pin = NMOS_SHFT_1TO5_SRCLK_Pin,
.rclk_pin = NMOS_SHFT_1TO5_RCLK_Pin,
.srclr_pin = NMOS_SHFT_1TO5_SRCLR_Pin,
.noe_pin = NMOS_SHFT_1TO5_NOE_Pin,
.ser_port = NMOS_SHFT_1TO5_SER_GPIO_Port,
.srclk_port = NMOS_SHFT_1TO5_SRCLK_GPIO_Port,
.rclk_port = NMOS_SHFT_1TO5_RCLK_GPIO_Port,
.srclr_port = NMOS_SHFT_1TO5_SRCLR_GPIO_Port,
.noe_port = NMOS_SHFT_1TO5_NOE_GPIO_Port,
.current_satus = 0,
.shift_reg_length = 40,
};


ShifRegister IO41TO80_IMPEDANCES = {
.ser_pin = NMOS_SHFT_1TO5_SER_Pin,
.srclk_pin = NMOS_SHFT_1TO5_SRCLK_Pin,
.rclk_pin = NMOS_SHFT_1TO5_RCLK_Pin,
.srclr_pin = NMOS_SHFT_1TO5_SRCLR_Pin,
.noe_pin = NMOS_SHFT_1TO5_NOE_Pin,
.ser_port = NMOS_SHFT_1TO5_SER_GPIO_Port,
.srclk_port = NMOS_SHFT_1TO5_SRCLK_GPIO_Port,
.rclk_port = NMOS_SHFT_1TO5_RCLK_GPIO_Port,
.srclr_port = NMOS_SHFT_1TO5_SRCLR_GPIO_Port,
.noe_port = NMOS_SHFT_1TO5_NOE_GPIO_Port,
.current_satus = 0,
.shift_reg_length = 40,
};

Multiplexer MUXES_1TO40 = {
.A0_pin = MUX_A0_Pin,
.A1_pin = MUX_A1_Pin,
.A2_pin = MUX_A2_Pin,
.data_out_pins = {MUX_D1_Pin, MUX_D2_Pin,MUX_D3_Pin,MUX_D4_Pin},
.mux_length = 8,
.number_of_paralel_muxes = 5,
.noe_pin = MUX_nOE_Pin,
.A0_port = MUX_A0_GPIO_Port,
.A1_port = MUX_A1_GPIO_Port,
.A2_port = MUX_A2_GPIO_Port,
.data_out_ports = {MUX_D1_GPIO_Port, MUX_D2_GPIO_Port,MUX_D3_GPIO_Port,MUX_D4_GPIO_Port},
.noe_port = MUX_nOE_GPIO_Port,
.current_satus = 0,
};

Multiplexer MUXES_41TO80 = {
.A0_pin = MUX_A0_Pin,
.A1_pin = MUX_A1_Pin,
.A2_pin = MUX_A2_Pin,
.data_out_pins = {MUX_D1_Pin, MUX_D2_Pin,MUX_D3_Pin,MUX_D4_Pin},
.mux_length = 8,
.number_of_paralel_muxes = 5,
.noe_pin = MUX_nOE_Pin,
.A0_port = MUX_A0_GPIO_Port,
.A1_port = MUX_A1_GPIO_Port,
.A2_port = MUX_A2_GPIO_Port,
.data_out_ports = {MUX_D1_GPIO_Port, MUX_D2_GPIO_Port,MUX_D3_GPIO_Port,MUX_D4_GPIO_Port},
.noe_port = MUX_nOE_GPIO_Port,
.current_satus = 0,
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
        sprintf(current_command->response,"ERROR: Wrong number of arguments after command: %s \
(Expected %d, got %d)\n",current_command->subcommands[current_subcommand_index] ,expected_number,current_command->number_of_subcommands-current_subcommand_index-1);
        return 0;
        }
    return 1;
}

static void setCommands(commandTemplate* current_command){
    //Function that handle SET Type commands
     if (current_command->number_of_subcommands == 1){
        sprintf(current_command->response, "ERROR: Subcommand is missing, received: %s %s\n", current_command->command, current_command->subcommands[0]);	
        return;
    }

    if (strcmp(current_command->subcommands[1],"DAC") == 0){
        if (checkNumberOfSubcommands(1,1,current_command) == 0) return;

        float ref_voltage = 3.300;
        float voltage_to_be_set;
        voltage_to_be_set = strtof(current_command->subcommands[2],NULL);
        uint32_t dac_value;
        dac_value = (voltage_to_be_set*4096)/ref_voltage;
        extern DAC_HandleTypeDef hdac;
        HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, dac_value);
        sprintf(current_command->response,"OK:Setting DAC to %1.5fV\n",dac_value*ref_voltage/4096);
    
    }//DAC

    else if(strcmp(current_command->subcommands[1],"REGISTER") == 0){
        if (checkNumberOfSubcommands(3,1,current_command) == 0) return;
        static ShifRegister* register_ptr;

        //SELECT REGISTER
        if (strcmp(current_command->subcommands[2],"IO1TO40_OUTPUTS") == 0){
            register_ptr = &IO1TO40_OUTPUTS;
        }

        else if (strcmp(current_command->subcommands[2],"IO41TO80_OUTPUTS") == 0){
            register_ptr = &IO41TO80_OUTPUTS;
        }

        
        else if (strcmp(current_command->subcommands[2],"IO1TO40_IMPEDANCES") == 0){
            register_ptr = &IO1TO40_IMPEDANCES;
        }

        else if (strcmp(current_command->subcommands[2],"IO41TO80_IMPEDANCES") == 0){
            register_ptr = &IO41TO80_IMPEDANCES;
        }

        else{
            sprintf(current_command->response,"ERROR: Unknown Register: %s\n",current_command->subcommands[2]);
            return;
        }
        //UPDATE REGISTER
        if (strcmp(current_command->subcommands[3],"VALUE") == 0)
        {
            uint64_t data = strtoull(current_command->subcommands[4],NULL,10);
            loadDataToShiftReg(data,register_ptr);
            sprintf(current_command->response,"OK:Setting Register %s to %s\n",current_command->subcommands[2],uint64ToDecimal(data));
        }

        else if(strcmp(current_command->subcommands[3],"DO_N_SHIFTS") == 0)
        {
            shiftRegNtimesShift((uint8_t)atoi(current_command->subcommands[4]),register_ptr);
            sprintf(current_command->response,"OK:Shifting Register %s %d times\n",current_command->subcommands[2],(uint8_t)atoi(current_command->subcommands[4]));
        }

        else{
            sprintf(current_command->response,"ERROR: Unknown Register: %s\n",current_command->subcommands[2]);
            return;
        }

    }// REGISTER

    else{
        sprintf(current_command->response,"ERROR: Unknown command: %s\n",current_command->subcommands[1]);
    }
}

static void readCommands(commandTemplate* current_command){

    if (current_command->number_of_subcommands == 1){
        sprintf(current_command->response, "ERROR: Subcommand is missing, received: %s %s\n", current_command->command, current_command->subcommands[0]);	
    return;
    }
    if (strcmp(current_command->subcommands[1],"MUX") == 0){
        if (checkNumberOfSubcommands(2,1,current_command) == 0) return;
        //MUX SELECTION
        static Multiplexer* mux_ptr;

        if (strcmp(current_command->subcommands[2],"MUXES_1TO40") == 0){
            mux_ptr = &MUXES_1TO40;
        }

        else if (strcmp(current_command->subcommands[2],"MUXES_41TO80") == 0){
            mux_ptr = &MUXES_41TO80;
        }

        else{
            sprintf(current_command->response,"ERROR: Unknown MUX: %s\n",current_command->subcommands[2]);
            return;
        }

        //MUX READ
        if (strcmp(current_command->subcommands[3],"ALL") == 0)
        {
            static uint32_t data;
            data = MUXreadAll(mux_ptr);
            sprintf(current_command->response,"OK:Reading MUX %s, ALL:%lu\n",current_command->subcommands[2],data);
        }

        else{
            GPIO_PinState mux_value;
            mux_value = MUXreadAdress((uint8_t)atoi(current_command->subcommands[3]),mux_ptr);
            sprintf(current_command->response,"OK:Reading MUX: %s, address:%d, value:%d\n",\
            current_command->subcommands[2],(uint8_t)atoi(current_command->subcommands[3]),mux_value);
        }
    }//MUX

    else if(strcmp(current_command->subcommands[1],"REGISTER") == 0){
        if (checkNumberOfSubcommands(1,1,current_command) == 0) return;
        static ShifRegister* register_ptr;

        //SELECT REGISTER
        if (strcmp(current_command->subcommands[2],"IO1TO40_OUTPUTS") == 0){
            register_ptr = &IO1TO40_OUTPUTS;
        }

        else if (strcmp(current_command->subcommands[2],"IO41TO80_OUTPUTS") == 0){
            register_ptr = &IO41TO80_OUTPUTS;
        }

        
        else if (strcmp(current_command->subcommands[2],"IO1TO40_IMPEDANCES") == 0){
            register_ptr = &IO1TO40_IMPEDANCES;
        }

        else if (strcmp(current_command->subcommands[2],"IO41TO80_IMPEDANCES") == 0){
            register_ptr = &IO41TO80_IMPEDANCES;
        }

        else{
            sprintf(current_command->response,"ERROR: Unknown Register: %s\n",current_command->subcommands[2]);
            return;
        }
        //SEND BACK VALUE:
        sprintf(current_command->response,"OK:Reading Register %s, value:%s\n",current_command->subcommands[2],uint64ToDecimal(register_ptr->current_satus));
    }// REGISTER
}

void module80CardParser(commandTemplate* current_command){
    //"""Implementation of commands"""
    if (current_command->number_of_subcommands == 0){
        sprintf(current_command->response, "ERROR: Subcommand is missing, received: %s\n", current_command->command);	
        return;
    }
 
    if (strcmp(current_command->subcommands[0],"SET") == 0){
        setCommands(current_command);
    }

    else if (strcmp(current_command->subcommands[0],"READ") == 0){
        readCommands(current_command);
    }
    else{
        sprintf(current_command->response, "ERROR: Unknown command: %s\n", current_command->subcommands[0]);
    }
    

}