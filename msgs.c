void readInputMsg() {
   if (msgSync==0) {
      resyncMsg();
   }
   if (msgSync==1) {
      while (rxBufSize>0) {
         inputMsg[msgIndex]=popCharFromInBuff(); // get a message character from the COM input buffer
         if (msgIndex>=2) { // if we are after the first 2 characters (at the parameters)
            inputMsgParams[msgIndex-2]=inputMsg[msgIndex];   // copy parameters of input message to their own buffer
         }
         msgIndex++;
         if (msgIndex==2) { // if we've read in two characters already...
            determineMsgType(); // determine the message type
//			if(mtlindex<50) {
//               msgTypeLog[mtlindex++]=msgType;
//            }       
            if (msgType==CMD_UNKNOWN) { // if invalid message type
               msgSync=0; // reset sync next time
               return;
            }
         }
         
         if (msgIndex>=msgLength && msgLength!=0) { // if we have read in a complete message
            if (Check_CRC(inputMsg,msgLength)==1) { // if CRC is OK
               processMsg(); // process message
               msgIndex=0; // reset message index
               return;
            } else {
               msgSync=0; // bad CRC---reset sync next time
               return;
            }
         }
      }
   }
}   

//=============================================================================================================
void determineMsgType() {
   int msgTypeByte1;
   int msgTypeByte2;

   msgTypeByte1=inputMsg[0];msgTypeByte2=inputMsg[1];
   msgType=CMD_UNKNOWN;
      
   if (msgTypeByte1==RESP_STATUS_REQ_1 && msgTypeByte2==RESP_STATUS_REQ_2) {
      msgType=CMD_STATUS_REQ;
      msgLength=RESP_STATUS_REQ_LEN;
      return;
   }
   if (msgTypeByte1==RESP_CONFIG_REQ_1 && msgTypeByte2==RESP_CONFIG_REQ_2) {
      msgType=CMD_CONFIG_REQ;
      msgLength=RESP_CONFIG_REQ_LEN;
         return;
   }
   if (msgTypeByte1==RESP_MISC_INFO_1 && msgTypeByte2==RESP_MISC_INFO_2) {
      msgType=CMD_MISC_INST;
      msgLength=RESP_MISC_INFO_LEN;
      return;
   }
   if (msgTypeByte1==RESP_SWEEP_RESP_1 && msgTypeByte2==RESP_SWEEP_RESP_2) {
      msgType=CMD_SWEEP;
      msgLength=RESP_SWEEP_LEN;
      return;
   }
}
//=============================================================================================================
int toggles=0;
void toggleMonoStereo() {
   if (monoMode==0) monoMode=1;
   else monoMode=0;
   toggles++;
}
//=============================================================================================================
void processMsg() {
   switch (msgType) {
      case CMD_STATUS_REQ: { // Freq/status response
         statusMsgTimer=0; // restart timer
         processStatusReq(); //process freq/status response parameters
         checkChannelChange();
 
         break;
      }
      case CMD_CONFIG_REQ: { //Set configuration response
         configMsgTimer=0; // restart timer
         oneConfigReceivedFlag=1;
         processConfigReqParams(); //process config response parameters
         break;
      }
      case CMD_MISC_INST: { //Set configuration response
         miscMsgTimer=0; // restart timer
         processMiscInstParams(); //process misc info response parameters
         break;
      }
      case CMD_SWEEP: { // If its sweeping, reset all timers so we won't generate a "rs", "cd" or "ct" and interrupt the external GUI
         miscMsgTimer=0; // restart timer
         configMsgTimer=0; // restart timer
         statusMsgTimer=0; // restart timer
         break;
      }
   }
}

//=============================================================================================================
signed int muteResponseCount=0;

