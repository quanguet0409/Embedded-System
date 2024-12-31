#include "mma8451.h"
#include <MKL46Z4.h>

static void i2c_init(void);
static void i2c_start(void);
static void i2c_stop(void);
static void i2c_write_byte(uint8_t data);
static uint8_t i2c_read_byte(uint8_t ack);
static void i2c_wait(void);

void mma8451_init(void)
{
    i2c_init();

    // Put in standby
    i2c_start();
    i2c_write_byte(MMA8451_ADDR << 1);
    i2c_write_byte(REG_CTRL1);
    i2c_write_byte(0x00);
    i2c_stop();

    // Configure XYZ_DATA_CFG for ±2g range
    i2c_start();
    i2c_write_byte(MMA8451_ADDR << 1);
    i2c_write_byte(REG_XYZ_DATA_CFG);
    i2c_write_byte(0x00);
    i2c_stop();

    // Active mode, 800Hz output
    i2c_start();
    i2c_write_byte(MMA8451_ADDR << 1);
    i2c_write_byte(REG_CTRL1);
    i2c_write_byte(0x01);
    i2c_stop();
}

void mma8451_read_xyz(int16_t *x, int16_t *y, int16_t *z)
{
    uint8_t temp;

    // Read X
    i2c_start();
    i2c_write_byte(MMA8451_ADDR << 1);
    i2c_write_byte(REG_XHI);
    i2c_start();
    i2c_write_byte((MMA8451_ADDR << 1) | 1);
    temp = i2c_read_byte(1);
    *x = temp << 8;
    temp = i2c_read_byte(0);
    *x |= temp;
    *x >>= 2;
    i2c_stop();

    // Read Y
    i2c_start();
    i2c_write_byte(MMA8451_ADDR << 1);
    i2c_write_byte(REG_YHI);
    i2c_start();
    i2c_write_byte((MMA8451_ADDR << 1) | 1);
    temp = i2c_read_byte(1);
    *y = temp << 8;
    temp = i2c_read_byte(0);
    *y |= temp;
    *y >>= 2;
    i2c_stop();

    // Read Z
    i2c_start();
    i2c_write_byte(MMA8451_ADDR << 1);
    i2c_write_byte(REG_ZHI);
    i2c_start();
    i2c_write_byte((MMA8451_ADDR << 1) | 1);
    temp = i2c_read_byte(1);
    *z = temp << 8;
    temp = i2c_read_byte(0);
    *z |= temp;
    *z >>= 2;
    i2c_stop();
}

uint8_t detect_step(void)
{
    static int16_t prev_z = 0;
    int16_t x, y, z;
    static uint8_t step_state = 0;

    mma8451_read_xyz(&x, &y, &z);

    // Step detection algorithm
    if ((z - prev_z) > 4000 && step_state == 0)
    {
        step_state = 1;
        prev_z = z;
        return 1;
    } else if ((z - prev_z) < -4