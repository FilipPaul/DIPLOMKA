#include "module80IOcard.h"
#include "stdio.h"
#include "stdlib.h"
#include "main.h"
#include "string.h"
#include "globals.h"
#include "shiftRegisters.h"
#include "multiplexers.h"
#include <inttypes.h>

#define DAC_RAMP_MAX_VALUE 4095
#define DAC_RAMP_MIN_VALUE 0
#define DAC_RAMP_STEP 1
#define DAC_RAMP_DELAY_IN_2500_NS 2
#define DAC_RAMP_DIRECTION_UP 1
#define DAC_RAMP_DIRECTION_DOWN 0
#define VOLTAGE_READ_AVERAGES 10

uint8_t dac_ramp_direction = DAC_RAMP_DIRECTION_DOWN;
/// SHIFT REGISTER PINS MUST BE CHANGED ACCCORDINGLY ---------
ShifRegister IO1TO40_OUTPUTS = {
.ser_pin = PMOS_SHFT_1TO5_SER_Pin,
.srclk_pin = PMOS_SHFT_1TO5_SRCLK_Pin,
.rclk_pin = PMOS_SHFT_1TO5_RCLK_Pin,
.srclr_pin = PMOS_SHFT_1TO5_SRCLR_Pin,
.noe_pin = PMOS_SHFT_1TO5_NOE_Pin,
.ser_port = PMOS_SHFT_1TO5_SER_GPIO_Port,
.srclk_port = PMOS_SHFT_1TO5_SRCLK_GPIO_Port,
.rclk_port = PMOS_SHFT_1TO5_RCLK_GPIO_Port,
.srclr_port = PMOS_SHFT_1TO5_SRCLR_GPIO_Port,
.noe_port = PMOS_SHFT_1TO5_NOE_GPIO_Port,
.current_satus = 0,
.shift_reg_length = 40,
.endianity = REGISTER_ENDIANITY_1_PIN_IS_LSB,
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
.endianity = REGISTER_ENDIANITY_1_PIN_IS_MSB,
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
.endianity = REGISTER_ENDIANITY_1_PIN_IS_LSB,
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
.endianity = REGISTER_ENDIANITY_1_PIN_IS_MSB,
};

Multiplexer MUXES_1TO40 = {
.A0_pin = MUX_A0_Pin,
.A1_pin = MUX_A1_Pin,
.A2_pin = MUX_A2_Pin,
.data_out_pins = {MUX_D1_Pin, MUX_D2_Pin,MUX_D3_Pin,MUX_D4_Pin,MUX_D5_Pin},
.mux_length = 8,
.number_of_paralel_muxes = 5,
.noe_pin = MUX_nOE_Pin,
.A0_port = MUX_A0_GPIO_Port,
.A1_port = MUX_A1_GPIO_Port,
.A2_port = MUX_A2_GPIO_Port,
.data_out_ports = {MUX_D1_GPIO_Port, MUX_D2_GPIO_Port,MUX_D3_GPIO_Port,MUX_D4_GPIO_Port,MUX_D5_GPIO_Port},
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
extern DAC_HandleTypeDef hdac;

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

static void measureCommands(commandTemplate* current_command){
    //Function that handle SET Type commands
     if (current_command->number_of_subcommands == 1){
        sprintf(current_command->response, "ERROR;Subcommand is missing, received: %s %s\n", current_command->command, current_command->subcommands[0]);	
        return;
    }

    if (strcmp(current_command->subcommands[1],"VOLTAGE") == 0){
        if (checkNumberOfSubcommands(1,1,current_command) == 0) return;
        if (strcmp(current_command->subcommands[2],"ALL") == 0){
            sprintf(current_command->response,"ERROR;Command is not supported yet!\n");
            return;
        }
        else{ //ANY NUMBER
            if (dac_ramp_direction ==  DAC_RAMP_DIRECTION_DOWN){ //initial value for ramp  down is FFF
                HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, 0xFFF);
            }
            else{ //RAM DIRECTION DOWN
                HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, 0x000); //initial value for ramp up is 0
            }
           
            _2500_ns_delay(DAC_RAMP_DELAY_IN_2500_NS);
            GPIO_PinState initial_pin_state = MUXreadAdress(atoi(current_command->subcommands[2]),&MUXES_1TO40); // read initial state of the measured pin

            //Check if the voltage is measurable, in other words if the voltage is in range of the DAC
            if ((initial_pin_state == GPIO_PIN_SET) && (dac_ramp_direction ==  DAC_RAMP_DIRECTION_DOWN)){
                sprintf(current_command->response, "ERROR;Voltage is higher than DAC max value!\n");
                return;
            }

            if ((initial_pin_state == GPIO_PIN_RESET) && (dac_ramp_direction ==  DAC_RAMP_DIRECTION_UP)){
                sprintf(current_command->response, "ERROR;Voltage is lower than DAC min value!\n");
                return;
            }


            for (uint16_t i = DAC_RAMP_MIN_VALUE; i < DAC_RAMP_MAX_VALUE  ; i = i + DAC_RAMP_STEP) // For each DAC step
            {
                static uint16_t DAC_VALUE; 
                if (dac_ramp_direction ==  DAC_RAMP_DIRECTION_DOWN){
                    DAC_VALUE = DAC_RAMP_MAX_VALUE - i;
                }
                else{// RAPMP UP
                    DAC_VALUE = i;
                }
                HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, DAC_VALUE);
                _2500_ns_delay(DAC_RAMP_DELAY_IN_2500_NS);
                uint8_t number_of_ones = 0;        
                //Read the pin N times and if the number of reads with oposite value then initial value is bigger
                //store the DAC value and break the loop
                for (uint8_t j = 0; j < VOLTAGE_READ_AVERAGES; j++)
                {
                    number_of_ones += MUXreadAdress(atoi(current_command->subcommands[2]),&MUXES_1TO40);
                }
                if (initial_pin_state == GPIO_PIN_RESET){ //STARTED WITH 0 AT OUTPUT
                   if (number_of_ones > VOLTAGE_READ_AVERAGES/2) //SIMILAR TO RISING EDGE -> VOLTAGE_READS_AVERAGES/2
                   {
                    HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, 0);
                    sprintf(current_command->response,"OK;Voltage in Volts:%1.5f\n",DAC_VALUE*3.300/4096);
                    return;
                   }
                }
                else if (initial_pin_state == GPIO_PIN_SET){ //STARTED WITH 1 AT OUTPUT
                    if (number_of_ones < VOLTAGE_READ_AVERAGES/2) //SIMILAR TO FALLING EDGE -> VOLTAGE_READS_AVERAGES/2
                    {
                        HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, 0); 
                        sprintf(current_command->response,"OK;Voltage in Volts:%1.5f\n",i*3.300/4096);
                        return;
                    }
                }
            }
            sprintf(current_command->response,"ERROR;VOLTAGE IS OUT OF RANGE-> initial read: %d\n", initial_pin_state);

             
        }  
    }//VOLTAGE
}

