##########################################################################################################################
# File automatically-generated by STM32forVSCode
##########################################################################################################################

# ------------------------------------------------
# Generic Makefile (based on gcc)
#
# ChangeLog :
#	2017-02-10 - Several enhancements + project update mode
#   2015-07-22 - first version
# ------------------------------------------------

######################################
# target
######################################
TARGET = shiftControler


######################################
# building variables
######################################
# debug build?
DEBUG = 1
# optimization
OPT = -Og


#######################################
# paths
#######################################
# Build path
BUILD_DIR = build

######################################
# source
######################################
# C sources
C_SOURCES =  \
Core/Src/commandParser.c \
Core/Src/freertos.c \
Core/Src/globals.c \
Core/Src/main.c \
Core/Src/module80IOcard.c \
Core/Src/multiplexers.c \
Core/Src/shiftRegisters.c \
Core/Src/stm32f4xx_hal_msp.c \
Core/Src/stm32f4xx_hal_timebase_tim.c \
Core/Src/stm32f4xx_it.c \
Core/Src/system_stm32f4xx.c \
Core/Src/tcpserver.c \
Drivers/BSP/Components/lan8742/lan8742.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_cortex.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dac.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dac_ex.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma_ex.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_eth.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_exti.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ex.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ramfunc.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_gpio.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pcd.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pcd_ex.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr_ex.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc_ex.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim_ex.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_uart.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_usb.c \
LWIP/App/lwip.c \
LWIP/Target/ethernetif.c \
Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS/cmsis_os.c \
Middlewares/Third_Party/FreeRTOS/Source/croutine.c \
Middlewares/Third_Party/FreeRTOS/Source/event_groups.c \
Middlewares/Third_Party/FreeRTOS/Source/list.c \
Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F/port.c \
Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/heap_4.c \
Middlewares/Third_Party/FreeRTOS/Source/queue.c \
Middlewares/Third_Party/FreeRTOS/Source/stream_buffer.c \
Middlewares/Third_Party/FreeRTOS/Source/tasks.c \
Middlewares/Third_Party/FreeRTOS/Source/timers.c \
Middlewares/Third_Party/LwIP/src/api/api_lib.c \
Middlewares/Third_Party/LwIP/src/api/api_msg.c \
Middlewares/Third_Party/LwIP/src/api/err.c \
Middlewares/Third_Party/LwIP/src/api/if_api.c \
Middlewares/Third_Party/LwIP/src/api/netbuf.c \
Middlewares/Third_Party/LwIP/src/api/netdb.c \
Middlewares/Third_Party/LwIP/src/api/netifapi.c \
Middlewares/Third_Party/LwIP/src/api/sockets.c \
Middlewares/Third_Party/LwIP/src/api/tcpip.c \
Middlewares/Third_Party/LwIP/src/apps/mqtt/mqtt.c \
Middlewares/Third_Party/LwIP/src/core/altcp.c \
Middlewares/Third_Party/LwIP/src/core/altcp_alloc.c \
Middlewares/Third_Party/LwIP/src/core/altcp_tcp.c \
Middlewares/Third_Party/LwIP/src/core/def.c \
Middlewares/Third_Party/LwIP/src/core/dns.c \
Middlewares/Third_Party/LwIP/src/core/inet_chksum.c \
Middlewares/Third_Party/LwIP/src/core/init.c \
Middlewares/Third_Party/LwIP/src/core/ip.c \
Middlewares/Third_Party/LwIP/src/core/ipv4/autoip.c \
Middlewares/Third_Party/LwIP/src/core/ipv4/dhcp.c \
Middlewares/Third_Party/LwIP/src/core/ipv4/etharp.c \
Middlewares/Third_Party/LwIP/src/core/ipv4/icmp.c \
Middlewares/Third_Party/LwIP/src/core/ipv4/igmp.c \
Middlewares/Third_Party/LwIP/src/core/ipv4/ip4.c \
Middlewares/Third_Party/LwIP/src/core/ipv4/ip4_addr.c \
Middlewares/Third_Party/LwIP/src/core/ipv4/ip4_frag.c \
Middlewares/Third_Party/LwIP/src/core/ipv6/dhcp6.c \
Middlewares/Third_Party/LwIP/src/core/ipv6/ethip6.c \
Middlewares/Third_Party/LwIP/src/core/ipv6/icmp6.c \
Middlewares/Third_Party/LwIP/src/core/ipv6/inet6.c \
Middlewares/Third_Party/LwIP/src/core/ipv6/ip6.c \
Middlewares/Third_Party/LwIP/src/core/ipv6/ip6_addr.c \
Middlewares/Third_Party/LwIP/src/core/ipv6/ip6_frag.c \
Middlewares/Third_Party/LwIP/src/core/ipv6/mld6.c \
Middlewares/Third_Party/LwIP/src/core/ipv6/nd6.c \
Middlewares/Third_Party/LwIP/src/core/mem.c \
Middlewares/Third_Party/LwIP/src/core/memp.c \
Middlewares/Third_Party/LwIP/src/core/netif.c \
Middlewares/Third_Party/LwIP/src/core/pbuf.c \
Middlewares/Third_Party/LwIP/src/core/raw.c \
Middlewares/Third_Party/LwIP/src/core/stats.c \
Middlewares/Third_Party/LwIP/src/core/sys.c \
Middlewares/Third_Party/LwIP/src/core/tcp.c \
Middlewares/Third_Party/LwIP/src/core/tcp_in.c \
Middlewares/Third_Party/LwIP/src/core/tcp_out.c \
Middlewares/Third_Party/LwIP/src/core/timeouts.c \
Middlewares/Third_Party/LwIP/src/core/udp.c \
Middlewares/Third_Party/LwIP/src/netif/bridgeif.c \
Middlewares/Third_Party/LwIP/src/netif/bridgeif_fdb.c \
Middlewares/Third_Party/LwIP/src/netif/ethernet.c \
Middlewares/Third_Party/LwIP/src/netif/lowpan6.c \
Middlewares/Third_Party/LwIP/src/netif/lowpan6_ble.c \
Middlewares/Third_Party/LwIP/src/netif/lowpan6_common.c \
Middlewares/Third_Party/LwIP/src/netif/ppp/auth.c \
Middlewares/Third_Party/LwIP/src/netif/ppp/ccp.c \
Middlewares/Third_Party/LwIP/src/netif/ppp/chap-md5.c \
Middlewares/Third_Party/LwIP/src/netif/ppp/chap-new.c \
Middlewares/Third_Party/LwIP/src/netif/ppp/chap_ms.c \
Middlewares/Third_Party/LwIP/src/netif/ppp/demand.c \
Middlewares/Third_Party/LwIP/src/netif/ppp/eap.c \
Middlewares/Third_Party/LwIP/src/netif/ppp/ecp.c \
Middlewares/Third_Party/LwIP/src/netif/ppp/eui64.c \
Middlewares/Third_Party/LwIP/src/netif/ppp/fsm.c \
Middlewares/Third_Party/LwIP/src/netif/ppp/ipcp.c \
Middlewares/Third_Party/LwIP/src/netif/ppp/ipv6cp.c \
Middlewares/Third_Party/LwIP/src/netif/ppp/lcp.c \
Middlewares/Third_Party/LwIP/src/netif/ppp/magic.c \
Middlewares/Third_Party/LwIP/src/netif/ppp/mppe.c \
Middlewares/Third_Party/LwIP/src/netif/ppp/multilink.c \
Middlewares/Third_Party/LwIP/src/netif/ppp/ppp.c \
Middlewares/Third_Party/LwIP/src/netif/ppp/pppapi.c \
Middlewares/Third_Party/LwIP/src/netif/ppp/pppcrypt.c \
Middlewares/Third_Party/LwIP/src/netif/ppp/pppoe.c \
Middlewares/Third_Party/LwIP/src/netif/ppp/pppol2tp.c \
Middlewares/Third_Party/LwIP/src/netif/ppp/pppos.c \
Middlewares/Third_Party/LwIP/src/netif/ppp/upap.c \
Middlewares/Third_Party/LwIP/src/netif/ppp/utils.c \
Middlewares/Third_Party/LwIP/src/netif/ppp/vj.c \
Middlewares/Third_Party/LwIP/src/netif/slipif.c \
Middlewares/Third_Party/LwIP/src/netif/zepif.c \
Middlewares/Third_Party/LwIP/system/OS/sys_arch.c


