#include "module80IOcard.h"
#include "stdio.h"
#include "stdlib.h"
#include "main.h"
#include "string.h"
#include "globals.h"
#include "shiftRegisters.h"
#include "multiplexers.h"
#include <inttypes.h>

// default settings value -> can be set by user using SET CONFIGURATION command
#define DAC_RAMP_DIRECTION_UP 1
#define DAC_RAMP_DIRECTION_DOWN 0

uint16_t dac_ramp_min_value = 0;
uint16_t dac_ramp_max_value = 4095;
uint16_t dac_ramp_step = 1;
uint16_t dac_ramp_delay_in_2500_ns = 2;
uint16_t voltage_read_averages = 10;
float voltage_reference = 3.3;
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
.ser_pin = PMOS_SHFT_6TO10_SER_Pin,
.srclk_pin = PMOS_SHFT_6TO10_SRCLK_Pin,
.rclk_pin = PMOS_SHFT_6TO10_RCLK_Pin,
.srclr_pin = PMOS_SHFT_6TO10_SRCLR_Pin,
.noe_pin = PMOS_SHFT_6TO10_NOE_Pin,
.ser_port = PMOS_SHFT_6TO10_SER_GPIO_Port,
.srclk_port = PMOS_SHFT_6TO10_SRCLK_GPIO_Port,
.rclk_port = PMOS_SHFT_6TO10_RCLK_GPIO_Port,
.srclr_port = PMOS_SHFT_6TO10_SRCLR_GPIO_Port,
.noe_port = PMOS_SHFT_6TO10_NOE_GPIO_Port,
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
.ser_pin = NMOS_SHFT_6TO10_SER_Pin,
.srclk_pin = NMOS_SHFT_6TO10_SRCLK_Pin,
.rclk_pin = NMOS_SHFT_6TO10_RCLK_Pin,
.srclr_pin = NMOS_SHFT_6TO10_SRCLR_Pin,
.noe_pin = NMOS_SHFT_6TO10_NOE_Pin,
.ser_port = NMOS_SHFT_6TO10_SER_GPIO_Port,
.srclk_port = NMOS_SHFT_6TO10_SRCLK_GPIO_Port,
.rclk_port = NMOS_SHFT_6TO10_RCLK_GPIO_Port,
.srclr_port = NMOS_SHFT_6TO10_SRCLR_GPIO_Port,
.noe_port = NMOS_SHFT_6TO10_NOE_GPIO_Port,
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
.endianity = REGISTER_ENDIANITY_1_PIN_IS_MSB,
};

Multiplexer MUXES_41TO80 = {
.A0_pin = MUX2_A0_Pin,
.A1_pin = MUX2_A1_Pin,
.A2_pin = MUX2_A2_Pin,
.data_out_pins = {MUX_D6_Pin, MUX_D7_Pin,MUX_D8_Pin,MUX_D9_Pin,MUX_D10_Pin},
.mux_length = 8,
.number_of_paralel_muxes = 5,
.noe_pin = MUX2_nOE_Pin,
.A0_port = MUX2_A0_GPIO_Port,
.A1_port = MUX2_A1_GPIO_Port,
.A2_port = MUX2_A2_GPIO_Port,
.data_out_ports = {MUX_D6_GPIO_Port, MUX_D7_GPIO_Port,MUX_D8_GPIO_Port,MUX_D9_GPIO_Port,MUX_D10_GPIO_Port},
.noe_port = MUX2_nOE_GPIO_Port,
.current_satus = 0,
.endianity = REGISTER_ENDIANITY_1_PIN_IS_MSB,
};

static char bfr[20+1];
extern DAC_HandleTypeDef hdac;
float pin_voltages[80];

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


