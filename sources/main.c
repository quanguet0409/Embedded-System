#include "step_counter.h"
#include "lcd.h"
#include "mma8451.h"
#include <MKL46Z4.h>

int main(void)
{
    init_hardware();

    while (1)
    {
        if (is_active)
        {
            if (detect_step())
            {
                step_count++;
                display_steps(step_count);
            }
        }
    }
}
