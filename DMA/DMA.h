#include "stm32f4xx.h"
#include "stm32f4xx_dma.h"
#include "stm32f4xx_rcc.h"

class DMA_Controller {
public:
    DMA_Controller(DMA_Stream_TypeDef* stream, uint32_t channel);

    void InitP2M(uint32_t periphAddr, uint32_t memAddr, uint32_t bufferSize);
    
    void InitM2P(uint32_t memAddr, uint32_t periphAddr, uint32_t bufferSize);

    void Start();
    void Stop();
    bool IsTransferComplete();

private:
    DMA_Stream_TypeDef* _stream;
    uint32_t _channel;
    DMA_InitTypeDef _dmaInit;

    void EnableClock();
};