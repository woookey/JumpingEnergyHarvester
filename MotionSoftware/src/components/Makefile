CUR_DIR = $(shell pwd)

build_components:
	make build_components_CP_HA_LED
	make build_components_CP_HA_GPIO
	make build_components_CP_HA_PWM
	make build_components_CP_HD_LEDDriver
	make build_components_LEDManager
	make build_components_CP_HA_HardwareSetup
	make build_components_CP_BH_PowerManager
	make build_components_CP_HD_MotorControlBoard
	make build_components_CP_BH_LegControl
	make build_components_CP_BH_LoggingManager
	make build_components_CP_HD_Logger
	make build_components_CP_HA_UART
	make build_components_CP_HA_ADC
	make build_components_CP_HD_AnalogInput
	
build_components_CP_HD_AnalogInput:
	cd ${CUR_DIR}/CP_HD_AnalogInput; make CP_HD_AnalogInput.o CC=${CC}

build_components_CP_HA_UART:
	cd ${CUR_DIR}/CP_HA_UART; make CP_HA_UART.o CC=${CC}
	
build_components_CP_HD_Logger:
	cd ${CUR_DIR}/CP_HD_Logger; make CP_HD_Logger.o CC=${CC}
	
build_components_CP_BH_LoggingManager:
	cd ${CUR_DIR}/CP_BH_LoggingManager; make CP_BH_LoggingManager.o CC=${CC}
	
build_components_CP_HD_MotorControlBoard:
	cd ${CUR_DIR}/CP_HD_MotorControlBoard; make CP_HD_MotorControlBoard.o CC=${CC}
	
build_components_CP_HA_GPIO:
	cd ${CUR_DIR}/CP_HA_GPIO; make CP_HA_GPIO.o CC=${CC}
	
build_components_CP_HA_PWM:
	cd ${CUR_DIR}/CP_HA_PWM; make CP_HA_PWM.o CC=${CC}
	
build_components_CP_BH_PowerManager:
	cd ${CUR_DIR}/CP_BH_PowerManager; make CP_BH_PowerManager.o CC=${CC}
	
build_components_CP_HA_HardwareSetup:
	cd ${CUR_DIR}/CP_HA_HardwareSetup; make CP_HA_HardwareSetup.o CC=${CC}
	
build_components_CP_HA_LED:
	cd ${CUR_DIR}/CP_HA_LED; make CP_HA_LED.o CC=${CC}

build_components_CP_HD_LEDDriver:
	cd ${CUR_DIR}/CP_HD_LEDDriver; make CP_HD_LEDDriver.o CC=${CC}
	
build_components_LEDManager:
	cd ${CUR_DIR}/LEDManager; make LEDManager.o CC=${CC}
	
build_components_CP_BH_LegControl:
	cd ${CUR_DIR}/CP_BH_LegControl; make CP_BH_LegControl.o CC=${CC}
	
build_components_CP_HA_ADC:
	cd ${CUR_DIR}/CP_HA_ADC; make CP_HA_ADC.o CC=${CC}
	
test_components:
	make test_components_LEDManager
	make test_components_CP_HD_LEDDriver
	
test_components_LEDManager:
	cd ${CUR_DIR}/LEDManager; make test
	
test_components_CP_HD_LEDDriver:
	cd ${CUR_DIR}/CP_HD_LEDDriver; make test
	

clean:
	cd $(CUR_DIR)/LEDManager; make clean
	cd ${CUR_DIR}/CP_HD_LEDDriver; make clean
	cd ${CUR_DIR}/CP_HA_LED; make clean
	cd ${CUR_DIR}/CP_HA_HardwareSetup; make clean
	cd ${CUR_DIR}/CP_BH_PowerManager; make clean
	cd ${CUR_DIR}/CP_BH_LegControl; make clean
	cd ${CUR_DIR}/CP_HA_GPIO; make clean
	cd ${CUR_DIR}/CP_HD_MotorControlBoard; make clean
	cd ${CUR_DIR}/CP_HA_PWM; make clean
	cd ${CUR_DIR}/CP_BH_LoggingManager; make clean
	cd ${CUR_DIR}/CP_HD_Logger; make clean
	cd ${CUR_DIR}/CP_HA_UART; make clean
	cd ${CUR_DIR}/CP_HA_ADC; make clean
	cd ${CUR_DIR}/CP_HD_AnalogInput; make clean
	
	