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

//basic program to test a change in the GPIO0

static void configure_GPIO(void)
{
	//reset an io
	gpio_reset_pin(GPIO_0);
	//set GPIO_0 as an output
	gpio_set_direction(GPIO_0, GPIO_MODE_OUTPUT);
}



void app_main(void)
{
	configure_GPIO();
    while (true) {
        printf("Hello from app_main!\n");
        //changes gpio0 to 1
        gpio_set_level(GPIO_0, 1);
        for (int i = 10; i >= 0; i--) {
        	printf("output off in %d seconds...\n", i);
        	vTaskDelay(4000 / portTICK_PERIOD_MS);
           }
        //changes gpio0 to 0
        gpio_set_level(GPIO_0, 0);
        for (int i = 10; i >= 0; i--) {
        	printf("output on in %d seconds...\n", i);
        	vTaskDelay(4000 / portTICK_PERIOD_MS);
        }



    }
}
