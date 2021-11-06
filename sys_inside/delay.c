/*
 * delay.c
 *
 *  Created on: 05/04/2019
 *      Author: cyh
 */

#include "delay.h"
/**
  * @brief  Delay severl time.
  * @param  None
  * @param  None
  * @retval None
  */
void Delay_ms(uint32_t nCount)
{
    DELAY_US(nCount * 1000);
}
/**
  * @brief  Delay severl time.
  * @param  nCount
  * @retval None
  */
void Delay_us(uint32_t nCount)
{
    DELAY_US(nCount);
}



