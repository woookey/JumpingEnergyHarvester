CUR_DIR = $(shell pwd)

OBJS = CP_HD_Logger.c
CFLAGS = -Wall -g -I. -c
CPU_CONFIG = --specs=nosys.specs -mthumb -mcpu=cortex-m4

INC_DIR = -I${CUR_DIR}/../CP_HA_UART/

ifeq (${CC}, arm-none-eabi-gcc)
	INC_DIR += -I${CUR_DIR}/../CP_HA_UART/target/ 
	#INC_DIR += -I${CUR_DIR}/../../lib/CMSIS/Device/ST/STM32F4xx/Include
	#INC_DIR += -I${CUR_DIR}/../../lib/CMSIS/Include
	#INC_DIR += -I${CUR_DIR}/../../lib/STM32F4xx_HAL_Driver/Inc
	CFLAGS += -DSTM32F407xx
	CFLAGS += ${CPU_CONFIG}
else
	INC_DIR += -I${CUR_DIR}/../CP_HA_UART/synthetic/
endif

CP_HD_Logger.o: CP_HD_Logger.c
	${CC} ${CFLAGS} ${INC_DIR} ${OBJS} -o CP_HD_Logger.o

clean:
	rm -rf *.o *.~