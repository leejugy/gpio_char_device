#include "gpio.h"
sem_t gpio_sem[GPIO_CHIP_NUM];

static GPIO_CHIP_NUMBER get_gpio_line(PIN_HEADER index, char *gpio_route)
{
    int chip_num = 0;

    if (P8_25 <= index && index <= P8_20)
    {
        sprintf(gpio_route, "%s0", GPIP_CHIP_ROUTE);
        chip_num = GPIO_CHIP0;
    }
    else if (P9_15B <= index && index <= P8_30)
    {
        sprintf(gpio_route, "%s1", GPIP_CHIP_ROUTE);
        chip_num = GPIO_CHIP1;
    }
    else if (P9_31 <= index && index <= P9_25)
    {
        sprintf(gpio_route, "%s2", GPIP_CHIP_ROUTE);
        chip_num = GPIO_CHIP2;
    }
    else if (P9_22 <= index && index <= P9_13)
    {
        sprintf(gpio_route, "%s3", GPIP_CHIP_ROUTE);
        chip_num = GPIO_CHIP3;
    }
    else
    {
        printf("unkown chip\n");
        return GPIO_CHIP_NONE;
    }

    return chip_num;
}

int gpio_init()
{
    int ret = 0;
    uint8_t i = 0;
    for (i = 0; i < GPIO_CHIP_NUM; i++)
    {
        ret = sem_init(&gpio_sem[i], 0, 1);

        if (ret < 0)
        {
            return -1;
        }
    }
}

int gpio_read(PIN_HEADER index, GPIO_PIN_VAL *gpio_val)
{
    int ret = 0;
    int fd = 0;
    int gpio_line = 0;
    struct gpio_v2_line_request req;
    struct gpio_v2_line_values val;
    char gpio_route[64] = {
        0,
    };

    memset(&req, 0, sizeof(req));
    memset(&val, 0, sizeof(val));

    gpio_line = get_gpio_line(index, gpio_route);
    sem_wait(&gpio_sem[gpio_line]);
    fd = open(gpio_route, O_RDWR);
    if (fd < 0)
    {
        sem_post(&gpio_sem[gpio_line]);
        return fd;
    }

    req.num_lines = 1;
    req.offsets[0] = GPIO_GET_LINE_INDEX_NUM(index, gpio_line);
    req.config.flags = GPIO_V2_LINE_FLAG_INPUT;
    req.config.num_attrs = 0;
    memset(req.config.attrs, 0, sizeof(req.config.attrs));

    ret = ioctl(fd, GPIO_V2_GET_LINE_IOCTL, &req);
    if (ret < 0)
    {
        sem_post(&gpio_sem[gpio_line]);
        printf("[index:%d]", index);
        perror("get line req fail");
        close(fd);
        return ret;
    }

    val.mask = 1; // 1번 라인만
    ret = ioctl(req.fd, GPIO_V2_LINE_GET_VALUES_IOCTL, &val);
    if (ret < 0)
    {
        sem_post(&gpio_sem[gpio_line]);
        printf("[index:%d]", index);
        perror("get line req fail");
        close(req.fd);
        close(fd);
        return ret;
    }

    *gpio_val = val.bits & 0x01;
    sem_post(&gpio_sem[gpio_line]);
    close(req.fd);
    close(fd);
    return ret;
}

int gpio_write(PIN_HEADER index, GPIO_PIN_VAL *gpio_val)
{
    int ret = 0;
    int fd = 0;
    int gpio_line = 0;
    static struct gpio_v2_line_request req; // 값 유지를 위해서, 닫아버리면? 값이 초기화 됨
    static struct gpio_v2_line_values val;
    char gpio_route[64] = {
        0,
    };

    close(req.fd); // 다시 실행되면 닫고 다시 열기.

    gpio_line = get_gpio_line(index, gpio_route);
    sem_wait(&gpio_sem[gpio_line]);
    fd = open(gpio_route, O_RDWR);
    if (fd < 0)
    {
        sem_post(&gpio_sem[gpio_line]);
        return fd;
    }

    req.num_lines = 1;
    req.offsets[0] = GPIO_GET_LINE_INDEX_NUM(index, gpio_line);
    req.config.flags = GPIO_V2_LINE_FLAG_OUTPUT;
    req.config.num_attrs = 0;
    memset(req.config.attrs, 0, sizeof(req.config.attrs));

    ret = ioctl(fd, GPIO_V2_GET_LINE_IOCTL, &req);
    if (ret < 0)
    {
        sem_post(&gpio_sem[gpio_line]);
        printf("[index:%d]", index);
        perror("get line req fail");
        close(fd);
        return ret;
    }

    val.bits = *gpio_val;
    val.mask = 1; // 1번 라인만
    ret = ioctl(req.fd, GPIO_V2_LINE_SET_VALUES_IOCTL, &val);
    if (ret < 0)
    {
        sem_post(&gpio_sem[gpio_line]);
        printf("[index:%d]", index);
        perror("get line req fail");
        close(fd);
        return ret;
    }

    sem_post(&gpio_sem[gpio_line]);
    close(fd);
    return ret;
}

void gpio_print_val(PIN_HEADER index)
{
    GPIO_PIN_VAL gpio_val = GPIO_VAL_NONE;
    char gpio_route[64] = {0, };
    GPIO_CHIP_NUMBER gpio_chip = get_gpio_line(index, gpio_route);
    gpio_read(index, &gpio_val);
    printf("[route : %s]", gpio_route);
    printf("[index : %d] val : %s\n", index, (gpio_val == GPIO_LOW) ? "gpio low" : (gpio_val == GPIO_HIGH) ? "gpio high" : "gpio_none");
}