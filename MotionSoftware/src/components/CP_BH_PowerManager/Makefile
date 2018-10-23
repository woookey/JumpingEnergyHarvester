CUR_DIR = $(shell pwd)
KERNEL_DIR = ${CUR_DIR}/../../kernel
CP_HD_LED_DIR = ${CUR_DIR}/../CP_HD_LEDDriver
SYSTEM_DIR = ${CUR_DIR}/../../system

CFLAGS = -Wall -g -I. -c 
CPU_CONFIG = --specs=nosys.specs -mthumb -mcpu=cortex-m4
INCLUDE_DIR = -I${KERNEL_DIR}
INCLUDE_DIR += -I${CP_HD_LED_DIR}
INCLUDE_DIR += -I${SYSTEM_DIR}

OBJS = ${KERNEL_DIR}/RF_agents.o
OBJS += ${KERNEL_DIR}/RF_events.o
OBJS += ${KERNEL_DIR}/RF_queue.o

ifeq (${CC}, arm-none-eabi-gcc)
	OBJS += ${CP_HD_LED_DIR}/CP_HD_LEDDriver.c
	CFLAGS += ${CPU_CONFIG}
endif

#test: LEDManager.o
#	cd ${CUR_DIR}/tests; make test

CP_BH_PowerManager.o: CP_BH_PowerManager.c CP_BH_PowerManager.h ${OBJS}  
	${CC} ${CFLAGS} ${INCLUDE_DIR} CP_BH_PowerManager.c

clean:
	rm -rf *.o *~
	#cd ${CUR_DIR}/tests; make clean