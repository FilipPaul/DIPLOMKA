#ifndef GLOBALS_H
#define GLOBALS_H
#include "stdio.h"
#include "stdint.h"

#define DELAY_MULTIPLES_OF_2500_NS 2 //5us
#define DO_CLK_PULSE(pinPort, pin) do {\
            HAL_GPIO_WritePin(pinPort,pin,GPIO_PIN_SET);\
            _2500_ns_delay(DELAY_MULTIPLES_OF_2500_NS);\
            HAL_GPIO_WritePin(pinPort,pin,GPIO_PIN_RESET);\
            _2500_ns_delay(DELAY_MULTIPLES_OF_2500_NS);\
           } while(0)



void _2500_ns_delay(uint32_t us); //delay in multiples of approx 2.5us -> not accurate!!
extern uint32_t _us_tick;
#endif