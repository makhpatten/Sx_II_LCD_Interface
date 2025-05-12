//---------------------
// global variables
//---------------------
int counter=0;
int offset=0;
unsigned char txt0[81]=   "Chan -        --.- VA:         L:       B:         R:        ---  ------ ------";
//unsigned char txt0[161]="0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789";
int filterNumber=0;
int monoMode=0;
int calToneMode=0;
int rcvdMonoMode=0;
int maxRange=0;
int channelNumber=0;
int rcvdChannelNumber=99; // initialize to an invalid value
unsigned int16 rxID=0;
char tempStr[10];
int cursorLocation=99; // set to this value to indicate first time displayed to show serial number that time
unsigned int msCounter=0;
unsigned int displayUpdateTimer=0;
unsigned int channelChangeTimeoutTimer=0;
//unsigned int16 loopTimer=1;
//unsigned int16 loopTimer2=1;
unsigned int switchTimer=0;
//unsigned int16 switchValueDownTimer=0;
//unsigned int16 switchFunctUpTimer=0;
//unsigned int16 switchFunctDownTimer=0;
unsigned int statusMsgTimer;
unsigned int configMsgTimer;
unsigned int miscMsgTimer;
int togglePinState;
int nDisplay_Backlight_Intensity=0;
int busyAddrByte0=0;
int busyAddrByte1=0;
//int xyz=0;

int    switchValueUpFlag;
int    switchValueDownFlag;
int    switchFunctUpFlag;
int    switchFunctDownFlag;
int    switchChanUpFlag;
int    switchChanDownFlag;
int    switchValueUpRepeatFlag;
int    switchValueDownRepeatFlag;
int    switchFunctUpRepeatFlag;
int    switchFunctDownRepeatFlag;
int    switchChanUpRepeatFlag;
int    switchChanDownRepeatFlag;
unsigned int    switchValueUpCounter;
unsigned int    switchValueDownCounter;
unsigned int    switchFunctUpCounter;
unsigned int    switchFunctDownCounter;
unsigned int    switchChanUpCounter;
unsigned int    switchChanDownCounter;
//int    repeatFlag=0;

char outputMsg[MAX_OUTPUT_MSG_SIZE];
char inputMsg[MAX_INPUT_MSG_SIZE];
char inputMsgParams[MAX_INPUT_MSG_SIZE];

char txBuffer[TX_BUFFER_SIZE];
int txBufferReadIndex=0;
int txBufferWriteIndex=0;
int txBufferSize=0;

char rxBuffer[RX_BUFFER_SIZE];
int rxBufReadIndex=0;
int rxBufWriteIndex=0;
int rxBufSize=0;

int msgSync=0;
int msgIndex=0;
int msgType=0;
int msgLength=0;
int rxBufOverrunCount=0;

unsigned int rssiA;
unsigned int rssiB;
int lockA;
int lockB;
int tempDigit;
int tempDigit2;
int desiredToneNoLockMode=0;
int reportedToneNoLockMode=99; // initialize to invalid value
int muteMode=0;
int bklightLevel=0;
unsigned int vuLeft;
unsigned int vuRight;
int transmittingFlag=0;
unsigned int16 busyCounter=0;
unsigned int rxVoltage=0;
char newMenuLine[21];

int scanFlag=0;
int channelChangeFlag=0;

int secretSwitchCodeIndex=0;
int displayPowerState;
int channelChangeMuteFlag=0;

int statusByte1,statusByte2;

int oneConfigReceivedFlag=0;
