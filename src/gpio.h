/* gpio routines. */

#ifndef GPIO_H
#define GPIO_H

#include <linux/gpio.h>

struct wp_gpio {
  struct gpiohandle_request *req;
  struct gpiohandle_data *data;
  int chip_fd;
  int line_fd[GPIOHANDLES_MAX];
};

struct wp_gpio_pin {
  int chip;
  int pin;
};

void wp_gpio_write (int pin, int value);

int wp_gpio_init();

int wp_gpio_pin_mode(int pin);

#endif
