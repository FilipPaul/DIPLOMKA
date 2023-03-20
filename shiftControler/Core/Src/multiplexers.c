#include "multiplexers.h"
#include "stdio.h"



GPIO_PinState MUXreadAdress(uint8_t address, Multiplexer* mux){
  HAL_GPIO_WritePin(mux->A0_port, mux->A0_pin, (((address % mux->mux_length) >> 0) & 0x01));
  HAL_GPIO_WritePin(mux->A1_port, mux->A1_pin, (((address % mux->mux_length) >> 1) & 0x01));
  HAL_GPIO_WritePin(mux->A2_port, mux->A2_pin, (((address % mux->mux_length) >> 2) & 0x01));
  _2500_ns_delay(DELAY_MULTIPLES_OF_2500_NS);
  return HAL_GPIO_ReadPin(mux->data_out_ports[address / mux->mux_length ], mux->data_out_pins[address / mux->mux_length]);
}

uint32_t MUXreadAll(Multiplexer* mux){
  uint32_t data = 0;
  for(uint8_t i = 0; i < mux->mux_length*mux->number_of_paralel_muxes; i++){
    data |= ((uint32_t)MUXreadAdress(i, mux) << i);
  }
  return data;
}
