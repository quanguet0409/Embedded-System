#ifndef MMA8451_H
#define MMA8451_H

#include <stdint.h>

// MMA8451 registers
#define MMA8451_ADDR 0x1D
#define REG_XHI 0x01
#define REG_XLO 0x02
#define REG_YHI 0x03
#define REG_YLO 0x04
#define REG_ZHI 0x05
#define REG_ZLO 0x06
#define REG_CTRL1 0x2A
#define REG_XYZ_DATA_CFG 0x0E

void mma8451_init(void);
void mma8451_read_xyz(int16_t *x, int16_t *y, int16_t *z);
uint8_t detect_step(void);

#endif