namespace usart6
{
	void usart6Init(uint32_t speed, uint8_t word_length, float stop_bits);
	void write(uint8_t byte);
	uint16_t read();
	uint16_t available();
	uint16_t look();
	// our buffers
	extern volatile uint8_t rx[30];
	extern volatile uint8_t tx[30];
	
	// 
	extern volatile uint16_t _rxCount;
	extern volatile uint16_t _txCount;
	
	extern volatile bool flag;
	
	
	extern volatile uint16_t _readCount;
	extern volatile uint16_t _sendCount;
	
	extern volatile uint8_t _bytesToSend;
	extern volatile uint32_t _tets;
	//very important thing!!!
	  extern volatile bool _receiver_buffer_overflow_warning;
}