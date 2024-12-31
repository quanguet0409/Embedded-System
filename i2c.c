#include "i2c.h"

void I2C1_Init()
{
	I2C_InitTypeDef i2c_init_struct;

  // Enable I2C1 peripheral clock
  	RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;
		RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;

  // Configure I2C1 pins
  // ...
	GPIOB->CRL |= (GPIO_CRL_CNF6 | GPIO_CRL_MODE6);
	GPIOB->CRL |= (GPIO_CRL_CNF7 | GPIO_CRL_MODE7);

  // Initialize I2C1 peripheral
  i2c_init_struct.I2C_ClockSpeed = 100000;  // Set I2C clock speed (in Hz)
  i2c_init_struct.I2C_Mode = I2C_Mode_I2C;  // Set stm32 as i2c master
//  i2c_init_struct.I2C_DutyCycle = I2C_DutyCycle_2;  // Set I2C duty cycle
//  i2c_init_struct.I2C_OwnAddress1 = 0x00;  // Set own address (not used in master mode)
  i2c_init_struct.I2C_Ack = I2C_Ack_Enable;  // Enable I2C acknowledge
  i2c_init_struct.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;  // Set acknowledged address mode

  I2C_Init(I2C1, &i2c_init_struct);  // Initialize I2C1 with the specified parameters

  I2C_Cmd(I2C1, ENABLE);  // Enable I2C1 peripheral
	
}

void I2C_Write(uint8_t addr, uint8_t data) {

	// T?o START condition
	 while (I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY));
    I2C_GenerateSTART(I2C1, ENABLE);

    // G?i d?a ch? slave và ch? ACK
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));
    I2C_Send7bitAddress(I2C1, addr, I2C_Direction_Transmitter);

    // G?i d? li?u
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
    I2C_SendData(I2C1, data);

    // K?t thúc truy?n d? li?u b?ng STOP condition
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
    I2C_GenerateSTOP(I2C1, ENABLE);
}

void I2C_Write_To_Reg(uint8_t addr, uint8_t data, uint8_t reg) {
	 // T?o START condition
    while (I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY));
    I2C_GenerateSTART(I2C1, ENABLE);

    // G?i d?a ch? slave và ch? ACK
    while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));
    I2C_Send7bitAddress(I2C1, addr, I2C_Direction_Transmitter);

    // G?i d?a ch? thanh ghi
    while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
    I2C_SendData(I2C1, reg);

    // G?i d? li?u
    while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
			I2C_SendData(I2C1, data);

    // K?t thúc truy?n d? li?u b?ng STOP condition
    while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
    I2C_GenerateSTOP(I2C1, ENABLE);
}

void I2C_Read(uint8_t addr, uint8_t reg, uint8_t* data, uint8_t length) {
     // T?o START condition
    while (I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY));
    I2C_GenerateSTART(I2C1, ENABLE);

    // G?i d?a ch? slave và ch? ACK
    while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));
    I2C_Send7bitAddress(I2C1, addr, I2C_Direction_Transmitter);

    // G?i d?a ch? thanh ghi
    while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
    I2C_SendData(I2C1, reg);

    // T?o RESTART condition

    while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
    I2C_GenerateSTART(I2C1, ENABLE);

    // G?i d?a ch? slave trong ch? d? d?c và ch? ACK
    while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));
    I2C_Send7bitAddress(I2C1, addr, I2C_Direction_Receiver);

    // Ð?c d? li?u
    while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));
    for (uint8_t i = 0; i < length; i++) {
        if (i == length - 1) {
            // Disable ACK before reading the last byte
            I2C_AcknowledgeConfig(I2C1, DISABLE);
        }

        while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED));
        data[i] = I2C_ReceiveData(I2C1);
    }

    // K?t thúc truy?n d? li?u b?ng STOP condition
    I2C_GenerateSTOP(I2C1, ENABLE);

    // Enable ACK again for the next communication
    I2C_AcknowledgeConfig(I2C1, ENABLE);
}