void processStatusReq() {
   statusByte1=inputMsg[5];
   statusByte2=inputMsg[6];


   findChannelNumber();
   computeRSSILevels();
   if ((statusByte1&0x40)!=0) {
      rcvdMonoMode=0;
   } else {
      rcvdMonoMode=1;
   }
   if ((statusByte1&0x20)!=0) {
      maxRange=1;
   } else {     
      maxRange=0;
   }
   if ((statusByte1&0x10)!=0) {
      calToneMode=1;
   } else {     
      calToneMode=0;
   }
//   if ((inputMsg[5]&0x10)!=0) {
//      toneMode=2;
//   } else {     
   if ((statusByte2&0x02)!=0) {
      reportedToneNoLockMode=1;
   } else {
      reportedToneNoLockMode=0;
   }
//   }
   filterNumber=inputMsg[5]&0x07;
   vuLeft=inputMsg[10];
   vuRight=inputMsg[11];

   if ((inputMsg[6]&0x05)!=0) { // if either "mute headphone" or "mute analog and headphone" selected we should be in off power state
      if (displayPowerState==1) { // if display power on...
         muteResponseCount++; // increment counter
         if (muteResponseCount>2) { // if two or more responses indicate off power state...
            muteResponseCount=0; // clear counter for nexte time
            displayPowerState=0; // set off power state
            write_eeprom(EEPROM_ADDR_DISP_PWR_STATE,displayPowerState); // save it in the EEPROM
            setDisplayPowerState(); // set the power state
         }
      } else muteResponseCount=0; // clear counter
   } else { //  
      if (displayPowerState==0) { // if display power off...
         muteResponseCount++; // increment counter
         if (muteResponseCount>2) { // two or more responses counter indicate on power state
            muteResponseCount=0; // clear counter for next time
            displayPowerState=1; // set on power state
            write_eeprom(EEPROM_ADDR_DISP_PWR_STATE,displayPowerState); // save it in the EEPROM
            setDisplayPowerState(); // set the power stae
         }
      } else muteResponseCount=0; // clear counter
   } 

   updateDisplay();
}
//=============================================================================================================
void checkChannelChange() {
   if (channelChangeFlag>0) { // if channel just changed then see if locked
            if (channelNumber==rcvdChannelNumber && monoMode==rcvdMonoMode) { // if received channel is the desired channel...
               channelChangeTimeoutTimer=0; // restart the time out timer for waiting for desired channel and mode...
               if ((lockA+lockB)==0) {  // if neither channel locked
                  channelChangeFlag++; // increment flag to count ST messages: 2 means one ST message received, etc.
                  if (channelChangeFlag==2) { // after 1 ST message without a lock
                     toggleMonoStereo(); // try toggling mode
                     writeFreqOperCmd(); // change mode
                  }
                  if (channelChangeFlag==3) { // after 1 more ST message without a lock, even after toggling mode...
                     toggleMonoStereo(); // toggle mode back
                     if (scanFlag==1) {
                        incrementChannel(); // if scanning, increment channel
                        channelChangeFlag=1; // indicate a new channel change
                        channelChangeTimeoutTimer=0; // reset timeout counter
                     } else if (scanFlag==2) {
                        decrementChannel(); // if scanning, decrement channel
                        channelChangeFlag=1; // indicate a new channel change
                        channelChangeTimeoutTimer=0; // reset timeout counter
                     } else {
                        channelChangeFlag=0; // if not scanning, end all this toggling modes stuff.
                     }
                     writeFreqOperCmd();
                  }
               } else {
                  if (scanFlag!=0 || channelChangeFlag!=0) { // if currently scanning or changing channel
                     scanFlag=0; // stop scanning
                     channelChangeFlag=0; // we have lock so stop trying other modes (mono or stereo)
                     writeFreqOperCmd(); // we need to send another freqOp to unmute because we were muted during scan
                  }
               } 
            }
         }
}
//=============================================================================================================
void processConfigReqParams() {
   rxVoltage=(unsigned int)inputMsg[15];
//   rxVoltage++;
}
//=============================================================================================================
void processMiscInstParams() {
}
//=============================================================================================================
void findChannelNumber() {
   int i;
   char testVal1x,testVal2x,testVal3x;
   for (i=0;i<NUM_CHANNELS;i++) {
      testVal1x=read_eeprom(i*3+0);
      testVal2x=read_eeprom(i*3+1);
      testVal3x=read_eeprom(i*3+2);
      if (inputMsg[2]==testVal1x && inputMsg[3]==testVal2x && inputMsg[4]==testVal3x) {
         if (rcvdChannelNumber>=NUM_CHANNELS) { // if channel number is going from invalid to valid...
            channelNumber=i; // initialize desired channel number to this new valid channel
         }
         rcvdChannelNumber=i;
         return;
      }
   }
   rcvdChannelNumber=99; // indicates invalid channel
}
//=============================================================================================================
int testCounter=0;

