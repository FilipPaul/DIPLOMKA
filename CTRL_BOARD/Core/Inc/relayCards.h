#ifndef RELAYCARDS_H
#define RELAYCARDS_H

#include "main.h"
#include "stdint.h"
#include "globals.h"
#include "shiftRegisters.h"
typedef struct RelayCards{
    uint16_t SN74238_A_EXT_PORT_pin_number;
    uint16_t SN74238_B_EXT_PORT_pin_number;
    uint16_t SN74238_C_EXT_PORT_pin_number;
    uint16_t SN74238_E3_EXT_PORT_pin_number;
    uint16_t SN74AC175D_D1_EXT_PORT_pin_number;
    uint16_t SN74AC175D_D2_EXT_PORT_pin_number;
    uint16_t SN74AC175D_D3_EXT_PORT_pin_number;
    uint16_t SN74AC175D_D4_EXT_PORT_pin_number;
    ShifRegister* shift_register; //pointer to shift register to which is relay card connected
    uint8_t number_of_relays;
    uint32_t current_satus;
    uint8_t ext_port_number;
} RelayCards;

uint8_t relayCardSetSingleRelay(uint8_t relay_number, uint8_t relay_state, RelayCards* RelayCard); //returns new relay state
uint32_t relayCardSetAllRelays(uint32_t value, RelayCards* RelayCard); //returns new port state
#endif