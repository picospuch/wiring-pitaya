/* gpio routines. */

#ifndef GPIO_H
#define GPIO_H

struct wp_gpio {
  struct gpiohandle_request *req;
  struct gpiohandle_data *data;
  int fd;
};

struct wp_gpio_pin {
  int chip;
  int pin;
};

void wp_gpio_write (int pin, int value);

int wp_gpio_init();

#endif
