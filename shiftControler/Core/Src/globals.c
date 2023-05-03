
#include "globals.h"
#include "main.h"

uint32_t _us_tick;
void _2500_ns_delay(uint32_t us){
    uint32_t start = _us_tick;
    //printf("start: %lu, _us_tick: %lu, us: %lu\n", start, _us_tick, us);
    //HAL_GPIO_WritePin(TIMER_check_GPIO_Port, TIMER_check_Pin, GPIO_PIN_SET);
    while((_us_tick - start) < us){
        __NOP();
    };
    //HAL_GPIO_WritePin(TIMER_check_GPIO_Port, TIMER_check_Pin, GPIO_PIN_RESET);
}