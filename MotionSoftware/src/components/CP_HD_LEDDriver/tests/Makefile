CUR_DIR = $(shell pwd)

UNITY_DIR = ${CUR_DIR}/../../../testing/Unity
CP_HD_LEDDRIVER_DIR = ${CUR_DIR}/..
CP_HA_MOCK_DIR = ${CUR_DIR}/../../CP_HA_LED/mock

INC_DIR = -I${CUR_DIR}/../../../testing/Unity
INC_DIR += -I${CUR_DIR}/../
INC_DIR += -I${CUR_DIR}/../../CP_HA_LED/
INC_DIR += -I${CUR_DIR}/../../CP_HA_LED/mock

OBJS = test.o ${UNITY_DIR}/unity.o ${CP_HD_LEDDRIVER_DIR}/CP_HD_LEDDriver.o ${CP_HA_MOCK_DIR}/mock.o
CC = gcc

CFLAGS = -Wall -g ${INC_DIR} -c 
LFLAGS = -Wall -g -I. -I${INC_DIR}

test:
	make CP_HD_LEDDriver_UnitTest
	./CP_HD_LEDDriver_UnitTest

CP_HD_LEDDriver_UnitTest: ${OBJS}
	${CC} ${LFLAGS} ${OBJS} -o CP_HD_LEDDriver_UnitTest
	
mock.o: ${CP_HA_MOCK_DIR}/mock.c
	${CC} ${CFLAGS} ${CP_HA_MOCK_DIR}/mock.c
	
unity.o: ${UNITY_DIR}/unity.c ${UNITY_DIR}/unity.h
	${CC} ${CFLAGS} ${UNITY_DIR}/unity.c 
	
test.o: test.c
	${CC} ${CFLAGS} test.c

clean:
	rm -rf *.o *~ CP_HD_LEDDriver_UnitTest
