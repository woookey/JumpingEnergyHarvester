CUR_DIR = $(shell pwd)

OBJS = CP_HD_MotorControlBoard.c
CFLAGS = -Wall -g -I. -c
CPU_CONFIG = --specs=nosys.specs -mthumb -mcpu=cortex-m4

INC_DIR = -I${CUR_DIR}/../CP_HA_GPIO/
INC_DIR += -I${CUR_DIR}/../CP_HA_PWM/

ifeq (${CC}, arm-none-eabi-gcc)
	INC_DIR += -I${CUR_DIR}/../CP_HA_GPIO/target
	#INC_DIR += -I${CUR_DIR}/../CP_HA_PWM/target
	INC_DIR += -I${CUR_DIR}/../../lib/CMSIS/Device/ST/STM32F4xx/Include
	INC_DIR += -I${CUR_DIR}/../../lib/CMSIS/Include
	INC_DIR += -I${CUR_DIR}/../../lib/STM32F4xx_HAL_Driver/Inc
	CFLAGS += -DSTM32F407xx
	CFLAGS += ${CPU_CONFIG}
else
	INC_DIR += -I${CUR_DIR}/../CP_HA_GPIO/synthetic/
	#INC_DIR += -I${CUR_DIR}/../CP_HA_PWM/synthetic/
endif

CP_HD_MotorControlBoard.o: CP_HD_MotorControlBoard.c
	${CC} ${CFLAGS} ${INC_DIR} ${OBJS} -o CP_HD_MotorControlBoard.o
	
#test:
#	cd tests; make test
	
clean:
	rm -rf *.o *.~
#	cd tests; make clean