CPP_SOURCES = \


# ASM sources
ASM_SOURCES =  \
startup_stm32f429xx.s



#######################################
# binaries
#######################################
PREFIX = arm-none-eabi-
POSTFIX = "
# The gcc compiler bin path can be either defined in make command via GCC_PATH variable (> make GCC_PATH=xxx)
# either it can be added to the PATH environment variable.
GCC_PATH="C:/ARM_TOOLS/COMPILER/GCC-ARM-NONE-EABI-10.3-2021.10/BIN
ifdef GCC_PATH
CXX = $(GCC_PATH)/$(PREFIX)g++$(POSTFIX)
CC = $(GCC_PATH)/$(PREFIX)gcc$(POSTFIX)
AS = $(GCC_PATH)/$(PREFIX)gcc$(POSTFIX) -x assembler-with-cpp
CP = $(GCC_PATH)/$(PREFIX)objcopy$(POSTFIX)
SZ = $(GCC_PATH)/$(PREFIX)size$(POSTFIX)
else
CXX = $(PREFIX)g++
CC = $(PREFIX)gcc
AS = $(PREFIX)gcc -x assembler-with-cpp
CP = $(PREFIX)objcopy
SZ = $(PREFIX)size
endif
HEX = $(CP) -O ihex
BIN = $(CP) -O binary -S

