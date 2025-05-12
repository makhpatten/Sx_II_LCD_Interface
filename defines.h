//------------
// defines
//------------
#define CLOCK_FREQ_HZ 8000000
//#define TIMER1_INITIAL_VALUE       0xF830    // For 1000 Hz: 65536-((TIMER1_OVERFLOW/1000)/(4*(1/CLOCK_FREQ_HZ)))
#define TIMER1_INITIAL_VALUE       0xB1E0    // For 100 Hz: 65536-((1/100)/(4*(1/8000000))) Assume TIMER1_OVERFLOW==1
#define NUMBER_FILTERS 8
#define NUMBER_CHANNELS 8
#define TESTING_INCREMENT_MSECS (unsigned int16)500

#use delay(clock=CLOCK_FREQ_HZ)
#use rs232(baud=9600,parity=N,xmit=PIN_C6,rcv=PIN_C7,bits=8)

// settings for 100 Hz interrupt
#define STATUS_MESSAGE_REPEAT_TIME 21 // 210 ms
#define CONFIG_MESSAGE_REPEAT_TIME 53 // 530 ms
#define MISC_INST_MESSAGE_REPEAT_TIME 107 // 1007 ms (make these numbers slightly odd to each other for more randomization of messages)

// Former settings for 1kHz interrupt
//#define STATUS_MESSAGE_REPEAT_TIME 200
//#define CONFIG_MESSAGE_REPEAT_TIME 500
//#define MISC_INST_MESSAGE_REPEAT_TIME 1000

#define TX_BUFFER_SIZE 80
#define RX_BUFFER_SIZE 90

#define MAX_INPUT_MSG_SIZE 20
#define MAX_OUTPUT_MSG_SIZE 20

#define MAX_RSSI_CHARS 6
#define MAX_VU_CHARS 6
#define ANTENNA_CHARACTER 149
#define UP_ARROW_CHARACTER 16
#define DOT_CHARACTER 0xBB
#define DOWN_ARROW_CHARACTER 17
#define LOCK_CHARACTER DOT_CHARACTER
