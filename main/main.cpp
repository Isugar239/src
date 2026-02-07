#include "project_config.h"
#include "../New Folder/GPIO.h"
#include "../UART/uart.h"
#include "../Time/Time.h"

int main()

{
  SystemInit(); 
  TimeHandler::init();
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	GPIO RX_pin = GPIO(GPIOC, GPIO_Pin_6, GPIO_Mode_AF, GPIO_Speed_100MHz, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_AF_USART6);
	GPIO TX_pin = GPIO(GPIOC, GPIO_Pin_7, GPIO_Mode_AF, GPIO_Speed_100MHz, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_AF_USART6);

	usart6::usart6Init(115200, 8, 1.0);
	volatile uint16_t data;
	while(1){
		TimeHandler::delay_ms(1);
		 data = usart6::read();
 		usart6::write(52); 
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

