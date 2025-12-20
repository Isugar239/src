#include "GPIO.h"
#include "project_config.h"

GPIO::GPIO(GPIO_TypeDef* GPIOx,
uint32_t GPIO_pin_num, 
GPIOMode_TypeDef modeGPIO,
GPIOSpeed_TypeDef speedGPIO,
GPIOOType_TypeDef otypeGPIO,
GPIOPuPd_TypeDef pupdGPIO,
uint8_t AF_GPIO)
{
	GPIO_InitTypeDef _initParams;
	
    _initParams.GPIO_Pin = GPIO_pin_num;

    _initParams.GPIO_Mode = modeGPIO;
    _initParams.GPIO_Speed = speedGPIO;
    _initParams.GPIO_OType = otypeGPIO;
    _initParams.GPIO_PuPd = pupdGPIO;
		if(GPIOx == GPIOA){
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); 
        }
        if(GPIOx == GPIOB){
        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
        }
        if(GPIOx == GPIOC){
        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
        }
        if(GPIOx == GPIOD){
        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
        }
    GPIO_Init(GPIOx, &_initParams);
    
    // Инициализация переменных-членов класса
    _GPIOx = GPIOx;
    _pinNumber = GPIO_pin_num;
    _modeGPIO = modeGPIO;
    _speedGPIO = speedGPIO;
    _otypeGPIO = otypeGPIO;
    _pupdGPIO = pupdGPIO;
		
		if( _pinNumber == GPIO_Pin_0) { _pinSourceGPIO = GPIO_PinSource0;}
	else if( _pinNumber == GPIO_Pin_1)  {_pinSourceGPIO = GPIO_PinSource1;}
	else if( _pinNumber == GPIO_Pin_2)  {_pinSourceGPIO = GPIO_PinSource2;}
	else if( _pinNumber == GPIO_Pin_3)  {_pinSourceGPIO = GPIO_PinSource3;}
	else if( _pinNumber == GPIO_Pin_4)  {_pinSourceGPIO = GPIO_PinSource4;}
	else if( _pinNumber == GPIO_Pin_5)  {_pinSourceGPIO = GPIO_PinSource5;}
	else if( _pinNumber == GPIO_Pin_6)  {_pinSourceGPIO = GPIO_PinSource6;}
	else if( _pinNumber == GPIO_Pin_7)  {_pinSourceGPIO = GPIO_PinSource7;}
	else if( _pinNumber == GPIO_Pin_8)  {_pinSourceGPIO = GPIO_PinSource8;}
	else if( _pinNumber == GPIO_Pin_9)  {_pinSourceGPIO = GPIO_PinSource9;}
	else if( _pinNumber == GPIO_Pin_10)  {_pinSourceGPIO = GPIO_PinSource10;}
	else if( _pinNumber == GPIO_Pin_11)  {_pinSourceGPIO = GPIO_PinSource11;}
	else if( _pinNumber == GPIO_Pin_12)  {_pinSourceGPIO = GPIO_PinSource12;}
	else if( _pinNumber == GPIO_Pin_13)  {_pinSourceGPIO = GPIO_PinSource13;}
	else if( _pinNumber == GPIO_Pin_14)  {_pinSourceGPIO = GPIO_PinSource14;}
	else if( _pinNumber == GPIO_Pin_15)  {_pinSourceGPIO = GPIO_PinSource15;}
    if(_modeGPIO == GPIO_Mode_AF){
        GPIO_PinAFConfig(_GPIOx, _pinSourceGPIO, AF_GPIO);
    }
    
}
void GPIO::writeGPIO(uint32_t pin, bool value){
    if(value){
        GPIO_SetBits(_GPIOx, pin);
    }
    else{
        GPIO_ResetBits(_GPIOx, pin);
    }
}

