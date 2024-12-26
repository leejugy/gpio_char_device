#include "gpio.h"

int main()
{
    gpio_init();
    GPIO_PIN_VAL gpio_val = 0;
    while(1)
    {
        gpio_val = GPIO_HIGH;
        gpio_write(P8_11, &gpio_val);
        printf("high\n");
        sleep(1);

        gpio_print_val(P8_13);
        sleep(1);

        gpio_val = GPIO_LOW;
        gpio_write(P8_11, &gpio_val);
        printf("low\n");
        sleep(1);
    }
}