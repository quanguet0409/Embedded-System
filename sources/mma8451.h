#ifndef MMA8451_H
#define MMA8451_H

#include <stdint.h>

void init_accelerometer(void);
uint8_t detect_step(void);
void read_accelerometer(int16_t *x, int16_t *y, int16_t *z);

#define MMA8451_I2C_ADDRESS 0x1D
#define CTRL_REG1 0x2A
#define XYZ_DATA_CFG 0x0E

#endif