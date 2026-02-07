#include "project_config.h"
#include "uart.h"

extern "C" void USART6_IRQHandler(void)
{
    if (USART_GetITStatus(USART6, USART_IT_TXE) == SET) {
        if (usart6::_bytesToSend > 0) {
            usart6::_bytesToSend--;
            USART_SendData(USART6, usart6::tx[usart6::_sendCount++]);
            if (usart6::_sendCount >= 30) {
                usart6::_sendCount = 0;
            }
        }
        else {
            USART_ITConfig(USART6, USART_IT_TXE, DISABLE);
        }
    }
    if (USART_GetITStatus(USART6, USART_IT_RXNE) == SET) //Receive part - Приемник не пуст, флаг IT_RXNE - Interruptiob RX Not Empty
    {
        if ((USART6->SR & (USART_FLAG_NE | USART_FLAG_FE | USART_FLAG_PE | USART_FLAG_ORE)) != 0) // Проверка корректности приема байта
        {
            USART_ReceiveData(USART6);//Если ошибка - просто пропусти байт
        }
        else {
            usart6::rx[usart6::_rxCount] = USART_ReceiveData(USART6);//Иначе прочитай байт и смести указатель в массиве
            usart6::_rxCount++;
            usart6::_bytesToRead++;
            if (usart6::_bytesToRead > 30) {
                usart6::_bytesToRead = 30;
            }
            if (usart6::_rxCount >= 30) {
                usart6::_rxCount = 0;
            }
        }
    }
}

namespace usart6
{
    // our buffers
    volatile uint8_t rx[30];
    volatile uint8_t tx[30];

    //
    volatile uint16_t _rxCount;
    volatile uint16_t _txCount;

    volatile bool flag;

    volatile uint16_t _readCount;
    volatile uint16_t _sendCount;

    volatile uint8_t _bytesToRead;
    volatile uint8_t _bytesToSend;
    volatile uint32_t _tets;
    //very important thing!!!
    volatile bool _receiver_buffer_overflow_warning;

    void write(uint8_t byte)
    {
        while (USART_GetFlagStatus(USART6, USART_FLAG_TXE) == RESET);
        USART_SendData(USART6, byte);
        while (USART_GetFlagStatus(USART6, USART_FLAG_TC) == RESET);
    }

    // read from our buffer
    uint16_t read()
    {
        if (_bytesToRead == 0) {
            return 0; // Нет данных для чтения
        }
        uint16_t data;
        ENTER_CRITICAL_SECTION();
        data = rx[_readCount];
        _readCount++;
        if (_readCount >= 30) {
            _readCount = 0;
        }
        _bytesToRead--;
        EXIT_CRITICAL_SECTION();
        return data;
    }

    //look
    uint16_t look()
    {
        uint16_t dat;
        ENTER_CRITICAL_SECTION();
        dat = rx[_readCount];
        EXIT_CRITICAL_SECTION();
        return dat;
    }

    uint16_t available()
    {
        return _bytesToRead; // Просто возвращаем количество байт для чтения
    }

    void usart6Init(uint32_t speed, uint8_t word_length, float stop_bits)
    {
        _txCount = 0;
        _rxCount = 0;
        flag = 1;
        _readCount = 0;
        _sendCount = 0;
        _bytesToRead = 0;
        _bytesToSend = 0;
        _receiver_buffer_overflow_warning = false;
        USART_InitTypeDef u6;
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART6, ENABLE);

        // Используем переданные параметры
        u6.USART_BaudRate = speed;
        u6.USART_WordLength = (word_length == 9) ? USART_WordLength_9b : USART_WordLength_8b;
        u6.USART_StopBits = (stop_bits == 2.0) ? USART_StopBits_2 : USART_StopBits_1;
        u6.USART_Parity = USART_Parity_No;
        u6.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
        u6.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
        USART_Init(USART6, &u6);


        //INTERUUUUUUUUUUUUPT
        NVIC_InitTypeDef NVIC_structure;
        NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
        NVIC_structure.NVIC_IRQChannel = USART6_IRQn;
        NVIC_structure.NVIC_IRQChannelCmd = ENABLE;
        NVIC_structure.NVIC_IRQChannelPreemptionPriority = 0;
        NVIC_structure.NVIC_IRQChannelSubPriority = 0;
        NVIC_Init(&NVIC_structure);
        USART_Cmd(USART6, ENABLE);
        USART_ITConfig(USART6, USART_IT_TXE, ENABLE);
        USART_ITConfig(USART6, USART_IT_RXNE, ENABLE);
    }
}