#######################################
# CFLAGS
#######################################
# cpu
CPU = -mcpu=cortex-m4

# fpu
FPU = -mfpu=fpv4-sp-d16

# float-abi
FLOAT-ABI = -mfloat-abi=hard

# mcu
MCU = $(CPU) -mthumb $(FPU) $(FLOAT-ABI)

# macros for gcc
# AS defines
AS_DEFS = 

# C defines
C_DEFS =  \
-DSTM32F429xx \
-DUSE_HAL_DRIVER


# CXX defines
CXX_DEFS =  \
-DSTM32F429xx \
-DUSE_HAL_DRIVER


# AS includes
AS_INCLUDES = \

# C includes
C_INCLUDES =  \
-ICore/Inc \
-IDrivers/BSP/Components/lan8742 \
-IDrivers/CMSIS/Device/ST/STM32F4xx/Include \
-IDrivers/CMSIS/Include \
-IDrivers/STM32F4xx_HAL_Driver/Inc \
-IDrivers/STM32F4xx_HAL_Driver/Inc/Legacy \
-ILWIP/App \
-ILWIP/Target \
-IMiddlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS \
-IMiddlewares/Third_Party/FreeRTOS/Source/include \
-IMiddlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F \
-IMiddlewares/Third_Party/LwIP/src/include \
-IMiddlewares/Third_Party/LwIP/src/include/compat/posix \
-IMiddlewares/Third_Party/LwIP/src/include/compat/posix/arpa \
-IMiddlewares/Third_Party/LwIP/src/include/compat/posix/net \
-IMiddlewares/Third_Party/LwIP/src/include/compat/posix/sys \
-IMiddlewares/Third_Party/LwIP/src/include/compat/stdc \
-IMiddlewares/Third_Party/LwIP/src/include/lwip \
-IMiddlewares/Third_Party/LwIP/src/include/lwip/apps \
-IMiddlewares/Third_Party/LwIP/src/include/lwip/priv \
-IMiddlewares/Third_Party/LwIP/src/include/lwip/prot \
-IMiddlewares/Third_Party/LwIP/src/include/netif \
-IMiddlewares/Third_Party/LwIP/src/include/netif/ppp \
-IMiddlewares/Third_Party/LwIP/system \
-IMiddlewares/Third_Party/LwIP/system/arch



