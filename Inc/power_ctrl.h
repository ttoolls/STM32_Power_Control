/******************************************************************************
  * @file           : power_ctrl.h
  * @brief          : Header for my_code.c file.
  *                   This file contains defines of the user functions.
  ******************************************************************************
  */
	
#pragma once

#include <stdint.h>

/** @brief This function reads Current_Max from array of switches s0 to s7. 
	* @param None
	* @retval None

	* The array of switches s0 to s7 defines a binary value setted by user.
	* Than the value is multiplied by 3 to obtain maximal current.
	*/
void Current_Max_Read();

/** @brief This function checks if values of current, input and output voltages are within set boundaries
	* @param Current is checked current value
	* @param Voltage_In is checked input voltage value
	* @param Voltage_Out is checked output voltage value
	* @retval 1 if the parameters are within set boundaries and 0 if they are not.
	*/
uint8_t Check_Parameters(uint16_t Current, uint16_t Voltage_In, uint16_t Voltage_Out);
