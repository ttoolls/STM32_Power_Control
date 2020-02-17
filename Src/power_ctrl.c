 /******************************************************************************
  * @file           : power_ctrl.c
  * @brief          : Realization of program logic
  ******************************************************************************
  */

#include "power_ctrl.h"
#include "main.h"

/** @brief Current treshold
	* @detail it is defined by setting array of swithes s0 to s7 
	*/
uint16_t Current_Max = 0;

/** @brief Delta between normal and abnormal values.
	*
	* Defines value to which current parameters shoul decreases to enable work mode
	* in the case of trouble situation is detected
*/
const float Delta = 0.9; 

const uint16_t Voltage_Max = 18;			//< Maximum voltahe value
const uint16_t Voltage_Min = 9;				//< Minimum voltage value
const float Vdda = 3.3;								//< ADC refference voltage 
const uint16_t ADC_Resolution = 4096;	//< ADC resolution

extern uint8_t Alarm;

/** @brief This function reads Current_Max from array of switches s0 to s7. 
	* @param None
	* @retval None

	* The array of switches s0 to s7 defines a binary value setted by user.
	* Than the value is multiplied by 3 to obtain maximal current.
	*/
void Current_Max_Read()
{
	//* Binary value read from array of switches s0 to s7
	uint32_t tmp = 0;				
	tmp = tmp | ((HAL_GPIO_ReadPin(S0_GPIO_Port, S0_Pin))^1);
	tmp = tmp | ((HAL_GPIO_ReadPin(S1_GPIO_Port, S1_Pin))^1)<<1;
	tmp = tmp | ((HAL_GPIO_ReadPin(S2_GPIO_Port, S2_Pin))^1)<<2;
	tmp = tmp | ((HAL_GPIO_ReadPin(S3_GPIO_Port, S3_Pin))^1)<<3;
	tmp = tmp | ((HAL_GPIO_ReadPin(S4_GPIO_Port, S4_Pin))^1)<<4;
	tmp = tmp | ((HAL_GPIO_ReadPin(S5_GPIO_Port, S5_Pin))^1)<<5;
	tmp = tmp | ((HAL_GPIO_ReadPin(S6_GPIO_Port, S6_Pin))^1)<<6;
	tmp = tmp | ((HAL_GPIO_ReadPin(S7_GPIO_Port, S7_Pin))^1)<<7;

	Current_Max = tmp*3;
}

/** @brief This function checks if values of current, input and output voltages are within set boundaries
	* @param Current is checked current value
	* @param Voltage_In is checked input voltage value
	* @param Voltage_Out is checked output voltage value
	* @retval 1 if the parameters are within set boundaries and 0 if they are not.
	*/
uint8_t Check_Parameters(uint16_t Current, uint16_t Voltage_In, uint16_t Voltage_Out)
{
	uint8_t flag = 1;
	float Shift;
	if (Alarm == 1)
	{
		Shift = Delta;
	}
	float u =  Voltage_In*Vdda/ADC_Resolution * Shift;
	if (u< Voltage_Min/10 || u>Voltage_Max/10) 
	{
			flag = 0;
	}
	u = Current*Vdda/ADC_Resolution*Shift;
	if (u > Current_Max/10)
	{
		flag = 0;
	}
	u = Voltage_Out*Vdda/ADC_Resolution*Shift;
	if (u< Voltage_Min/10 || u>Voltage_Max/10)
	{
		flag = 0;
	}
	if (flag == 1)
	{
		Alarm = 0;
	}
	return flag;	 
}
