RF_OBJS = RF_porting.o RF_agents.o RF_scheduler.o RF_events.o RF_queue.o RF_dispatcher.o RF_timers.o 
CFLAGS = -Wall -g -I. -c
LFLAGS = -Wall -I.
CPU_CONFIG = --specs=nosys.specs -mthumb -mcpu=cortex-m4

ifeq (${CC}, arm-none-eabi-gcc)
	CFLAGS += ${CPU_CONFIG}
endif

RF_kernel: ${RF_OBJS}

RF_scheduler.o: RF_agents.o RF_scheduler.h RF_scheduler.c RF_events.o RF_queue.o RF_porting.o
	${CC} ${CFLAGS} RF_scheduler.c
	
RF_dispatcher.o: RF_agents.o RF_queue.o RF_events.o RF_dispatcher.h RF_dispatcher.c RF_definitions.h RF_porting.o
	${CC} ${CFLAGS} RF_dispatcher.c

RF_timers.o: RF_porting.o RF_timers.c RF_timers.h RF_agents.o RF_events.o 
	${CC} ${CFLAGS} RF_timers.c

RF_agents.o: RF_agents.c RF_agents.h RF_events.o RF_queue.o RF_porting.o
	${CC} ${CFLAGS} RF_agents.c
	
RF_queue.o: RF_events.o RF_queue.c RF_queue.h RF_porting.o
	${CC} ${CFLAGS} RF_queue.c
	
RF_events.o: RF_events.c RF_events.h 
	${CC} ${CFLAGS} RF_events.c
	
RF_porting.o: RF_porting.c RF_porting.h
	${CC} ${CFLAGS} RF_porting.c
	
test:
	cd tests/queue; make test
	cd tests/dispatcher; make test
	cd tests/timers; make test
	
clean:
	rm -rf *.o *~ main
	cd tests/queue; make clean
	cd tests/dispatcher; make clean
	cd tests/timers; make clean
	
