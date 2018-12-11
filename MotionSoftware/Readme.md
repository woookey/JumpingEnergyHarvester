# Modular Systems Framework
Modular Systems Framework is a C project implementing the kernel for any event-driven, real-time project that is based on modules

## Prerequisite ##
* st-link software is installed
* GNU Arm Embedded Toolchain (https://developer.arm.com/open-source/gnu-toolchain/gnu-rm/downloads)

## How to use ##
Only synthetic build and STM32F407VG microcontroller are supported for now!

* For synthetic build:
  1) make build_synthetic
  2) ./bld/synthetic/ARM_main

* For target build
  1) make build_target
  2) st-flash write ./bld/target/ARM_main.bin 0x8000000 

## Compilation ##
make build_target - for target 
make build_synthetic - for synthetic

## Testing ##
make test

## Running synthetic version ##
./bld/synthetic/ARM_main

## Flashing target ##
st-flash write ./bld/target/ARM_main.bin 0x8000000
