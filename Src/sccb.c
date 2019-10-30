/*********************************************************************************************************
*
* File                : sccb.c
* Hardware Environment: 
* Build Environment   : RealView MDK-ARM  Version: 4.20
* Version             : V1.0
* By                  : Yehui
*
*                                  (c) Copyright 2005-2017, WaveShare
*                                       http://www.waveshare.net
*                                          All Rights Reserved
*
*********************************************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "sccb.h"
#include "main.h"

/* --EV5 */
#define  I2C_EVENT_MASTER_MODE_SELECT                      ((uint32_t)0x00030001)  /* BUSY, MSL and SB flag */

/* --EV6 */
#define  I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED        ((uint32_t)0x00070082)  /* BUSY, MSL, ADDR, TXE and TRA flags */
#define  I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED           ((uint32_t)0x00030002)  /* BUSY, MSL and ADDR flags */

/* Master RECEIVER mode -----------------------------*/ 
/* --EV7 */
#define  I2C_EVENT_MASTER_BYTE_RECEIVED                    ((uint32_t)0x00030040)  /* BUSY, MSL and RXNE flags */

/* Master TRANSMITTER mode --------------------------*/
/* --EV8 */
#define I2C_EVENT_MASTER_BYTE_TRANSMITTING                 ((uint32_t)0x00070080) /* TRA, BUSY, MSL, TXE flags */
/* --EV8_2 */
#define  I2C_EVENT_MASTER_BYTE_TRANSMITTED                 ((uint32_t)0x00070084)  /* TRA, BUSY, MSL, TXE and BTF flags */





__IO uint32_t  DCMI_TIMEOUT_MAX = 10000;

/*******************************************************************************
* Function Name  : SCCB_GPIO_Config
* Description    : 
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void SCCB_GPIO_Config(void)
{
//	I2C_InitTypeDef  SCCB_InitStructure;
//	GPIO_InitTypeDef  GPIO_InitStructure; 
//	
//	RCC_AHB1PeriphClockCmd(Open207V_SCCB_SDA_GPIO_CLK | Open207V_SCCB_SCL_GPIO_CLK,ENABLE);
//	
//	RCC_APB1PeriphClockCmd(Open207V_SCCB_CLK,ENABLE);
//	
//	GPIO_PinAFConfig(Open207V_SCCB_SDA_GPIO_PORT, Open207V_SCCB_SDA_SOURCE, Open207V_SCCB_SDA_AF);
//	GPIO_PinAFConfig(Open207V_SCCB_SCL_GPIO_PORT, Open207V_SCCB_SCL_SOURCE, Open207V_SCCB_SCL_AF);
//	
//	GPIO_InitStructure.GPIO_Pin =  Open207V_SCCB_SDA_PIN | Open207V_SCCB_SCL_PIN;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
//  	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
//  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
//  	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
//	GPIO_Init(GPIOB, &GPIO_InitStructure);
//		
//	I2C_DeInit(Open207V_SCCB);
//	SCCB_InitStructure.I2C_Mode = I2C_Mode_I2C;
//	SCCB_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
//	SCCB_InitStructure.I2C_OwnAddress1 = SCCB_SLAVE_ADDRESS7;
//	SCCB_InitStructure.I2C_Ack = I2C_Ack_Enable;
//	SCCB_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
//	SCCB_InitStructure.I2C_ClockSpeed = SCCB_SPEED;
//	
//	I2C_Cmd(Open207V_SCCB, ENABLE);
//	I2C_Init(Open207V_SCCB, &SCCB_InitStructure);
//	
//	I2C_AcknowledgeConfig(Open207V_SCCB, ENABLE);	
}

/**
  * @brief  Writes a byte at a specific Camera register
  * @param  Device: OV9655 write address.
  * @param  Addr: OV9655 register address. 
  * @param  Data: data to be written to the specific register 
  * @retval 0x00 if write operation is OK. 
  *         0xFF if timeout condition occured (device not connected or bus error).
  */
uint8_t DCMI_SingleRandomWrite(uint8_t DeviceAddr, uint16_t Reg, uint8_t Data)
{
  if(HAL_I2C_Mem_Write(&hi2c2, DeviceAddr, Reg, I2C_MEMADD_SIZE_8BIT, &Data, 1, 100) != HAL_OK)
  {
    return 0xFF;
  }
  return 0;
}

/**
  * @brief  Reads a byte from a specific Camera register 
  * @param  Device: OV9655 write address.
  * @param  Addr: OV9655 register address. 
  * @retval data read from the specific register or 0xFF if timeout condition 
  *         occured. 
  */

uint8_t DCMI_SingleRandomRead(uint8_t DeviceAddr, uint16_t Reg, uint8_t *Data)
{
  if(HAL_I2C_Mem_Read(&hi2c2, DeviceAddr, Reg, I2C_MEMADD_SIZE_8BIT, Data, 1, 100) != HAL_OK)
  {
    return 0xFF;
  }
  return 0;
}
