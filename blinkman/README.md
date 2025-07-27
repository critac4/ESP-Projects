This project blinks the onboard LED of the NodeMCU ESP32WROOM32, sold by AZ-Delivery. (Can find relevant docs on their website).


main/main.c is where your code lives, everything else is for esp-idf compile and built pipeline.

In this particular model, the onboard LED is connected to the U0TXD pin by default, which is activated whenever anything is being transmitted, over microusb. Hence the LED lights up whenever anything is being transmitted over the USB. 
The U0TXD corresponds to the GPIO #1 pin, and can perform multiple fucntions, out of which GPIO1 is set as fucntion 2. To set this pin as GPIO1, refer to the section 6.10 in the technical reference manual. 
The function of the U0TXD can be changed by using the IO_MUX_U0TXD_REG register at 0x3ff49088. Refer to the esp32 technical reference document as to why the bit 13 is being set as 1

To use GPIO, first enable GPIO register, then we write into the GPIO register.

The delay is set using the vTaskDelay(__ticks__) function part of the FreeRTOS running on the esp32 MCU.
