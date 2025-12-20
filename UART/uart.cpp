#include "project_config.h"
namespace usart6
{
   void write(uint8_t byte)
   {
      while (USART_GetFlagStatus(USART6, USART_FLAG_TXE) == RESET);
      USART_SendData(USART6, byte);
      while (USART_GetFlagStatus(USART6, USART_FLAG_TC) == RESET);
   }

   uint8_t read()
   {
      while (USART_GetFlagStatus(USART6, USART_FLAG_RXNE) == RESET);
      return USART_ReceiveData(USART6);
   }

   void usart6Init(uint32_t speed, uint8_t word_length, float stop_bits)
   {
      USART_InitTypeDef u6;
		  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART6, ENABLE);

      // Используем переданные параметры
      u6.USART_BaudRate = speed;
      u6.USART_WordLength = (word_length == 9) ? USART_WordLength_9b : USART_WordLength_8b;
      u6.USART_StopBits = (stop_bits == 2.0) ? USART_StopBits_2 : USART_StopBits_1;
      u6.USART_Parity = USART_Parity_No;
      u6.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
      u6.USART_Mode = USART_Mode_Tx | USART_Mode_Rx ;
      USART_Init(USART6, &u6);
      
      // Включаем UART
      USART_Cmd(USART6, ENABLE);
   }
}