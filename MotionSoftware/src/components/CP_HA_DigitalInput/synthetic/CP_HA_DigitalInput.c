#include <InputType.h>
#include <CP_HA_DigitalInput.h>
#include <stdio.h>

static struct DigitalInputType safetySwitchInputInstance =
{
		.pin = 0,
		.port = 'C',
};

CP_HA_DigitalInput safetySwitchInput = &safetySwitchInputInstance;

uint8_t CP_HA_DigitalInput_readInput(CP_HA_DigitalInput digitalInput)
{
	return (uint8_t)1;
}

void CP_HA_DigitalInput_constructInput(CP_HA_DigitalInput digitalInput)
{
	printf("Input port %c%d constructed\n", digitalInput->port, digitalInput->pin);
}
