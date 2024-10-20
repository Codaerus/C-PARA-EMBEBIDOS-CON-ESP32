#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

void app_main() {
  gpio_set_direction(GPIO_NUM_2, GPIO_MODE_OUTPUT);
  gpio_set_direction(GPIO_NUM_4, GPIO_MODE_INPUT);
  gpio_set_pull_mode(GPIO_NUM_4, GPIO_PULLUP_ONLY);
  while (1){
    int button_state = gpio_get_level(GPIO_NUM_4);
    if(button_state == 0) {
        gpio_set_level(GPIO_NUM_2,1);
    }
    else{
        gpio_set_level(GPIO_NUM_2,0);
    }
  }
}
