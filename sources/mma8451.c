#include "mma8451.h"
#include <MKL46Z4.h>

static void i2c_init(void);
static void i2c_write(uint8_t reg, uint8_t data);
static uint8_t i2c_read(uint8_t reg);

void init_accelerometer(void)
{
    // Initialize I2C
    i2c_init();

    // Configure accelerometer
    i2c_write(CTRL_REG1, 0x00);    // Standby mode
    i2c_write(XYZ_DATA_CFG, 0x00); // 2g range
    i2c_write(CTRL_REG1, 0x01);    // Active mode, 800Hz
}

uint8_t detect_step(void)
{
    static int16_t prev_z = 0;
    int16_t x, y, z;
    static uint8_t step_state = 0;

    read_accelerometer(&x, &y, &z);

    // Simple step detection algorithm
    if ((z - prev_z) > 1000 && step_state == 0)
    {
        step_state = 1;
        prev_z = z;
        return 1;
    }
    else if ((z - prev_z) < -1000)
    {
        step_state = 0;
    }

    prev_z = z;
    return 0;
}

void read_accelerometer(int16_t *x, int16_t *y, int16_t *z)
{
    // Read 6 bytes of data for X, Y, Z
    // Convert to 16-bit values
    *x = (int16_t)((i2c_read(0x01) << 8) | i2c_read(0x02));
    *y = (int16_t)((i2c_read(0x03) << 8) | i2c_read(0x04));
    *z = (int16_t)((i2c_read(0x05) << 8) | i2c_read(0x06));
}

// I2C helper functions implementation
static void i2c_init(void)
{
    // Enable clock to I2C and port
    SIM->SCGC4 |= SIM_SCGC4_I2C0_MASK;
    SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK;

    // Configure I2C pins
    PORTE->PCR[24] = PORT_PCR_MUX(5); // SCL
    PORTE->PCR[25] = PORT_PCR_MUX(5); // SDA

    // Configure I2C
    I2C0->F = 0x14;               // Set frequency divider for 100kHz
    I2C0->C1 = I2C_C1_IICEN_MASK; // Enable I2C
}

static void i2c_write(uint8_t reg, uint8_t data)
{
    // I2C write implementation
}

static uint8_t i2c_read(uint8_t reg)
{
    // I2C read implementation
    return 0;
}