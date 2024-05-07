#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_chip_info.h"
#include "esp_flash.h"
#include "esp_system.h"


#define GPIO_0 GPIO_NUM_0
#define GPIO_21 GPIO_NUM_21


static void configure_GPIO(void)
{
	//reset an io
	gpio_reset_pin(GPIO_0);
	//set GPIO_0 as an output
	gpio_set_direction(GPIO_0, GPIO_MODE_OUTPUT);
	//reset an io
	gpio_reset_pin(GPIO_21);
	//set GPIO_21 as an input
	gpio_set_direction(GPIO_21, GPIO_MODE_INPUT);
}


void app_main(void)
{
	configure_GPIO();
    while (true) {
        if(gpio_get_level(GPIO_21)==1){
        	printf("value detected");
        	gpio_set_level(GPIO_0, 1);
        }
        else{
        	printf("no value");
        	gpio_set_level(GPIO_0, 0);
        }
        for (int i = 10; i >= 0; i--) {
        	printf("wait in %d seconds...\n", i);
            vTaskDelay(4000 / portTICK_PERIOD_MS);
        }





        sleep(1);
    }
}
