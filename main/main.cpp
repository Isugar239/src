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
	
	while(1){
		TimeHandler::delay_ms(1000);
		uint16_t data = usart6::read();
 		usart6::write(49); 
	}

}