const char* uint64_to_decimal_string(uint64_t num) {
    int digits = 0;
    uint64_t temp = num;
    do {
        digits++;
        temp /= 10;
    } while (temp);
    const int buffer_size = digits + 1;
    char* buffer = (char*) malloc(buffer_size * sizeof(char));
    if (!buffer) {
        return NULL;
    }
    int i = 0;
    do {
        buffer[i++] = num % 10 + '0';
        num /= 10;
    } while (num);
    buffer[i] = '\0';
    int j = i - 1;
    i = 0;
    while (i < j) {
        char temp = buffer[i];
        buffer[i] = buffer[j];
        buffer[j] = temp;
        i++;
        j--;
    }
    const char* result = (const char*) buffer;
    return result;
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
        if (strcmp(current_command->subcommands[2],"ALL") == 0){ //MEASURE VOLTAGE AT ALL PINS IN HIGH Z STATE
            if (dac_ramp_direction ==  DAC_RAMP_DIRECTION_DOWN){ //initial value for ramp  down is FFF
                HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, 0xFFF);
            }
            else{ //RAM DIRECTION DOWN
                HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, 0x000); //initial value for ramp up is 0
            }
        
            //FILL ALL MEASURED VALUES WITH -1 (NOT MEASURED)
            for (uint8_t i = 0; i < 80; i++){
                pin_voltages[i] = -1;
            }
            //READ STATUS OF EACH PIN FOR FIRST MULTIPLEXER
            MUXreadAll(&MUXES_1TO40);
            MUXreadAll(&MUXES_41TO80);

            for (uint16_t i = dac_ramp_min_value; i < dac_ramp_max_value  ; i = i + dac_ramp_step) // For each DAC step
            {
                static uint16_t DAC_VALUE; 
                if (dac_ramp_direction ==  DAC_RAMP_DIRECTION_DOWN){
                    DAC_VALUE = dac_ramp_max_value  - i;
                }
                else{// RAPMP UP
                    DAC_VALUE = i;
                }

                HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, DAC_VALUE);
                _2500_ns_delay(dac_ramp_delay_in_2500_ns);

                //READ STATUS OF EACH PIN FOR FIRST MULTIPLEXER
                
                for (uint8_t pin = 0; pin < 40; pin++)
                {
                    //AVERAGE EACH READ....
                    if(pin_voltages[pin] != -1) continue; //if the pin is already measured, skip it, because it is already measured
                    uint16_t number_of_oposite_readings = 0;
                    for (uint16_t j = 0; j < voltage_read_averages; j++){ // do averaging
                        number_of_oposite_readings += (MUXreadAdress(pin,&MUXES_1TO40) != ((MUXES_1TO40.current_satus >> pin) & 0x01));
                        if (number_of_oposite_readings > voltage_read_averages/2){
                            pin_voltages[pin] = DAC_VALUE * voltage_reference /4096;
                            break;
                        }
                    }
                }
                    
                

                //READ STATUS OF EACH PIN FOR SECOND MULTIPLEXER
                for (uint8_t pin = 0; pin < 40; pin++)
                {
                    if(pin_voltages[pin+40] != -1) continue; //if the pin is already measured, skip it, because it is already measured
                    uint16_t number_of_oposite_readings = 0;
                    for (uint16_t j = 0; j < voltage_read_averages; j++){ // do averaging
                        number_of_oposite_readings += (MUXreadAdress(pin,&MUXES_41TO80) != ((MUXES_41TO80.current_satus >> (40 - pin)) & 0x01));
                        if (number_of_oposite_readings > voltage_read_averages/2){
                            pin_voltages[pin+40] = DAC_VALUE * voltage_reference /4096;
                            break;
                        }
                    }
                }
            }


            //RESPONSE
            sprintf(current_command->response,"OK;");
            for (uint8_t i = 0; i < 80; i++){
                sprintf(current_command->response + strlen(current_command->response),"%f;",pin_voltages[i]);
            }
            sprintf(current_command->response + strlen(current_command->response),"\n");
        }//ALL

        else{ //ANY NUMBER
            if (dac_ramp_direction ==  DAC_RAMP_DIRECTION_DOWN){ //initial value for ramp  down is FFF
                HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, 0xFFF);
            }
            else{ //RAM DIRECTION DOWN
                HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, 0x000); //initial value for ramp up is 0
            }
        
            //FILL ALL MEASURED VALUES WITH -1 (NOT MEASURED)
            uint8_t initial_value = 0;
            uint8_t pin_number; 
            pin_number = atoi(current_command->subcommands[2]);
            //READ STATUS OF EACH PIN FOR FIRST MULTIPLEXER
            if (pin_number < 40){
                initial_value =  MUXreadAdress(pin_number,&MUXES_1TO40);
            }
            else if (pin_number < 80){
                pin_number -= 40;
                initial_value =  MUXreadAdress(pin_number,&MUXES_41TO80);
            }
            else{
                sprintf(current_command->response,"ERROR; PIN NUMBER OUT OF RANGE");
            }
             
            for (uint16_t i = dac_ramp_min_value; i < dac_ramp_max_value  ; i = i + dac_ramp_step) // For each DAC step
            {
                static uint16_t DAC_VALUE; 
                if (dac_ramp_direction ==  DAC_RAMP_DIRECTION_DOWN){
                    DAC_VALUE = dac_ramp_max_value  - i;
                }
                else{// RAPMP UP
                    DAC_VALUE = i;
                }

                HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, DAC_VALUE);
                _2500_ns_delay(dac_ramp_delay_in_2500_ns);

                //AVERAGE EACH READ....
                uint16_t number_of_oposite_readings = 0;
                for (uint16_t j = 0; j < voltage_read_averages; j++){ // do averaging
                    number_of_oposite_readings += (MUXreadAdress(pin_number,&MUXES_1TO40) != initial_value);
                    if (number_of_oposite_readings > voltage_read_averages/2){
                        pin_voltages[pin_number] = DAC_VALUE * voltage_reference /4096;
                        sprintf(current_command->response,"OK;Voltage:%f\n",pin_voltages[pin_number]);
                        return;
                    }
                }//AVERAGINGLOOP

            }//DAC LOOP
             sprintf(current_command->response,"ERROR;Voltage OUT OF RANGE:-1\n");
        }//ANY NUMBER
    }//VOLTAGE
}//MEASURE COMMANDS
static void setCommands(commandTemplate* current_command){
    //Function that handle SET Type commands
     if (current_command->number_of_subcommands == 1){
        sprintf(current_command->response, "ERROR;Subcommand is missing, received: %s %s\n", current_command->command, current_command->subcommands[0]);	
        return;
    }

    if (strcmp(current_command->subcommands[1],"DAC") == 0){
        if (checkNumberOfSubcommands(1,1,current_command) == 0) return;

        float voltage_to_be_set;
        voltage_to_be_set = strtof(current_command->subcommands[2],NULL);
        if (voltage_to_be_set > voltage_reference) {
            sprintf(current_command->response,"ERROR;Requested voltage %f is bigger than reference voltage %f\n",voltage_to_be_set,voltage_reference);
            return;
        }

        uint32_t dac_value;
        dac_value = (voltage_to_be_set*4096)/voltage_reference;
        HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, dac_value);
        sprintf(current_command->response,"OK;DAC: %lu, discretized Value in Volts:%1.5f\n",dac_value,dac_value*voltage_reference/4096);
    
    }//DAC

    else if(strcmp(current_command->subcommands[1],"CONFIGURATION") == 0){ 
        if (checkNumberOfSubcommands(2,1,current_command) == 0) return;

        if (strcmp(current_command->subcommands[2], "DAC_RAMP_DIRECTION") == 0){ //SET CONFIGURATION DAC_RAMP_DIRECTION UP|DOWN -> 0 = UP, 1 = DOWN
            if (strcmp(current_command->subcommands[3], "UP") == 0){
                dac_ramp_direction = DAC_RAMP_DIRECTION_UP;
                sprintf(current_command->response,"OK;DAC_RAMP_DIRECTION set to:UP\n");
            }
            else if (strcmp(current_command->subcommands[3], "DOWN") == 0){
                dac_ramp_direction = DAC_RAMP_DIRECTION_DOWN;
                sprintf(current_command->response,"OK;DAC_RAMP_DIRECTION set to:DOWN\n");
            }
            else{
                sprintf(current_command->response,"ERROR;DAC_RAMP_DIRECTION can be only UP or DOWN\n");
            }            
        }
        else if (strcmp(current_command->subcommands[2], "DAC_RAMP_MIN_VALUE") == 0){
            dac_ramp_min_value = atoi(current_command->subcommands[3]);
            sprintf(current_command->response,"OK;DAC_RAMP_MIN_VALUE set to:%d\n",dac_ramp_min_value);
        }

        else if (strcmp(current_command->subcommands[2], "DAC_RAMP_MAX_VALUE") == 0){
            dac_ramp_max_value = atoi(current_command->subcommands[3]);
            sprintf(current_command->response,"OK;DAC_RAMP_MAX_VALUE set to:%d\n",dac_ramp_max_value);
        }

        else if (strcmp(current_command->subcommands[2], "DAC_RAMP_STEP") == 0){
            dac_ramp_step = atoi(current_command->subcommands[3]);
            sprintf(current_command->response,"OK;DAC_RAMP_STEP set to:%d\n",dac_ramp_step);
        }

        else if (strcmp(current_command->subcommands[2], "DAC_RAMP_DELAY_2500_NS") == 0){
            dac_ramp_delay_in_2500_ns = atoi(current_command->subcommands[3]);
            sprintf(current_command->response,"OK;DAC_RAMP_DELAY_2500_NS set to:%d\n",dac_ramp_delay_in_2500_ns);
        }

        else if (strcmp(current_command->subcommands[2], "VOLTAGE_READ_AVERAGES") == 0){
            voltage_read_averages = atoi(current_command->subcommands[3]);
            sprintf(current_command->response,"OK;DAC_RAMP_DELAY_2500_NS set to:%d\n",voltage_read_averages);
        }

        else if (strcmp(current_command->subcommands[2], "VOLTAGE_REFERENCE") == 0){
            voltage_reference = strtof(current_command->subcommands[3],NULL);
            sprintf(current_command->response,"OK;VOLTAGE_REFERENCE set to:%f\n",voltage_reference);
        }

        else{
            sprintf(current_command->response,"ERROR;Unknown command: %s\n",current_command->subcommands[2]);
        }
    } //CONFIGURATION
        

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

    else if(strcmp(current_command->subcommands[1],"CONFIGURATION") == 0){
        if (checkNumberOfSubcommands(1,1,current_command) == 0) return;

        if(strcmp(current_command->subcommands[2], "VOLTAGE_READINGS") == 0){
        sprintf(current_command->response,"OK;DAC_RAMP_DIRECTION:%d;DAC_RAMP_MIN_VALUE:%d;DAC_RAMP_MAX_VALUE:%d;DAC_RAMP_STEP:%d;DAC_RAMP_DELAY_2500_NS:%d;\
VOLTAGE_READ_AVERAGES:%d;VOLTAGE_REFERENCE:%f;\n",\
dac_ramp_direction,dac_ramp_min_value,dac_ramp_max_value,dac_ramp_step,dac_ramp_delay_in_2500_ns,voltage_read_averages,voltage_reference);
        }

        else if (strcmp(current_command->subcommands[2],"SHIFT_REGISTERS") == 0)
        {
            static char IO1TO40_OUTPUTS_value[21];
            static char IO41TO80_OUTPUTS_value[21];
            static char IO1TO40_IMPEDANCES_value[21];
            static char IO41TO80_IMPEDANCES_value[21];

            memcpy(IO1TO40_OUTPUTS_value,uint64ToDecimal(IO1TO40_OUTPUTS.current_satus),21);
            memcpy(IO41TO80_OUTPUTS_value,uint64ToDecimal(IO41TO80_OUTPUTS.current_satus),21);
            memcpy(IO1TO40_IMPEDANCES_value,uint64ToDecimal(IO1TO40_IMPEDANCES.current_satus),21);
            memcpy(IO41TO80_IMPEDANCES_value,uint64ToDecimal(IO41TO80_IMPEDANCES.current_satus),21);

            sprintf(current_command->response,"OK;IO1TO40_OUTPUTS:(length:%d,endianity:%d,value:%s);IO41TO80_OUTPUTS:(length:%d,endianity:%d,value:%s);\
IO1TO40_IMPEDANCES:(length:%d,endianity:%d,value:%s);IO41TO80_IMPEDANCES:(length:%d,endianity:%d,value:%s);\n",\
            IO1TO40_OUTPUTS.shift_reg_length,IO1TO40_OUTPUTS.endianity,IO1TO40_OUTPUTS_value,\
            IO41TO80_OUTPUTS.shift_reg_length,IO41TO80_OUTPUTS.endianity,IO41TO80_OUTPUTS_value,\
            IO1TO40_IMPEDANCES.shift_reg_length,IO1TO40_IMPEDANCES.endianity,IO1TO40_IMPEDANCES_value,\
            IO41TO80_IMPEDANCES.shift_reg_length,IO41TO80_IMPEDANCES.endianity,IO41TO80_IMPEDANCES_value);

            //sprintf(current_command->response,"OK;Reading Register %s, value:%s\n",current_command->subcommands[2],uint64ToDecimal(IO1TO40_OUTPUTS.current_satus));
        }

        else if (strcmp(current_command->subcommands[2],"MULTIPLEXERS") == 0)
        {
            static char MUXES_1TO40_value[21];
            static char MUXES_41TO80_value[21];

            memcpy(MUXES_1TO40_value,uint64ToDecimal(MUXES_1TO40.current_satus),21);
            memcpy(MUXES_41TO80_value,uint64ToDecimal(MUXES_41TO80.current_satus),21);

            sprintf(current_command->response,"OK;MUXES_1TO40:(bits:%d,paralel:%d,endianity:%d,value:%s);MUXES_41TO80:(bits:%d,paralel:%d,endianity:%d,value:%s);\n",\
            MUXES_1TO40.mux_length,MUXES_1TO40.number_of_paralel_muxes,MUXES_1TO40.endianity,MUXES_1TO40_value,\
            MUXES_41TO80.mux_length,MUXES_41TO80.number_of_paralel_muxes,MUXES_41TO80.endianity,MUXES_41TO80_value);
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