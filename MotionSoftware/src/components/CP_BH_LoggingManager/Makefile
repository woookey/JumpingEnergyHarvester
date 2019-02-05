CUR_DIR = $(shell pwd)
KERNEL_DIR = ${CUR_DIR}/../../kernel
SYSTEM_DIR = ${CUR_DIR}/../../system

CFLAGS = -Wall -g -I. -c 
CPU_CONFIG = --specs=nosys.specs -mthumb -mcpu=cortex-m4
INCLUDE_DIR = -I${KERNEL_DIR}
INCLUDE_DIR += -I${SYSTEM_DIR}

OBJS = ${KERNEL_DIR}/RF_agents.o
OBJS += ${KERNEL_DIR}/RF_events.o
OBJS += ${KERNEL_DIR}/RF_queue.o

ifeq (${CC}, arm-none-eabi-gcc)
	CFLAGS += ${CPU_CONFIG}
endif

CP_BH_LoggingManager.o: CP_BH_LoggingManager.c CP_BH_LoggingManager.h ${OBJS}  
	${CC} ${CFLAGS} ${INCLUDE_DIR} CP_BH_LoggingManager.c

clean:
	rm -rf *.o *~