#include <CP_HA_PWMDefinition.h>
#include <CP_HA_PWM.h>

static struct PWMStruct pretensionMotorPWMInstance =
{
	.htim =
	{
		.Instance = TIM3,
		.Init =
		{
			.Prescaler = (uint32_t)0,
			.CounterMode = TIM_COUNTERMODE_UP,
			.Period = (uint32_t)8399,
			.ClockDivision = TIM_CLOCKDIVISION_DIV1,
			.RepetitionCounter = (uint32_t)0,
		},
		//DMA_HandleTypeDef - ignore DMA
		.Channel = HAL_TIM_ACTIVE_CHANNEL_2,
		.Lock = HAL_UNLOCKED,
		.State = HAL_TIM_STATE_RESET,
	},
};

//typedef struct
//{
//  TIM_TypeDef                 *Instance;     /*!< Register base address             */
//  TIM_Base_InitTypeDef        Init;          /*!< TIM Time Base required parameters */
//  HAL_TIM_ActiveChannel       Channel;       /*!< Active channel                    */
//  DMA_HandleTypeDef           *hdma[7];      /*!< DMA Handlers array
//                This array is accessed by a @ref DMA_Handle_index */
 // HAL_LockTypeDef             Lock;          /*!< Locking object                    */
 // __IO HAL_TIM_StateTypeDef   State;         /*!< TIM operation state               */
//}TIM_HandleTypeDef;



CP_HA_PWM CP_HA_PWM_pretensionMotorPWM = &pretensionMotorPWMInstance;

void CP_HA_initialisePWM(CP_HA_PWM PWMInstance)
{
	//HAL_StatusTypeDef
	HAL_TIM_PWM_Init(&PWMInstance->htim);
}

void CP_HA_startPWM(CP_HA_PWM PWMInstance)
{
	HAL_TIM_PWM_Start(&PWMInstance->htim, TIM_CHANNEL_2);
}