# compile gcc flags
ASFLAGS = $(MCU) $(AS_DEFS) $(AS_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections

CFLAGS = $(MCU) $(C_DEFS) $(C_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections

CXXFLAGS = $(MCU) $(CXX_DEFS) $(C_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections -feliminate-unused-debug-types

ifeq ($(DEBUG), 1)
CFLAGS += -g -gdwarf -ggdb
CXXFLAGS += -g -gdwarf -ggdb
endif

# Add additional flags
CFLAGS += 
ASFLAGS += 
CXXFLAGS += 

# Generate dependency information
CFLAGS += -MMD -MP -MF"$(@:%.o=%.d)"
CXXFLAGS += -MMD -MP -MF"$(@:%.o=%.d)"

#######################################
# LDFLAGS
#######################################
# link script
LDSCRIPT = STM32F429ZITx_FLASH.ld

# libraries
LIBS = -lc -lm -lnosys 
LIBDIR = \


# Additional LD Flags from config file
ADDITIONALLDFLAGS = -specs=nano.specs -u _printf_float 

LDFLAGS = $(MCU) $(ADDITIONALLDFLAGS) -T$(LDSCRIPT) $(LIBDIR) $(LIBS) -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--cref -Wl,--gc-sections

# default action: build all
all: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).hex $(BUILD_DIR)/$(TARGET).bin


#######################################
# build the application
#######################################
# list of cpp program objects
OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(CPP_SOURCES:.cpp=.o)))
vpath %.cpp $(sort $(dir $(CPP_SOURCES)))

# list of C objects
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(C_SOURCES)))
# list of ASM program objects
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(ASM_SOURCES:.s=.o)))
vpath %.s $(sort $(dir $(ASM_SOURCES)))

$(BUILD_DIR)/%.o: %.cpp STM32Make.make | $(BUILD_DIR) 
	$(CXX) -c $(CXXFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.cpp=.lst)) $< -o $@

$(BUILD_DIR)/%.o: %.cxx STM32Make.make | $(BUILD_DIR) 
	$(CXX) -c $(CXXFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.cxx=.lst)) $< -o $@

$(BUILD_DIR)/%.o: %.c STM32Make.make | $(BUILD_DIR) 
	$(CC) -c $(CFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst)) $< -o $@

$(BUILD_DIR)/%.o: %.s STM32Make.make | $(BUILD_DIR)
	$(AS) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS) STM32Make.make
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@
	$(SZ) $@

$(BUILD_DIR)/%.hex: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(HEX) $< $@

$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(BIN) $< $@

$(BUILD_DIR):
	mkdir $@

#######################################
# flash
#######################################
flash: $(BUILD_DIR)/$(TARGET).elf
	"C:/ARM_TOOLS/DEBUGER/OPENOCD-20211118-0.11.0/BIN/OPENOCD.EXE" -f ./openocd.cfg -c "program $(BUILD_DIR)/$(TARGET).elf verify reset exit"

#######################################
# erase
#######################################
erase: $(BUILD_DIR)/$(TARGET).elf
	"C:/ARM_TOOLS/DEBUGER/OPENOCD-20211118-0.11.0/BIN/OPENOCD.EXE" -f ./openocd.cfg -c "init; reset halt; stm32f4x mass_erase 0; exit"

#######################################
# clean up
#######################################
clean:
	cmd /c rd /s /q $(BUILD_DIR)

#######################################
# custom makefile rules
#######################################


	
#######################################
# dependencies
#######################################
-include $(wildcard $(BUILD_DIR)/*.d)

# *** EOF ***