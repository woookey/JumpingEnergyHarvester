DEV_DIR = /home/wookie/Development/ARMDev
CUR_DIR = $(shell pwd)
KERNEL_DIR = ${CUR_DIR}/src/kernel
TARGET_BUILD = ${CUR_DIR}/src/target/discoveryf4
COMPONENTS_DIR = ${CUR_DIR}/src/components
PORTING_DIR = ${CUR_DIR}/src/porting
TESTING_DIR = ${CUR_DIR}/src/testing

CPU_CONFIG = --specs=nosys.specs -mthumb -mcpu=cortex-m4

build_synthetic:
	make clean
	cd ${KERNEL_DIR}; make RF_kernel CC=gcc
	cd ${COMPONENTS_DIR}; make build_components CC=gcc
	cd ${TARGET_BUILD}; make build_synthetic
	mkdir -p bld/synthetic/
	cp ${TARGET_BUILD}/ARM_main ${CUR_DIR}/bld/synthetic

build_target:
	make clean
	cd ${KERNEL_DIR}; make RF_kernel CC=arm-none-eabi-gcc
	cd ${COMPONENTS_DIR}; make build_components CC=arm-none-eabi-gcc
	cd ${TARGET_BUILD}; make build_target
	mkdir -p bld/target
	cp ${TARGET_BUILD}/ARM_main.axf ${CUR_DIR}/bld/target
	cp ${TARGET_BUILD}/ARM_main.bin ${CUR_DIR}/bld/target


build_synthetic_kernel:
	make clean
	cd ${KERNEL_DIR}; make RF_kernel CC=gcc
	
test:
	make test_kernel;
	make test_components;
	
test_kernel:
	make clean
	cd ${KERNEL_DIR}; make test
	
test_components:
	make clean
	cd ${KERNEL_DIR}; make RF_kernel CC=gcc # TODO: The whole kernel is not needed to be compiled
	cd ${COMPONENTS_DIR}; make test_components
	
clean:
	rm -rf bld
	cd ${KERNEL_DIR}; make clean
	cd ${TARGET_BUILD}; make clean
	cd ${COMPONENTS_DIR}; make clean
	cd ${TESTING_DIR}; make clean