void computeRSSILevels() {

// testing:
//   inputMsg[8]=testCounter;
//   inputMsg[9]=testCounter++;

   lockA=0;
   lockB=0; 
   if ((inputMsg[8]&0x80)!=0) {
      rssiA=127-(inputMsg[8]&0x7F);
   } else {
      lockA=1; // 
      rssiA=inputMsg[8]&0x7F;
   }
   if ((inputMsg[9]&0x80)!=0) {
      rssiB=127-(inputMsg[9]&0x7F);
   } else {
      lockB=1; // 
      rssiB=inputMsg[9]&0x7F;
   }
}


//=============================================================================================================
#define VALID_MSG_FIRST_CHAR1 's'
//#define VALID_MSG_FIRST_CHAR2 'r'

void resyncMsg() {
   char msgTypeByte1;
   msgIndex=0;
   while (rxBufSize>0 && msgSync==0) {
     msgTypeByte1=popCharFromInBuff();
     if (msgTypeByte1==VALID_MSG_FIRST_CHAR1) {
        msgSync=1;
        msgIndex=1;
        inputMsg[0]=msgTypeByte1;
     }
   }
}
//=============================================================================================================
#define TXSTA 0x0fac

void writeOutputMsgs() {
   if (!input(RS232_DETECT)) {
      if (statusMsgTimer>STATUS_MESSAGE_REPEAT_TIME) { // if it's been too long since a status message has arrived...
         statusMsgTimer=0; // restart timer
         writeRequestStatusCmd(); // request status
      }
      if (configMsgTimer>CONFIG_MESSAGE_REPEAT_TIME) { // if it's been too long since a config message has arrived...
         configMsgTimer=0; // restart timer
         writeRequestConfigCmd(); // request config
      }
      if (miscMsgTimer>MISC_INST_MESSAGE_REPEAT_TIME) { // if it's been too long since a misc. instructions message has arrived...
         miscMsgTimer=0; // restart timer
         writeRequestMiscCmd(); // request misc instructions
      }
//   } else if (oneConfigReceivedFlag==0) { // even if RS232 is detected, send config requests until we get at least one...
//      if (configMsgTimer>CONFIG_MESSAGE_REPEAT_TIME) { // if it's been too long since a config message has arrived...
//         configMsgTimer=0; // restart timer
//         writeRequestConfigCmd(); // request config
//      }
   }
   if (channelChangeFlag>0) {
      if (channelChangeTimeoutTimer>CHANNEL_CHANGE_TIMEOUT) {
         channelChangeTimeoutTimer=0;
         writeFreqOperCmd(); // resend freqOp command since it evidently got lost
      }
   }


   if (transmittingFlag!=0) {
      if (((*TXSTA)&0x02)!=0) {
         transmittingFlag=0;
         delay_ms(1);
         output_low(WRITE_MSG_ENABLE);
      }
   }
}

