#define FREQ_RANGE_362_391_OR_900_940MHz 0
#define FREQ_RANGE_361_388MHz            1

#define NUM_CHANNELS 16 // channel number ranges from 0 to 15: 0--7 for 360 MHz, 8--15 fro 900 MHz

//#define FREQ_RANGE FREQ_RANGE_362_391_OR_900_940MHz
#define FREQ_RANGE FREQ_RANGE_361_388MHz


//#define INITIAL_TIME_SW0_MS 20
//#define REPEAT_TIME_SW0_MS 500
//#define REPEAT_RATE_SW0_MS 250

// the following values are in 10s of miliseconds
#define INITIAL_TIME_SW0_MS 2 // 20 ms delay before switch is considered pressed
#define REPEAT_TIME_SW0_MS 50 // 500 ms to hold switch before it starts repeating
#define REPEAT_RATE_SW0_MS 25 // 250 ms between repeats (this value must be less than repeat time)

#define DISPLAY_UPDATE_TIME 100 // emergency update---every second
#define CHANNEL_CHANGE_TIMEOUT 100 // timeout after channel change before resending freqOp command---one second

#define DEBUG_DISPLAY_MSG_STATUS_BYTES 0
#define DEBUG_DISABLE_FILTTYPES_FOR_MORE_RAM 0
#define DEBUG_PIN_E0_TIMER_TOGGLE 0