void GPIO::pwmInit(uint8_t RCC_TIMx, uint16_t prescaller, uint16_t period, uint8_t channel, TIM_TypeDef* TIMx){
    _ch = channel;
    _TIMx = TIMx;
    _pwmPeriod = period; // Сохраняем период для вычисления скважности
    if(TIMx==TIM1){
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
    }
    if(TIMx==TIM2){
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    }
    if(TIMx==TIM3){
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
    }
    if(TIMx==TIM4){
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
    }
    if(TIMx==TIM5){
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
    }
    if(TIMx==TIM6){
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);
    }
    if(TIMx==TIM7){
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);
    }
    if(TIMx==TIM8){
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);
    }
    if(TIMx==TIM9){
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM9, ENABLE);
    }
    if(TIMx==TIM10){
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM10, ENABLE);
    }
    if(TIMx==TIM11){
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM11, ENABLE);
    }
    if(TIMx==TIM12){
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM12, ENABLE);
    }
    if(TIMx==TIM13){
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM13, ENABLE);
    }
    if(TIMx==TIM14){
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM14, ENABLE);
    }
    TIM_TimeBaseInitTypeDef TIM_InitStruct;

    TIM_InitStruct.TIM_Prescaler = prescaller;
    TIM_InitStruct.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_InitStruct.TIM_Period = period;
    TIM_InitStruct.TIM_ClockDivision = TIM_CKD_DIV1;

    TIM_TimeBaseInit(TIMx, &TIM_InitStruct);
    TIM_Cmd(TIMx, ENABLE);
    TIM_OCInitTypeDef ch; //ch ~ channel
    ch.TIM_OCMode = TIM_OCMode_PWM1;
    ch.TIM_OutputState = TIM_OutputState_Enable;
    ch.TIM_Pulse = 0;
    ch.TIM_OCPolarity = TIM_OCPolarity_High;
    ch.TIM_OCIdleState = TIM_OCIdleState_Reset;
    ch.TIM_OCNPolarity = TIM_OCNPolarity_Low;
    ch.TIM_OutputNState = TIM_OutputNState_Disable;
    ch.TIM_OCNIdleState = TIM_OCNIdleState_Set;
    
    if(channel==1){
        TIM_OC1Init(_TIMx, &ch);

    }
    else if(channel==2){
        TIM_OC2Init(_TIMx, &ch);
       
    }
    else if(channel==3){
        TIM_OC3Init(_TIMx, &ch);
    
    }
    else if(channel==4){
        TIM_OC4Init(_TIMx, &ch);
  
    }
}
    void GPIO::pwm(uint32_t pulse){
        if(_ch==1){
            TIM_SetCompare1(_TIMx, pulse);
        }
        else if(_ch==2){
        TIM_SetCompare2(_TIMx, pulse);
        }
        else if(_ch==3){
            TIM_SetCompare3(_TIMx, pulse);
        }
        else if(_ch==4){
            TIM_SetCompare4(_TIMx, pulse);
        }   
}

void GPIO::pwmSetDutyCycle(uint8_t dutyCycle){
    // Ограничиваем значение от 0 до 100
    if(dutyCycle > 100){
        dutyCycle = 100;
    }
    // Вычисляем значение pulse на основе процента скважности
    uint32_t pulse = (_pwmPeriod * dutyCycle) / 100;
    pwm(pulse);
}

void GPIO::pwmStart(void){
    if(_ch==1){
        TIM_CCxCmd(_TIMx, TIM_Channel_1, TIM_CCx_Enable);
    }
    else if(_ch==2){
        TIM_CCxCmd(_TIMx, TIM_Channel_2, TIM_CCx_Enable);
    }
    else if(_ch==3){
        TIM_CCxCmd(_TIMx, TIM_Channel_3, TIM_CCx_Enable);
    }
    else if(_ch==4){
        TIM_CCxCmd(_TIMx, TIM_Channel_4, TIM_CCx_Enable);
    }
}

void GPIO::pwmStop(void){
    if(_ch==1){
        TIM_CCxCmd(_TIMx, TIM_Channel_1, TIM_CCx_Disable);
    }
    else if(_ch==2){
        TIM_CCxCmd(_TIMx, TIM_Channel_2, TIM_CCx_Disable);
    }
    else if(_ch==3){
        TIM_CCxCmd(_TIMx, TIM_Channel_3, TIM_CCx_Disable);
    }
    else if(_ch==4){
        TIM_CCxCmd(_TIMx, TIM_Channel_4, TIM_CCx_Disable);
    }
}

uint16_t GPIO::pwmGetPeriod(void){
    return _pwmPeriod;
}