 /******************************************************************************
  * @file           : my_code.c
  * @brief          : Realization of program logic
  ******************************************************************************
  */

#include "power_ctrl.h"
#include "main.h"

/** @brief Current treshold
	* @detail it is defined by setting array of swithes s0 to s7 
	*/
uint16_t Current_Max = 0;


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