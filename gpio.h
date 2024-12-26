#ifndef __GPIO__
#define __GPIO__

#include <linux/gpio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>

#define GPIO_CHIP_NUM 4
#define GPIP_CHIP_ROUTE "/dev/gpiochip"
#define GPIO_GET_LINE_INDEX_NUM(gpio_index, gpio_chip_num) gpio_index - gpio_chip_num * 32

typedef enum
{
    P8_25 = 0, /* gpio chip 0 */
    P8_5 = 2,
    P8_6 = 3,
    P8_23 = 4,
    P8_22 = 5,
    P8_3 = 6,
    P8_4 = 7,
    P8_12 = 12,
    P8_11 = 13,
    P8_16 = 14,
    P8_15 = 15,
    P9_15A = 16,
    P9_23 = 17,
    P9_14 = 18,
    P9_16 = 19,
    P9_12 = 28,
    P8_26 = 29,
    P8_21 = 30,
    P8_20 = 31,

    P9_15B = 0 + 32, /* gpio chip 1 */
    P8_18 = 1 + 32,
    P8_7 = 2 + 32,
    P8_8 = 3 + 32,
    P8_10 = 4 + 32,
    P8_9 = 5 + 32,
    P8_45 = 6 + 32,
    P8_46 = 7 + 32,
    P8_43 = 8 + 32,
    P8_44 = 9 + 32,
    P8_41 = 10 + 32,
    P8_42 = 11 + 32,
    P8_39 = 12 + 32,
    P8_40 = 13 + 32,
    P8_37 = 14 + 32,
    P8_38 = 15 + 32,
    P8_36 = 16 + 32,
    P8_34 = 17 + 32,
    P8_27 = 22 + 32,
    P8_29 = 23 + 32,
    P8_28 = 24 + 32,
    P8_30 = 25 + 32,

    P9_31 = 14 + 64, /* gpio chip 2 */
    P9_29 = 15 + 64,
    P9_30 = 16 + 64,
    P9_28 = 17 + 64,
    P9_42B = 18 + 64,
    P9_27 = 19 + 64,
    P9_41A = 20 + 64,
    P9_25 = 21 + 64,

    P9_22 = 2 + 96, /* gpio chip 3 */
    P9_21 = 3 + 96,
    P9_18 = 4 + 96,
    P9_17 = 5 + 96,
    P9_42A = 7 + 96,
    P8_35 = 8 + 96,
    P8_33 = 9 + 96,
    P8_31 = 10 + 96,
    P8_32 = 11 + 96,
    P9_20 = 12 + 96,
    P9_19 = 13 + 96,
    P9_26 = 14 + 96,
    P9_24 = 15 + 96,
    P9_41B = 20 + 96,
    P8_19 = 22 + 96,
    P8_13 = 23 + 96,
    P8_14 = 26 + 96,
    P8_17 = 27 + 96,
    P9_11 = 30 + 96,
    P9_13 = 31 + 96,
} PIN_HEADER;

typedef enum
{
    GPIO_LOW,
    GPIO_HIGH,
    GPIO_VAL_NONE = -1,
} GPIO_PIN_VAL;

typedef enum
{
    GPIO_CHIP0,
    GPIO_CHIP1,
    GPIO_CHIP2,
    GPIO_CHIP3,
    GPIO_CHIP_NONE = -1,
} GPIO_CHIP_NUMBER;

int gpio_init();

int gpio_read(PIN_HEADER index, GPIO_PIN_VAL *gpio_val);

int gpio_write(PIN_HEADER index, GPIO_PIN_VAL *gpio_val);

void gpio_print_val(PIN_HEADER index);
#endif