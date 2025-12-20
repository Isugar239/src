#pragma once
#include "project_config.h"

class GPIO
{
	public:
	GPIO(GPIO_TypeDef* GPIOx, 
	uint32_t GPIO_pin_num, 
  GPIOMode_TypeDef modeGPIO,
  GPIOSpeed_TypeDef speedGPIO,
  GPIOOType_TypeDef otypeGPIO,
  GPIOPuPd_TypeDef pupdGPIO,
  uint8_t AF_GPIO = 0);
	
	void setMode(GPIOMode_TypeDef modeGPIO);
	void setSpeed(GPIOSpeed_TypeDef speedGPIO);
	void setOType(GPIOOType_TypeDef otypeGPIO);
	void setPUPD(GPIOPuPd_TypeDef pupdGPIO);
	void writeGPIO(uint32_t pin, bool value);
	void pwmInit(uint8_t RCC_TIMx, uint16_t prescaller, uint16_t period, uint8_t channel, TIM_TypeDef* TIMx);
	void pwm(uint32_t pulse);
	void pwmSetDutyCycle(uint8_t dutyCycle); // Установка скважности в процентах (0-100)
	void pwmStart(void); // Запуск ШИМ
	void pwmStop(void); // Остановка ШИМ
	uint16_t pwmGetPeriod(void); // Получение периода ШИМ
			private:

	GPIO_TypeDef* _GPIOx;
	uint32_t _pinNumber;
	GPIOMode_TypeDef _modeGPIO;
	GPIOSpeed_TypeDef _speedGPIO;
	GPIOOType_TypeDef _otypeGPIO;
	GPIOPuPd_TypeDef _pupdGPIO;
	uint16_t _pinSourceGPIO;		
	uint8_t _ch;
	TIM_TypeDef* _TIMx;
	uint16_t _pwmPeriod; // Период ШИМ для вычисления скважности
	
};
