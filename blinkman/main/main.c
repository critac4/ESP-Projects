#include "freertos/FreeRTOS.h"
#include <stdio.h>
#include "freertos/task.h"

#define IO_MUX_U0TXD_REG ((volatile uint32_t *)0x3FF49088)
#define GPIO_OUT_W1TS_REG ((volatile uint32_t *)0x3FF44008)
#define GPIO_OUT_W1TC_REG ((volatile uint32_t *)0x3FF4400c)
#define GPIO_ENABLE_W1TS_REG ((volatile uint32_t *)0x3FF44024)


//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

//  THE SERIAL WILL NOT WORK SINCE THE U0TXD IS RECONFIGURED TO THE GPIO1 PIN
//  AND SINCE ONLY ONE PIN CONNECTS TO THE CP2102 (THE U0TXD PIN.. ) AS LONG AS ITS 
//  CONFIGURED AS GPIO1, THE SERIAL WILL NOT WORK.

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


void led_on()
{
    // 2. Drive GPIO1 HIGH
    *GPIO_OUT_W1TS_REG = (1 << 1); // GPIO_OUT_W1TS_REG
    //printf("LED ON\n");
}

void led_off()
{
    // 2. Drive GPIO1 HIGH
    *GPIO_OUT_W1TC_REG = (1 << 1); // GPIO_OUT_W1TC_REG
    //printf("LED OFF\n");
}

void app_main(void)
{
    // set IO MUX GPIO #1 as GPIO1 pin directly from IO_MUX by changing the function of the
    //  pin from "function 0" {U0TXD} to "function 2" {GPIO1}
    //  This is done by setting the 13th bit of IO_MUX_U0TXD_REG to 1
    *IO_MUX_U0TXD_REG = (1 << 13);

    // 1. Enable output driver for GPIO1
    *GPIO_ENABLE_W1TS_REG = (1 << 1); // GPIO_ENABLE_W1TS_REG

    // // 2. Drive GPIO2 HIGH
    // *((volatile uint32_t *)0x3FF44008) = (1 << 1);  // GPIO_OUT_W1TS_REG

    // // 3. Drive GPIO1 LOW
    // *((volatile uint32_t *)0x3FF4400c) = (1 << 1);  // GPIO_OUT_W1TC_REG

    // 3. Prevent task watchdog panic by delaying
    while (1)
    {

        led_on();
        vTaskDelay(1000 / portTICK_PERIOD_MS); // Sleep for 1 second

        led_off();
        vTaskDelay(3000 / portTICK_PERIOD_MS); // Sleep for 1 second

        //printf("Hello, world!\n");
        // vTaskDelay(1000 / portTICK_PERIOD_MS);  // Sleep for 1 second

    }
}
