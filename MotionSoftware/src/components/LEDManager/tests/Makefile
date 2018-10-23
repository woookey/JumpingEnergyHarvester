CUR_DIR = $(shell pwd)
UNITY_DIR = ${CUR_DIR}/../../../testing/Unity
TESTING_UTILS_DIR = ${CUR_DIR}/../../../testing/testingUtilities
LED_MANAGER_DIR = ${CUR_DIR}/..
KERNEL_DIR = ${CUR_DIR}/../../../kernel
SYSTEM_DIR = ${CUR_DIR}/../../../system
CP_HD_LED_DIR = ${CUR_DIR}/../../CP_HD_LEDDriver

KERNEL_OBJS = ${KERNEL_DIR}/RF_scheduler.o ${KERNEL_DIR}/RF_dispatcher.o
KERNEL_OBJS += ${KERNEL_DIR}/RF_queue.o ${KERNEL_DIR}/RF_events.o 
KERNEL_OBJS += ${KERNEL_DIR}/RF_agents.o ${KERNEL_DIR}/RF_timers.o
KERNEL_OBJS += ${KERNEL_DIR}/RF_porting.o

OBJS = test.c 
OBJS += ${UNITY_DIR}/unity.c 
OBJS += ${TESTING_UTILS_DIR}/testing_utils.c
OBJS += ${LED_MANAGER_DIR}/LEDManager.c
OBJS += ${CP_HD_LED_DIR}/mock/CP_HD_LEDDriver_mock.c

INC_DIR = -I. 
INC_DIR += -I${UNITY_DIR} 
INC_DIR += -I${LED_MANAGER_DIR} 
INC_DIR += -I${KERNEL_DIR} 
INC_DIR += -I${SYSTEM_DIR}
INC_DIR += -I${CP_HD_LED_DIR}
INC_DIR += -I${CP_HD_LED_DIR}/mock
INC_DIR += -I${TESTING_UTILS_DIR}

CC = gcc
CFLAGS = -Wall -g -I. -I${UNITY_DIR}
 
test: 
	make CP_LEDManager_UnitTest
	./CP_LEDManager_UnitTest

CP_LEDManager_UnitTest: ${OBJS} ${LED_MANAGER_DIR}/LEDManager.o ${KERNEL_OBJS} 
	${CC} ${CFLAGS} ${INC_DIR} ${OBJS} ${KERNEL_OBJS} -o CP_LEDManager_UnitTest
	
clean:
	rm -rf *.o *~
	rm -rf CP_LEDManager_UnitTest