//=============================================================================================================
void writeRequestStatusCmd() {
   outputMsg[0]='r';
   outputMsg[1]='s';
   writeMsg(4);
}
//=============================================================================================================
void writeFreqOperCmd() {
   outputMsg[0]='c';
   outputMsg[1]='s';
   outputMsg[2]=read_eeprom(3*channelNumber+0);
   outputMsg[3]=read_eeprom(3*channelNumber+1);
   outputMsg[4]=read_eeprom(3*channelNumber+2);
   outputMsg[5]=filterNumber;
   outputMsg[5]|=0x80; // receiver on bit
   if (calToneMode!=0) {
      outputMsg[5]|=0x10;
   }
   if (monoMode==0) {
      outputMsg[5]|=0x40;
   }
   if (maxRange!=0) {
      outputMsg[5]|=0x20;
   }

   outputMsg[6]=0;
   if (desiredToneNoLockMode==1) {
      if (scanFlag!=0 || channelChangeFlag!=0) { // if scanning or just changed channels
         channelChangeMuteFlag=1; // don't set tone no lock, but set flag indicating that it will need to be set when stopping scan or channel change
      } else {
         outputMsg[6]|=0x02; // set tone no lock
      }
   }

   if (muteMode==1) {  // if mute mode selected
      outputMsg[6]|=0x05; // mute both headphones and analog output
   }

   writeMsg(9);
}

//=============================================================================================================
void writeRequestConfigCmd() {
   outputMsg[0]='c';
   outputMsg[1]='d';
   writeMsg(4);
}

//=============================================================================================================
void writeRequestMiscCmd() {
   outputMsg[0]='c';
   outputMsg[1]='t';
   writeMsg(12);
}

//=============================================================================================================
void writeMsg(int msgLength) {
   int nCount;
   int16 lCRC_value;
   lCRC_value = Use_Crc(outputMsg, (msgLength-2));
   outputMsg[msgLength-2] = make8(lCRC_value,1);    // MSByte of CRC
   outputMsg[msgLength-1] = make8(lCRC_value,0);    // LSByte  "  "
// enable message output and delay to make sure any external messages are reset
   transmittingFlag=1;
   output_high(WRITE_MSG_ENABLE);
   delay_ms(10);
   for (nCount=0; nCount < msgLength; nCount++)  {
      pushByteToTxBuffer(outputMsg[nCount]);
   }
// send it twice for safety reasons
   for (nCount=0; nCount < msgLength; nCount++)  {
      pushByteToTxBuffer(outputMsg[nCount]);
   }
}

