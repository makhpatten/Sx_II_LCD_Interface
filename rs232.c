int txOverruns=0;

void pushByteToTxBuffer(char b) {
   if (txBufferSize<TX_BUFFER_SIZE) {
      disable_interrupts(INT_TBE); //disable the RS232 transmit interrupt
      txBuffer[txBufferWriteIndex]=b;
      txBufferWriteIndex++;
      if (txBufferWriteIndex>=TX_BUFFER_SIZE) txBufferWriteIndex=0;
      txBufferSize++;
      enable_interrupts(INT_TBE); //disable the RS232 transmit interrupt
   } else {
      txOverruns++;
   }
}


char popCharFromInBuff() {
   char oneChar;
   oneChar=rxBuffer[rxBufReadIndex++];
   if (rxBufReadIndex>=RX_BUFFER_SIZE) {
      rxBufReadIndex=0;
   }
   rxBufSize--;
   return(oneChar);
}

//-----------------------------------------------------
#int_TBE // interrupt = uC's transmit byte buffer is empty
TBE_isr() {
   if (txBufferSize==0) {
      disable_interrupts(INT_TBE); //disable the RS232 transmit interrupt
   } else {
      putc(txBuffer[txBufferReadIndex]); //copy byte at current read index to transmit buffer
      txBufferReadIndex++;
      if (txBufferReadIndex>=TX_BUFFER_SIZE) txBufferReadIndex=0;
      txBufferSize--;
   }
}

//-----------------------------------------------------
#byte      RCSTA = 0xfab   // Receive Status and Control Register
#define  CREN   4
#define  OERR   1           // EUSART Overrun Error Bit

#int_RDA // RS232 receive data available
RDA_isr()
{              //MAKE SURE THIS INTERRUPT IS DISABLED, BUT ONLY BRIEFLY, DURING COMMAND READS!!!!!!!!
   unsigned int nReceived_Byte;

   nReceived_Byte = getch();                   // read the current received byte

   if(rxBufSize<RX_BUFFER_SIZE) // i.e. if the RS232 is not full
   {
      rxBuffer[rxBufWriteIndex]=nReceived_Byte;
      rxBufWriteIndex++;
      if (rxBufWriteIndex>=RX_BUFFER_SIZE) {
         rxBufWriteIndex=0;
      }
      rxBufSize++;
   }

   if(bit_test(RCSTA,OERR))   // if there's an overrun error, clear it.
   {
      bit_clear(RCSTA,CREN);
      bit_set(RCSTA,CREN);
      rxBufOverrunCount++;
   }
}