#include "ADC.h"

Adc::Adc(ADC_TypeDef* ADCx,
		uint8_t numberOfChannels,
		uint8_t curChannel,
		uint32_t RCC_APB2Periph_ADCx,
		uint8_t num_of_cycles)
{
	m_ADCx = ADCx;
	m_numberOfChannels = numberOfChannels;
	m_curChannel = curChannel;
	m_RCC_APB2Periph_ADCx = RCC_APB2Periph_ADCx;
	cur = 0;
	
	switch(curChannel) {
		case 0: m_ADC_Channel_x = ADC_Channel_0; break;
		case 1: m_ADC_Channel_x = ADC_Channel_1; break;
		case 2: m_ADC_Channel_x = ADC_Channel_2; break;
		case 3: m_ADC_Channel_x = ADC_Channel_3; break;
		case 4: m_ADC_Channel_x = ADC_Channel_4; break;
		case 5: m_ADC_Channel_x = ADC_Channel_5; break;
		case 6: m_ADC_Channel_x = ADC_Channel_6; break;
		case 7: m_ADC_Channel_x = ADC_Channel_7; break;
		case 8: m_ADC_Channel_x = ADC_Channel_8; break;
		case 9: m_ADC_Channel_x = ADC_Channel_9; break;
		case 10: m_ADC_Channel_x = ADC_Channel_10; break;
		case 11: m_ADC_Channel_x = ADC_Channel_11; break;
		case 12: m_ADC_Channel_x = ADC_Channel_12; break;
		case 13: m_ADC_Channel_x = ADC_Channel_13; break;
		case 14: m_ADC_Channel_x = ADC_Channel_14; break;
		case 15: m_ADC_Channel_x = ADC_Channel_15; break;
		case 16: m_ADC_Channel_x = ADC_Channel_16; break;
		case 17: m_ADC_Channel_x = ADC_Channel_17; break;
		case 18: m_ADC_Channel_x = ADC_Channel_18; break;
		default: m_ADC_Channel_x = ADC_Channel_0; break;
	}
	
	channel[0] = curChannel;
}

void Adc::adcInit(uint8_t _num_of_cycles)
{
	// Инициализация общего блока ADC
	ADC_CommonInitTypeDef my_ADC;
	my_ADC.ADC_Mode = ADC_Mode_Independent;
	my_ADC.ADC_Prescaler = ADC_Prescaler_Div4;
	my_ADC.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_15Cycles;
	ADC_CommonInit(&my_ADC);
	
	// Инициализация конкретного ADC
	ADC_InitTypeDef adc;
	adc.ADC_Resolution = ADC_Resolution_12b;
	adc.ADC_ScanConvMode = ENABLE;
	adc.ADC_ContinuousConvMode = ENABLE;
	adc.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
	adc.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T3_TRGO;
	adc.ADC_DataAlign = ADC_DataAlign_Right;
	adc.ADC_NbrOfConversion = m_numberOfChannels;
	ADC_Init(m_ADCx, &adc);
}

void Adc::setChannel()
{
	ADC_RegularChannelConfig(m_ADCx, m_ADC_Channel_x, 1, ADC_SampleTime_56Cycles);
}

void Adc::startAdc()
{
	ADC_Cmd(m_ADCx, ENABLE);
	ADC_SoftwareStartConv(m_ADCx);
}

ADC_TypeDef* Adc::getAdc()
{
	return m_ADCx;
}

