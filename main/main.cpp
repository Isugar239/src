#include "project_config.h"
#include "../New Folder/GPIO.h"
#include "../UART/uart.h"
#include "../Time/Time.h"
#include "../I2C/soft_i2c.h"
int main()

{
  SystemInit(); 
  TimeHandler::init();
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	GPIO SDA = GPIO(GPIOC, GPIO_Pin_6, GPIO_Mode_OUT, GPIO_Speed_100MHz, GPIO_OType_OD, GPIO_PuPd_UP);
	GPIO SCL = GPIO(GPIOC, GPIO_Pin_7, GPIO_Mode_OUT, GPIO_Speed_100MHz, GPIO_OType_OD, GPIO_PuPd_UP);
  soft_i2c i2c(SCL, SDA);
	TimeHandler::delay_ms(500);
	volatile uint8_t napr=52;
	volatile uint8_t strenth;

	while(1){
		TimeHandler::delay_ms(100);

    napr = i2c.readRegister(0x29, 0xC0); 
   strenth  = i2c.readRegister(0x29, 0xC1);

	}

}


uint8_t crc8(uint8_t* data, int len)
{
uint8_t src8 = 0xFF;

	for(int i = 0; i < len; i++){
		src8 ^= data[i];
		for(int j = 0; j < 8; j++){
		if(src8 & 0x80) {
		src8 = (char)((src8<<1) ^ 0x31) ;
		}
		else{
		src8 <<= 1;
		}
		}
	}
	return src8;
}


