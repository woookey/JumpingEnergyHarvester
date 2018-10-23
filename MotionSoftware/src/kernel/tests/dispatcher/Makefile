CUR_DIR = $(shell pwd)
RF_DIR = ${CUR_DIR}/../../
UNITY_DIR = ${CUR_DIR}/../../../testing/Unity
TEST_UTIL_DIR = ${CUR_DIR}/../../../testing/testingUtilities
RF_OBJS = RF_dispatcher.o RF_queue.o RF_events.o RF_agents.o
OBJS = test.o unity.o testing_utils.o
CC = gcc
CFLAGS = -Wall -g -I${RF_DIR} -I${UNITY_DIR} -I${TEST_UTIL_DIR} -c 
LFLAGS = -Wall -g -I. -I${RF_DIR}

test:
	make RF_dispatcherUnitTest
	./RF_dispatcher_UnitTest

RF_dispatcherUnitTest: ${OBJS} ${RF_OBJS}
	${CC} ${LFLAGS} ${OBJS} ${RF_OBJS} -o RF_dispatcher_UnitTest
	
testing_utils.o: ${TEST_UTIL_DIR}/testing_utils.c ${TEST_UTIL_DIR}/testing_utils.h
	${CC} ${CFLAGS} ${TEST_UTIL_DIR}/testing_utils.c
	
unity.o: ${UNITY_DIR}/unity.c ${UNITY_DIR}/unity.h
	${CC} ${CFLAGS} ${UNITY_DIR}/unity.c 
	
test.o: test.c
	${CC} ${CFLAGS} test.c

RF_dispatcher.o: ${RF_DIR}/RF_dispatcher.c ${RF_DIR}/RF_dispatcher.h ${RF_DIR}/RF_queue.o ${RF_DIR}/RF_agents.o
	${CC} ${CFLAGS} ${RF_DIR}/RF_dispatcher.c
	
RF_agents.o: ${RF_DIR}/RF_agents.c ${RF_DIR}/RF_agents.h ${RF_DIR}/RF_events.o ${RF_DIR}/RF_queue.o
	${CC} ${CFLAGS} ${RF_DIR}/RF_agents.c
	
RF_queue.o: ${RF_DIR}/RF_events.o ${RF_DIR}/RF_queue.c ${RF_DIR}/RF_queue.h
	${CC} ${CFLAGS} ${RF_DIR}/RF_queue.c
	
RF_events.o: ${RF_DIR}/RF_events.c ${RF_DIR}/RF_events.h
	${CC} ${CFLAGS} ${RF_DIR}/RF_events.c

clean:
	rm -rf *.o *~ RF_dispatcher_UnitTest
