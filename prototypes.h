//---------------------
// function prototypes
//---------------------
void updateDisplay();
void scanSwitches();
void lcd_command(char oneByte);
void lcd_data(char oneByte);
void lcd_data_read(char *oneByte);
void lcd_busyflag_addrcount_read(char *oneByte);
void setup4bitData(char xxx);
void read4bitData(char *xxx2);
void display_init_42003(void);    //4bit
void all_A_42003(void);
void Texttest_auf_42003(void);
//void incrementAllParmsForTesting();
void updateTimers();
void moveCursorOneRight();
void moveCursorRight(int r);
void updateScreenText();
//void moveCursorToCurrentLocation();
void setDisplayAddress(int x);
void writeStringToDisplay(char *c,int l);
void checkSwitchTimers(int s,unsigned int *a, int *b, int *c);
//void checkSwitchTimers(int *a,int *b,unsigned int16 *c, unsigned int16 d,unsigned int16 e,unsigned int16 f);
void  processSwitches();
void readInputMsg();
void writeOutputMsgs();
void writeRequestStatusCmd(); // request status
void writeRequestConfigCmd(); // request status
void writeRequestMiscCmd(); // request status
void writeMsg(int length);
void pushByteToTxBuffer(byte b);
unsigned int16 Use_Crc(unsigned char *Buffer, int BuffLength);
BOOLEAN Check_CRC(unsigned char *Buffer, int BuffLength);
unsigned int16 Use_Crc(unsigned char *Buffer, int BuffLength);
void Crc_Update(long data_ptr, unsigned int16 *accum);
char popCharFromInBuff();
void resyncMsg();
void determineMsgType();
void processStatusReq();
void processConfigReqParams();
void processMiscInstParams();
void processMsg();
void findChannelNumber();
void computeRSSILevels();
void drawBargraph(int startLoc,int numSegments,int value);
void return_home(void);
void writeFreqOperCmd();
void waitForDisplayNotBusy();
void setBacklightLevel();
void scrollMenuLine();
void updateMenuLine();
void strcpy99(char *a,char  *b);
void toggleMonoStereo();
void setDisplayPowerState();
void decrementChannel();
void incrementChannel();
void checkChannelChange();
void stopScanning();
void checkSecretKeyPowerToggle();
