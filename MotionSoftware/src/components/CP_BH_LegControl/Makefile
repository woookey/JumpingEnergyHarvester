CUR_DIR = $(shell pwd)
KERNEL_DIR = ${CUR_DIR}/../../kernel
SYSTEM_DIR = ${CUR_DIR}/../../system

CFLAGS = -Wall -g -I. -c 
CPU_CONFIG = --specs=nosys.specs -mthumb -mcpu=cortex-m4
INCLUDE_DIR = -I${KERNEL_DIR}
INCLUDE_DIR += -I${SYSTEM_DIR}
INCLUDE_DIR += -I${CUR_DIR}/../CP_HD_MotorControlBoard/

OBJS = ${KERNEL_DIR}/RF_agents.o
OBJS += ${KERNEL_DIR}/RF_events.o
OBJS += ${KERNEL_DIR}/RF_queue.o
OBJS += ${KERNEL_DIR}/RF_timers.o

ifeq (${CC}, arm-none-eabi-gcc)
	OBJS += ${CUR_DIR}/../CP_HD_MotorControlBoard/CP_HD_MotorControlBoard.o
	CFLAGS += ${CPU_CONFIG}
endif

CP_BH_LegControl.o: CP_BH_LegControl.c CP_BH_LegControl.h ${OBJS}  
	${CC} ${CFLAGS} ${INCLUDE_DIR} CP_BH_LegControl.c

clean:
	rm -rf *.o *~