static void setCommands(commandTemplate* current_command){
    //Function that handle SET Type commands
     if (current_command->number_of_subcommands == 1){
        sprintf(current_command->response, "ERROR;Subcommand is missing, received: %s %s\n", current_command->command, current_command->subcommands[0]);	
        return;
    }

    if (strcmp(current_command->subcommands[1],"DAC") == 0){
        if (checkNumberOfSubcommands(1,1,current_command) == 0) return;

        float ref_voltage = 3.300;
        float voltage_to_be_set;
        voltage_to_be_set = strtof(current_command->subcommands[2],NULL);
        uint32_t dac_value;
        dac_value = (voltage_to_be_set*4096)/ref_voltage;
        HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, dac_value);
        sprintf(current_command->response,"OK;DAC discretized Value in Volts:%1.5f\n",dac_value*ref_voltage/4096);
    
    }//DAC

    else if(strcmp(current_command->subcommands[1],"SHIFT_REGISTER") == 0){
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

        else{
            sprintf(current_command->response,"ERROR;Unknown Operation with Register: %s\n",current_command->subcommands[2]);
            return;
        }

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
            sprintf(current_command->response,"ERROR; Unknown MUX: %s\n",current_command->subcommands[2]);
            return;
        }

        //MUX READ
        if (strcmp(current_command->subcommands[3],"ALL") == 0)
        {
            static uint64_t mux_data;
            mux_data = MUXreadAll(mux_ptr);
            sprintf(current_command->response,"OK;Reading MUX %s, ALL:%s\n",current_command->subcommands[2],uint64ToDecimal(mux_data));
        }

        else{
            GPIO_PinState mux_value;
            mux_value = MUXreadAdress((uint8_t)atoi(current_command->subcommands[3]),mux_ptr);
            sprintf(current_command->response,"OK;Reading MUX: %s, address:%d, value:%d\n",\
            current_command->subcommands[2],(uint8_t)atoi(current_command->subcommands[3]),mux_value);
        }
    }//MUX

    else if(strcmp(current_command->subcommands[1],"SHIFT_REGISTER") == 0){
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
            sprintf(current_command->response,"ERROR; Unknown Register: %s\n",current_command->subcommands[2]);
            return;
        }
        //SEND BACK VALUE:
        sprintf(current_command->response,"OK;Reading Register %s, value:%s\n",current_command->subcommands[2],uint64ToDecimal(register_ptr->current_satus));
    }// REGISTER
}

void module80CardParser(commandTemplate* current_command){
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
        measureCommands(current_command);
    }

    else{
        sprintf(current_command->response, "ERROR; Unknown command: %s\n", current_command->subcommands[0]);
    }
    

}