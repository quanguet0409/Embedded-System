#ifndef STEP_COUNTER_H
#define STEP_COUNTER_H

#include <stdint.h>

// Global variables (extern to be accessible across files)
extern volatile uint32_t step_count;
extern volatile uint8_t is_active;

// Function prototypes
void init_hardware(void);
void toggle_counter(void);
void reset_counter(void);

#endif