// =============================================================================================================
void Crc_Update(long data_ptr, unsigned int16 *accum)
{
   static const unsigned int16 crctab []  =
           { // this table requires 512 Bytes of storage
           0x0000, 0x1021, 0x2042, 0x3063, 0x4084, 0x50a5, 0x60c6, 0x70e7,
           0x8108, 0x9129, 0xa14a, 0xb16b, 0xc18c, 0xd1ad, 0xe1ce, 0xf1ef,
           0x1231, 0x0210, 0x3273, 0x2252, 0x52b5, 0x4294, 0x72f7, 0x62d6,
           0x9339, 0x8318, 0xb37b, 0xa35a, 0xd3bd, 0xc39c, 0xf3ff, 0xe3de,
           0x2462, 0x3443, 0x0420, 0x1401, 0x64e6, 0x74c7, 0x44a4, 0x5485,
           0xa56a, 0xb54b, 0x8528, 0x9509, 0xe5ee, 0xf5cf, 0xc5ac, 0xd58d,
           0x3653, 0x2672, 0x1611, 0x0630, 0x76d7, 0x66f6, 0x5695, 0x46b4,
           0xb75b, 0xa77a, 0x9719, 0x8738, 0xf7df, 0xe7fe, 0xd79d, 0xc7bc,
           0x48c4, 0x58e5, 0x6886, 0x78a7, 0x0840, 0x1861, 0x2802, 0x3823,
           0xc9cc, 0xd9ed, 0xe98e, 0xf9af, 0x8948, 0x9969, 0xa90a, 0xb92b,
           0x5af5, 0x4ad4, 0x7ab7, 0x6a96, 0x1a71, 0x0a50, 0x3a33, 0x2a12,
           0xdbfd, 0xcbdc, 0xfbbf, 0xeb9e, 0x9b79, 0x8b58, 0xbb3b, 0xab1a,
           0x6ca6, 0x7c87, 0x4ce4, 0x5cc5, 0x2c22, 0x3c03, 0x0c60, 0x1c41,
           0xedae, 0xfd8f, 0xcdec, 0xddcd, 0xad2a, 0xbd0b, 0x8d68, 0x9d49,
           0x7e97, 0x6eb6, 0x5ed5, 0x4ef4, 0x3e13, 0x2e32, 0x1e51, 0x0e70,
           0xff9f, 0xefbe, 0xdfdd, 0xcffc, 0xbf1b, 0xaf3a, 0x9f59, 0x8f78,
           0x9188, 0x81a9, 0xb1ca, 0xa1eb, 0xd10c, 0xc12d, 0xf14e, 0xe16f,
           0x1080, 0x00a1, 0x30c2, 0x20e3, 0x5004, 0x4025, 0x7046, 0x6067,
           0x83b9, 0x9398, 0xa3fb, 0xb3da, 0xc33d, 0xd31c, 0xe37f, 0xf35e,
           0x02b1, 0x1290, 0x22f3, 0x32d2, 0x4235, 0x5214, 0x6277, 0x7256,
           0xb5ea, 0xa5cb, 0x95a8, 0x8589, 0xf56e, 0xe54f, 0xd52c, 0xc50d,
           0x34e2, 0x24c3, 0x14a0, 0x0481, 0x7466, 0x6447, 0x5424, 0x4405,
           0xa7db, 0xb7fa, 0x8799, 0x97b8, 0xe75f, 0xf77e, 0xc71d, 0xd73c,
           0x26d3, 0x36f2, 0x0691, 0x16b0, 0x6657, 0x7676, 0x4615, 0x5634,
           0xd94c, 0xc96d, 0xf90e, 0xe92f, 0x99c8, 0x89e9, 0xb98a, 0xa9ab,
           0x5844, 0x4865, 0x7806, 0x6827, 0x18c0, 0x08e1, 0x3882, 0x28a3,
           0xcb7d, 0xdb5c, 0xeb3f, 0xfb1e, 0x8bf9, 0x9bd8, 0xabbb, 0xbb9a,
           0x4a75, 0x5a54, 0x6a37, 0x7a16, 0x0af1, 0x1ad0, 0x2ab3, 0x3a92,
           0xfd2e, 0xed0f, 0xdd6c, 0xcd4d, 0xbdaa, 0xad8b, 0x9de8, 0x8dc9,
           0x7c26, 0x6c07, 0x5c64, 0x4c45, 0x3ca2, 0x2c83, 0x1ce0, 0x0cc1,
           0xef1f, 0xff3e, 0xcf5d, 0xdf7c, 0xaf9b, 0xbfba, 0x8fd9, 0x9ff8,
           0x6e17, 0x7e36, 0x4e55, 0x5e74, 0x2e93, 0x3eb2, 0x0ed1, 0x1ef0
           };

 *accum = (*accum << 8) ^ crctab[(*accum >> 8) ^ data_ptr];

/*  accum is a ptr to type unsigned short ie 8 bit
     *accum dereferences accum i.e. change the value of the information at address *accum which keeps everything
     as a type unsigned short - Otherwise the shift is treated like a 12 bit shift and shift left of the
     value FFEEgives FFEE00 instead of the desired EE00*/
}

//=============================================================================================================
unsigned int16 Use_Crc(unsigned char *Buffer, int BuffLength)
{
   unsigned int i;
   unsigned int16 crcValue = 0xFFFF;

   for (i=0; i<BuffLength; i++)   Crc_Update(Buffer[i], &crcValue);

   return crcValue;
}
//=============================================================================================================

BOOLEAN Check_CRC(unsigned char *Buffer, int BuffLength)
{

 if (Use_Crc(Buffer, BuffLength) == 0) return true;
 else                                  return false;
}
