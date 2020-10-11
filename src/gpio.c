/* gpio routines.
gpio line = gpio pin
line handle = pin handle
linux/gpio.h can be used to handle multiple gpio lines at the same time. */

#include "gpio.h"

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include <linux/gpio.h>

struct wp_gpio wg_gpio_instance;

int wp_gpio_init() {
  char chrdev_name[20];
  int fd, ret;
  
  struct gpiohandle_request *req;
  struct gpiohandle_data *data;

  strcpy(chrdev_name, "/dev/gpiochip6");

  /*  Open device: gpiochip6 for GPIO bank G */
  fd = open(chrdev_name, 0);
  if (fd == -1) {
    ret = -errno;
    fprintf(stderr, "Failed to open %s\n", chrdev_name);

    return ret;
  }

  wg_gpio_instance.fd = fd;
  
  wg_gpio_instance.req = malloc(sizeof(struct gpiohandle_request));
  wg_gpio_instance.data = malloc(sizeof(struct gpiohandle_data));

  req = wg_gpio_instance.req;
  data = wg_gpio_instance.data;
  
  /* request GPIO line: GPIO_G_3 */
  req->lineoffsets[0] = 3;
  req->lines  = 1;
  req->flags = GPIOHANDLE_REQUEST_OUTPUT;
  memcpy(req->default_values, data, sizeof(req->default_values));
  strcpy(req->consumer_label, "led_gpio_g_3");

  ret = ioctl(fd, GPIO_GET_LINEHANDLE_IOCTL, req);
  if (ret == -1) {
    ret = -errno;
    fprintf(stderr, "strerror: %s\n", strerror(errno));
    fprintf(stderr, "Failed to issue GET LINEHANDLE IOCTL (%d)\n",
			ret);
  }
  if (close(fd) == -1)
    perror("Failed to close GPIO character device file");

}

int wp_gpio_release() {
  int ret;
  /*  release line */
  ret = close(wg_gpio_instance.fd);
  if (ret == -1) {
    perror("Failed to close GPIO LINEHANDLE device file");
    ret = -errno;
  }
  return 0;
}
int wp_gpio_pin_mode() {
  return 0;
}

void wp_gpio_write (int pin, int value) {
  int ret;
  
  struct gpiohandle_request *req;
  struct gpiohandle_data *data;

  value = value ? 1 : 0;
  
  req = wg_gpio_instance.req;
  data = wg_gpio_instance.data;
  
  data->values[0] = value;
  ret = ioctl(req->fd, GPIOHANDLE_SET_LINE_VALUES_IOCTL, data);
  if (ret == -1) {
    ret = -errno;
    fprintf(stderr, "Failed to issue %s (%d)\n",
            "GPIOHANDLE_SET_LINE_VALUES_IOCTL", ret);
  }
}

int wp_gpio_main(int argc, char **argv)
{
  int ret;
  
  ret = wp_gpio_init();
  if (ret != 0) return ret;

  
  /*  Start led blinking */
  while(1) {
    sleep(1);
    wp_gpio_write(3, 1);
    sleep(1);
    wp_gpio_write(3, 0);
  }

  return ret;
}

/* int main(int argc, char **argv) { */
/*   return wp_gpio_main(argc, argv); */
/* } */
