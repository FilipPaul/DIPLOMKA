#include "relayCards.h"
#include "main.h"

uint8_t relayCardSetSingleRelay(uint8_t relay_number, uint8_t relay_state, RelayCards* RelayCard){
    /*First of all set E3 to 0 -> CLK pin of all flipflops (connected to the SN74..238) is set to 0.
    Pin E3 is connected to the shift register output), but to this register are all 3 EXT ports connected,
    so we cannot change the whole register....*/

    //Remaping of pins to the shift register position
    static uint8_t pin_E3;
    static uint8_t pin_A;
    static uint8_t pin_B;
    static uint8_t pin_C;
    static uint8_t pin_D1;
    static uint8_t pin_D2;
    static uint8_t pin_D3;
    static uint8_t pin_D4;
    static uint32_t offset;
    offset = 24 - RelayCard->ext_port_number*8;

    pin_E3 = 8 - RelayCard->SN74238_E3_EXT_PORT_pin_number +  offset;
    pin_A =  8 - RelayCard->SN74238_A_EXT_PORT_pin_number +  offset;
    pin_B =  8 - RelayCard->SN74238_B_EXT_PORT_pin_number +  offset;
    pin_C =  8 - RelayCard->SN74238_C_EXT_PORT_pin_number +  offset;
    pin_D1 = 8 - RelayCard->SN74AC175D_D1_EXT_PORT_pin_number +  offset;
    pin_D2 = 8 - RelayCard->SN74AC175D_D2_EXT_PORT_pin_number +  offset;
    pin_D3 = 8 - RelayCard->SN74AC175D_D3_EXT_PORT_pin_number +  offset;
    pin_D4 = 8 - RelayCard->SN74AC175D_D4_EXT_PORT_pin_number +  offset;


    //set clk of all flipflops to 0
    shiftRegSetSinglePin(pin_E3, 0, RelayCard->shift_register);
    _2500_ns_delay(5);
    
    //SET value to the D1,D2,D3,D4 pins -> they are grouped by 4 - current state of 4 pins:
    static uint8_t Dpins_state;
    Dpins_state = (RelayCard->current_satus >> ( (uint8_t)(relay_number / 4) *4 ) ) & 0x0F;
    printf("Dpins_state before: %d\n", Dpins_state);

    if (relay_state == 1){
        Dpins_state = Dpins_state | (1 << relay_number % 4);
    }
    else{
        Dpins_state = Dpins_state & ~(1 << relay_number % 4);
    }
    printf("Dpins_state after: %d\n", Dpins_state);
    // set new states:
    shiftRegSetSinglePin(pin_D1, Dpins_state & 0x01, RelayCard->shift_register);
    shiftRegSetSinglePin(pin_D2, Dpins_state & 0x02, RelayCard->shift_register);
    shiftRegSetSinglePin(pin_D3, Dpins_state & 0x04, RelayCard->shift_register);
    shiftRegSetSinglePin(pin_D4, Dpins_state & 0x08, RelayCard->shift_register);


    //set A,B,C pins to the value coresponding to the relay number

    shiftRegSetSinglePin(pin_A, (relay_number / 4) & 0x01, RelayCard->shift_register);
    shiftRegSetSinglePin(pin_B, (relay_number / 4) & 0x02, RelayCard->shift_register);
    shiftRegSetSinglePin(pin_C, (relay_number / 4) & 0x04, RelayCard->shift_register);
    
    //set clk of all flipflops to 1
    _2500_ns_delay(5);
    shiftRegSetSinglePin(pin_E3, 1, RelayCard->shift_register);
    _2500_ns_delay(5);
    //set clk of all flipflops to 0
    shiftRegSetSinglePin(pin_E3, 0, RelayCard->shift_register);
    //Update new relay status

    printf("Relay EXT PORT %d, relay %d, state %d -> previous State: %lu \n", RelayCard->ext_port_number,\
    relay_number, relay_state, RelayCard->current_satus);

    if(relay_state == 1){
        RelayCard->current_satus = RelayCard->current_satus | (1 << relay_number);
    }
    else{
        RelayCard->current_satus= RelayCard->current_satus & ~(1 << relay_number);
    }
    printf("Relay EXT PORT %d, relay %d, state %d -> new state: %lu \n", RelayCard->ext_port_number,\
    relay_number, relay_state, RelayCard->current_satus);
    return 1;
    
}
uint32_t relayCardSetAllRelays(uint32_t value, RelayCards* RelayCard){
    return 1;
}