#include <CP_HD_DigitalAndAnalogInputs.h>
#include <CP_HA_DigitalInput.h>


struct digitalAndAnalogInputStruct
{
	CP_HA_DigitalInput digitalInput;
};

struct digitalAndAnalogInputStruct safetySwitchInstance =
{
	.digitalInput = safetySwitchInput,
};


CP_HD_DigitalAndAnalogInput CP_HD_DigitalAndAnalogInput_SafetySwitch =
		&safetySwitchInstance;

void CP_HD_DigitalAndAnalogInputs_ReadInput(CP_HD_DigitalAndAnalogInput input);
