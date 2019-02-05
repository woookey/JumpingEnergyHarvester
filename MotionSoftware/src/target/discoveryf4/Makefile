CUR_DIR = $(shell pwd)
CC_TARGET = arm-none-eabi-gcc
CC_SYNTHETIC = gcc
CC_CONFIG = -g -Wall
CPU_CONFIG = --specs=nosys.specs -mthumb -mcpu=cortex-m4
RF_KERNEL_DIR = ${CUR_DIR}/../../kernel
CMSIS_CORE_INC_PATH = ${CUR_DIR}/../../lib/CMSIS/Include/
CMSIS_STM32F4XX_INC_PATH = ${CUR_DIR}/../../lib/CMSIS/Device/ST/STM32F4xx/Include/
CMSIS_STARTUP_INC_PATH = ${CUR_DIR}/../../lib/CMSIS/Device/ST/STM32F4xx/Source/Templates/gcc
CMSIS_SYSTEM_CONFIG_INC_PATH = ${CUR_DIR}/../../lib/CMSIS/Device/ST/STM32F4xx/Source/Templates
STM32_HAL_DRIVER_INC_PATH = ${CUR_DIR}/../../lib/STM32F4xx_HAL_Driver/Inc/
STM32_HAL_DRIVER_SRC_PATH = ${CUR_DIR}/../../lib/STM32F4xx_HAL_Driver/Src
CFLAGS = -I ${CMSIS_CORE_INC_PATH} -I ${CMSIS_STM32F4XX_INC_PATH} -I${RF_KERNEL_DIR}
CFLAGS += -I ${STM32_HAL_DRIVER_INC_PATH}
LINKER_SCRIPT = STM32F407VGTx_FLASH.ld
LINKER_PATH = ${CUR_DIR}/../../lib/STM32F407_Linker/
LFLAGS = -T ${LINKER_SCRIPT} -L ${LINKER_PATH}
DEFS = -DHSE_VALUE=8000000 -DSTM32F407xx

INCLUDE_DIRS = -I./
INCLUDE_DIRS += -I../../components/LEDManager/
INCLUDE_DIRS += -I../../components/CP_BH_PowerManager/
INCLUDE_DIRS += -I../../components/CP_HD_LEDDriver/
INCLUDE_DIRS += -I../../components/CP_HA_LED/
INCLUDE_DIRS += -I../../components/CP_HA_HardwareSetup/
INCLUDE_DIRS += -I../../components/CP_BH_LegControl/
INCLUDE_DIRS += -I../../components/CP_HD_MotorControlBoard/
INCLUDE_DIRS += -I../../components/CP_BH_LoggingManager/
INCLUDE_DIRS += -I../../components/CP_HA_GPIO/
INCLUDE_DIRS += -I../../components/CP_HA_PWM/
INCLUDE_DIRS += -I../../components/CP_HD_Logger/
INCLUDE_DIRS += -I../../components/CP_HA_UART/
INCLUDE_DIRS += -I../../system/
INCLUDE_DIRS += -I../../kernel/

HAL_SRC = ${STM32_HAL_DRIVER_SRC_PATH}/stm32f4xx_hal_rcc.c 
HAL_SRC += ${STM32_HAL_DRIVER_SRC_PATH}/stm32f4xx_hal.c 
HAL_SRC += ${STM32_HAL_DRIVER_SRC_PATH}/stm32f4xx_hal_gpio.c 
HAL_SRC += ${STM32_HAL_DRIVER_SRC_PATH}/stm32f4xx_hal_cortex.c 
HAL_SRC += ${STM32_HAL_DRIVER_SRC_PATH}/stm32f4xx_hal_tim.c
HAL_SRC += ${STM32_HAL_DRIVER_SRC_PATH}/stm32f4xx_hal_tim_ex.c 
HAL_SRC += ${STM32_HAL_DRIVER_SRC_PATH}/stm32f4xx_hal_dma.c

DEPENDENCIES += ../../components/LEDManager/LEDManager.o
DEPENDENCIES += ../../components/CP_BH_PowerManager/CP_BH_PowerManager.o
DEPENDENCIES += ../../components/CP_HD_LEDDriver/CP_HD_LEDDriver.o
DEPENDENCIES += ../../components/CP_HA_LED/CP_HA_LED.o
DEPENDENCIES += ../../components/CP_HA_HardwareSetup/CP_HA_HardwareSetup.o
DEPENDENCIES += ../../components/CP_BH_LegControl/CP_BH_LegControl.o
DEPENDENCIES += ../../components/CP_HD_MotorControlBoard/CP_HD_MotorControlBoard.o
DEPENDENCIES += ../../components/CP_HA_GPIO/CP_HA_GPIO.o
DEPENDENCIES += ../../components/CP_HA_PWM/CP_HA_PWM.o
DEPENDENCIES += ../../components/CP_BH_LoggingManager/CP_BH_LoggingManager.o
DEPENDENCIES += ../../components/CP_HD_Logger/CP_HD_Logger.o
DEPENDENCIES += ../../components/CP_HA_UART/CP_HA_UART.o

KERNEL_OBJS = ${RF_KERNEL_DIR}/RF_porting.o
KERNEL_OBJS += ${RF_KERNEL_DIR}/RF_queue.o
KERNEL_OBJS += ${RF_KERNEL_DIR}/RF_events.o
KERNEL_OBJS += ${RF_KERNEL_DIR}/RF_scheduler.o
KERNEL_OBJS += ${RF_KERNEL_DIR}/RF_dispatcher.o
KERNEL_OBJS += ${RF_KERNEL_DIR}/RF_agents.o
KERNEL_OBJS += ${RF_KERNEL_DIR}/RF_timers.o


build_target: ${DEPENDENCIES} ${KERNEL_OBJS} 
	${CC_TARGET} ${CC_CONFIG} ${CPU_CONFIG} -Os \
	${CFLAGS} ${INCLUDE_DIRS} ${LFLAGS} ${CMSIS_STARTUP_INC_PATH}/startup_stm32f407xx.s \
	${DEPENDENCIES} ${KERNEL_OBJS} ARM_main.c ${CMSIS_SYSTEM_CONFIG_INC_PATH}/system_stm32f4xx.c \
	${HAL_SRC} ${DEFS} -o ARM_main.axf;
	arm-none-eabi-objcopy -O binary ARM_main.axf ARM_main.bin
	
build_synthetic: ${DEPENDENCIES} ${KERNEL_OBJS} 
	${CC_SYNTHETIC} -g -Wall ${CFLAGS} ${INCLUDE_DIRS} \
	${DEPENDENCIES} ${KERNEL_OBJS} ARM_main.c -o ARM_main	
	
system:
	${CC_TARGET} ${CC_CONFIG} ${CPU_CONFIG} -I../../lib/CMSIS/Include/ -I ../../lib/CMSIS/Device/ST/STM32F4xx/Include/ ${DEFS} -Os -c ../../lib/CMSIS/Device/ST/STM32F4xx/Source/Templates/system_stm32f4xx.c -o system.o

startup:
	${CC_TARGET} ${CC_CONFIG} ${CPU_CONFIG} -I../../lib/CMSIS/Include/ -I ../../lib/CMSIS/Device/ST/STM32F4xx/Include/ ${DEFS} -Os -c ../../lib/CMSIS/Device/ST/STM32F4xx/Source/Templates/gcc/startup_stm32f407xx.s -o startup.o
	
clean:
	rm -rf *~ *.axf *.bin ARM_main_synth *o ARM_main
	
	