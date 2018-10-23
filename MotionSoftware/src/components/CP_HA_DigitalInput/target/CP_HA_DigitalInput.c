#include <InputType.h>
#include <CP_HA_DigitalInput.h>
#include <stdint.h>


static struct DigitalInputType safetySwitchInputInstance =
{
		.GPIOTypeDef_t = GPIOC,
		.GPIOInitTypeDef_t =
		{
			.Pin = 4,
			.Mode = GPIO_MODE_INPUT,
			.Pull = GPIO_PULLDOWN,
			.Speed = GPIO_SPEED_FREQ_VERY_HIGH,
		},
};

CP_HA_DigitalInput safetySwitchInput = &safetySwitchInputInstance;

uint8_t CP_HA_DigitalInput_readInput(CP_HA_DigitalInput digitalInput)
{
	return (uint8_t)digitalInput->GPIOTypeDef_t->IDR;
}
void CP_HA_DigitalInput_constructInput(CP_HA_DigitalInput digitalInput)
{
	digitalInput->GPIOTypeDef_t->MODER |= (1 << (digitalInput->GPIOInitTypeDef_t.Pin << 1));
	digitalInput->GPIOTypeDef_t->OSPEEDR |= (3 << (digitalInput->GPIOInitTypeDef_t.Pin << 1));
}
