CUR_DIR = $(shell pwd)
RF_DIR = ${CUR_DIR}/../../
UNITY_DIR = ${CUR_DIR}/../../../testing/Unity
RF_OBJS = RF_events.o RF_queue.o
OBJS = test.o unity.o
CC = gcc
CFLAGS = -Wall -g -I${RF_DIR} -I${UNITY_DIR} -c 
LFLAGS = -Wall -g -I.

test:
	make RF_queueUnitTest
	./RF_queue_UnitTest
	
RF_queueUnitTest: ${OBJS} ${RF_OBJS}
	${CC} ${LFLAGS} ${OBJS} ${RF_OBJS} -o RF_queue_UnitTest
	
unity.o: ${UNITY_DIR}/unity.c ${UNITY_DIR}/unity.h
	${CC} ${CFLAGS} ${UNITY_DIR}/unity.c 

test.o: test.c RF_queue.o RF_events.o
	${CC} ${CFLAGS} test.c

RF_queue.o: RF_events.o ${RF_DIR}/RF_queue.c ${RF_DIR}/RF_queue.h
	${CC} ${CFLAGS} ${RF_DIR}/RF_queue.c
	
RF_events.o: ${RF_DIR}/RF_events.c ${RF_DIR}/RF_events.h
	${CC} ${CFLAGS} ${RF_DIR}/RF_events.c

clean:
	rm -rf *.o *~ RF_queue_UnitTest
