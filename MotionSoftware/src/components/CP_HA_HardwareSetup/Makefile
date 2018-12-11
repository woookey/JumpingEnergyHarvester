CUR_DIR = $(shell pwd)
CFLAGS = -Wall -g -c -I.

CPU_CONFIG = --specs=nosys.specs -mthumb -mcpu=cortex-m4

CMSIS_SYSTEM_CONFIG_INC_PATH = ${CUR_DIR}/../../lib/CMSIS/Device/ST/STM32F4xx/Source/Templates
STM32_HAL_DRIVER_SRC_PATH = ${CUR_DIR}/../../lib/STM32F4xx_HAL_Driver/Src


ifeq (${CC}, arm-none-eabi-gcc)
	INC_DIR = -I${CUR_DIR}/target
	INC_DIR += -I${CUR_DIR}
	INC_DIR += -I${CUR_DIR}/../../lib/STM32F4xx_HAL_Driver/Inc
	INC_DIR += -I${CUR_DIR}/../../lib/CMSIS/Device/ST/STM32F4xx/Include
	INC_DIR += -I${CUR_DIR}/../../lib/CMSIS/Include
	INC_DIR += -I${CUR_DIR}/../../kernel
	CFLAGS += -DSTM32F407xx 
	CFLAGS += ${CPU_CONFIG}
	
	OBJS = ${CUR_DIR}/target/CP_HA_HardwareSetup.c
	OBJS += ${STM32_HAL_DRIVER_SRC_PATH}/stm32f4xx_hal_rcc.c 
	OBJS += ${STM32_HAL_DRIVER_SRC_PATH}/stm32f4xx_hal.c
	OBJS += ${STM32_HAL_DRIVER_SRC_PATH}/stm32f4xx_hal_gpio.c
	OBJS += ${STM32_HAL_DRIVER_SRC_PATH}/stm32f4xx_hal_cortex.c
	OBJS += ${CMSIS_SYSTEM_CONFIG_INC_PATH}/system_stm32f4xx.c
else
	INC_DIR = -I${CUR_DIR}/synthetic
	OBJS = ${CUR_DIR}/synthetic/CP_HA_HardwareSetup.c
endif

CP_HA_HardwareSetup.o: ${OBJS} 
	${CC} ${CFLAGS} ${DEPENDENCIES} ${INC_DIR} ${OBJS}
	
clean:
	rm -rf *.o *.~ 