// Commands for CT-148 communication

#define MAX_MSG_LENGTH        30

#define CMD_UNKNOWN					0
#define CMD_SET_FREQ_OPER			1
#define CMD_STATUS_REQ				5
#define CMD_SWEEP					6
#define CMD_CONFIG_SET				7
#define CMD_CONFIG_REQ				8
#define CMD_MISC_INST				9
#define CMD_CARD_STATUS_REQ			10
#define CMD_RECORD_STATUS_REQ		11
#define CMD_RECORD_SET				12
#define CMD_TIME_READ				13
#define CMD_DATE_READ				14
#define CMD_TIME_SET				15
#define CMD_DATE_SET				16
#define CMD_WRITE_REMOTECTL_TX           17
#define CMD_WRITE_REMOTECTL_TX_SCHED     18
#define CMD_NEXT_FILE_NAME_SET      19
#define CMD_NEXT_FILE_NAME_REQ      20
#define CMD_TX_FREQ_SET				29
#define CMD_TX_FREQ_REQ				30
#define CMD_SIG_PROC_SET			31
#define CMD_SIG_PROC_REQ			32
#define CMD_TX_STATUS_SET			33
#define CMD_TX_STATUS_REQ			44
#define CMD_FPGA_REG_SET       		55
#define CMD_FPGA_REG_REQ			66
#define CMD_EEPROM_PIC1_SET    		67
#define CMD_EEPROM_PIC1_REQ			68
#define CMD_DEFAULT_STATE_SET		83

/*
#define CMD_SET_DEV            14
#define CMD_READ_DEV           15
#define CMD_SET_TX_FREQ    16
#define CMD_SET_DELTA_PHASE    18
#define CMD_READ_DELTA_PHASE   19
#define CMD_SET_CLKS_PER_FS    20
#define CMD_READ_CLKS_PER_FS   21
#define CMD_READ_BER           22
#define CMD_SET_OSC_CTRL       23
#define CMD_READ_OSC_CTRL      24
#define CMD_RESTORE_OSC_CTRL   25
#define CMD_SET_BAND_SW            26
#define CMD_READ_BAND_SW            27
  #define CMD_SET_SQUELCH        28
#define CMD_READ_SQUELCH            29
#define CMD_READ_LOCAL_AGC          30
#define CMD_WRITE_LOCAL_AGC         31
#define CMD_READ_REMOTE_AGC         32
#define CMD_WRITE_REMOTE_AGC        33
#define CMD_REMOTECTL_TX_RECORD          36
#define CMD_DOGLEASH_MODE           37
#define CMD_TIME_DATE_SET           38
#define CMD_TIME_DATE_READ          39
#define CMD_SDRAM_AUDIO_READ        40
#define CMD_BYTES_PER_CLUSTER_READ  43
#define CMD_CHANNEL_SCAN            44
#define CMD_ENCRYPT_SET				45
*/

// Status Request: RS command
#define CMD_STATUS_REQ_1 'r'
#define CMD_STATUS_REQ_2 's'
#define CMD_STATUS_REQ_LEN 4
// Set Freq/Operation: CS command
#define CMD_SET_FREQ_OPER_1 'c'
#define CMD_SET_FREQ_OPER_2 's'
#define CMD_SET_FREQ_OPER_LEN 9
// Status Request: ST response
#define RESP_STATUS_REQ_1 's'
#define RESP_STATUS_REQ_2 't'
#define RESP_STATUS_REQ_LEN 14


// Configuration Request: CD command
#define CMD_CONFIG_REQ_1 'c'
#define CMD_CONFIG_REQ_2 'd'
#define CMD_CONFIG_REQ_LEN 4
// Configuration response: SD response
#define RESP_CONFIG_REQ_1 's'
#define RESP_CONFIG_REQ_2 'd'
#define RESP_CONFIG_REQ_LEN 19

// Sweep Request: CD command
#define CMD_SWEEP_REQ_1 'c'
#define CMD_SWEEP_REQ_2 'w'
#define CMD_SWEEP_REQ_LEN 13
// Configuration response: SD response
#define RESP_SWEEP_RESP_1 's'
#define RESP_SWEEP_RESP_2 'w'
#define RESP_SWEEP_LEN 9

// REMOTECTL_TX command
#define CMD_REMOTECTL_TX_1 'r'
#define CMD_REMOTECTL_TX_2 'x'
#define CMD_WRITE_REMOTECTL_TX_LEN 12 // 8 bytes + 2 for message ID+ 2 for CRC
// Write 8 byte REMOTECTL_TX schedule command
#define CMD_REMOTECTL_TX_SCHEDULE_1 'r'
#define CMD_REMOTECTL_TX_SCHEDULE_2 'z'
#define CMD_WRITE_REMOTECTL_TX_SCHEDULE_LEN 12 // 8 bytes + 2 for message ID+ 2 for CRC

// Card Status Request: CG command
#define CMD_CARD_STATUS_REQ_1 'c'
#define CMD_CARD_STATUS_REQ_2 'g'
#define CMD_CARD_STATUS_REQ_LEN 4
// Card Status response: SG response
#define RESP_CARD_STATUS_REQ_1 's'
#define RESP_CARD_STATUS_REQ_2 'g'
#define RESP_CARD_STATUS_LEN 20

// Record Status Request: CP command
#define CMD_RECORD_STATUS_REQ_1 'c'
#define CMD_RECORD_STATUS_REQ_2 'p'
#define CMD_RECORD_STATUS_REQ_LEN 4
// Record Set: CQ command
#define CMD_RECORD_SET_1 'c'
#define CMD_RECORD_SET_2 'q'
#define CMD_RECORD_SET_LEN 5
// Record Status response: SP response
#define RESP_RECORD_STATUS_REQ_1 's'
#define RESP_RECORD_STATUS_REQ_2 'p'
#define RESP_RECORD_STATUS_LEN 5

// File Name Request: CH command
#define CMD_NEXT_FILE_NAME_REQ_1 'c'
#define CMD_NEXT_FILE_NAME_REQ_2 'h'
#define CMD_NEXT_FILE_NAME_REQ_LEN 4
// File Name Set: CJ command
#define CMD_NEXT_FILE_NAME_SET_1 'c'
#define CMD_NEXT_FILE_NAME_SET_2 'j'
#define CMD_NEXT_FILE_NAME_SET_LEN 12
// Next File Name response: SH response
#define RESP_NEXT_FILE_NAME_REQ_1 's'
#define RESP_NEXT_FILE_NAME_REQ_2 'h'
#define RESP_NEXT_FILE_NAME_LEN 12

// Misc Info Request: CT command
#define CMD_MISC_INFO_1 'c'
#define CMD_MISC_INFO_2 't'
#define CMD_MISC_INFO_LEN 12
// Misc Info response: SV response
#define RESP_MISC_INFO_1 's'
#define RESP_MISC_INFO_2 'v'
#define RESP_MISC_INFO_LEN 12

// Time Request: CK command
#define CMD_TIME_REQ_1 'c'
#define CMD_TIME_REQ_2 'k'
#define CMD_TIME_REQ_LEN 4
// Time Set: CL command
#define CMD_TIME_SET_1 'c'
#define CMD_TIME_SET_2 'l'
#define CMD_TIME_SET_LEN 7
// Time response: SK response
#define RESP_TIME_1 's'
#define RESP_TIME_2 'k'
#define RESP_TIME_LEN 7

// Date Request: CM command
#define CMD_DATE_REQ_1 'c'
#define CMD_DATE_REQ_2 'm'
#define CMD_DATE_REQ_LEN 4
// Date Set: CN command
#define CMD_DATE_SET_1 'c'
#define CMD_DATE_SET_2 'n'
#define CMD_DATE_SET_LEN 7
// Date response: SM response
#define RESP_DATE_1 's'
#define RESP_DATE_2 'm'
#define RESP_DATE_LEN 7

// Transmitter frequency request: AA command
#define CMD_TX_FREQ_REQ_1 'a'
#define CMD_TX_FREQ_REQ_2 'a'
#define CMD_TX_FREQ_REQ_LEN 4
// Transmitter frequency set: AB command
#define CMD_TX_FREQ_SET_1 'a'
#define CMD_TX_FREQ_SET_2 'b'
#define CMD_TX_FREQ_SET_LEN 7
// Transmitter frequency response: BA response
#define RESP_TX_FREQ_1 'b'
#define RESP_TX_FREQ_2 'a'
#define RESP_TX_FREQ_LEN 7

// Signal processing settings request: AC command
#define CMD_SIG_PROC_REQ_1 'a'
#define CMD_SIG_PROC_REQ_2 'c'
#define CMD_SIG_PROC_REQ_LEN 4
// Signal processing settings set: AD command
#define CMD_SIG_PROC_SET_1 'a'
#define CMD_SIG_PROC_SET_2 'd'
#define CMD_SIG_PROC_SET_LEN 5
// Signal processing settings response: BC response
#define RESP_SIG_PROC_1 'b'
#define RESP_SIG_PROC_2 'd'
#define RESP_SIG_PROC_LEN 5

// Transmitter settings request: AE command
#define CMD_TX_STATUS_REQ_1 'a'
#define CMD_TX_STATUS_REQ_2 'e'
#define CMD_TX_STATUS_REQ_LEN 4
// Transmitter settings set: AF command
#define CMD_TX_STATUS_SET_1 'a'
#define CMD_TX_STATUS_SET_2 'f'
#define CMD_TX_STATUS_SET_LEN 5
// Transmitter settings response: BE response
#define RESP_TX_STATUS_1 'b'
#define RESP_TX_STATUS_2 'e'
#define RESP_TX_STATUS_LEN 5

// FPGA register request: CB command
#define CMD_FPGA_REG_REQ_1 'c'
#define CMD_FPGA_REG_REQ_2 'b'
#define CMD_FPGA_REG_REQ_LEN 5
// FPGA register set: CC command
#define CMD_FPGA_REG_SET_1 'c'
#define CMD_FPGA_REG_SET_2 'c'
#define CMD_FPGA_REG_SET_LEN 6
// FPGA register response: SB response
#define RESP_FPGA_REG_1 's'
#define RESP_FPGA_REG_2 'b'
#define RESP_FPGA_REG_LEN 6

// EEPROM (Pic 1) register request: RB command
#define CMD_EEPROM_PIC1_REQ_1 'r'
#define CMD_EEPROM_PIC1_REQ_2 'b'
#define CMD_EEPROM_PIC1_REQ_LEN 5
// EEPROM (Pic 1) register set: RC command
#define CMD_EEPROM_PIC1_SET_1 'r'
#define CMD_EEPROM_PIC1_SET_2 'c'
#define CMD_EEPROM_PIC1_SET_LEN 6
// EEPROM (Pic 1) register response: TB response
#define RESP_EEPROM_PIC1_1 't'
#define RESP_EEPROM_PIC1_2 'b'
#define RESP_EEPROM_PIC1_LEN 6

// Return to default state: CZ command
#define CMD_DEFAULT_STATE_SET_1 'c'
#define CMD_DEFAULT_STATE_SET_2 'z'
#define CMD_DEFAULT_STATE_SET_LEN 4
// Return to default state response: SZ response
#define RESP_DEFAULT_STATE_SET_1 's'
#define RESP_DEFAULT_STATE_SET_2 'z'
#define RESP_DEFAULT_STATE_SET_LEN 4


// Set Frequency: CS command
//static char setFreqCmdStr[2]={'c','s'};
//#define CMD_SET_FREQ_LEN 5
// Read Frequency: DS command
//static char readFreqCmdStr[2]={'d','s'};
//#define CMD_READ_FREQ_LEN 2
// Both above commands gove the following response:
// Freq response: SS command
//static char freqRespStr[2]={'s','s'};
//#define RESP_FREQ_LEN 5




// Set Filter Parameter: ES command
//static char setFilterCmdStr[2]={'e','s'};
//#define CMD_SET_FILTER_LEN 4
// Read Filter Parameter: FS command
//static char readFilterCmdStr[2]={'f','s'};
//#define CMD_READ_FILTER_LEN 2
// Both above commands gove the following response:
// Filter response: TS command
//static char filterRespStr[2]={'t','s'};
//#define RESP_FILTER_LEN 4

// Channel Scan (returns RF level, checks Mono&Stero for lock): RY response
/*
static char channelScanCmdStr[2]={'r','y'};
#define CMD_CHANNEL_SCAN_LEN 2
static char channelScanRespStr[2]={'s','y'};
#define RESP_CHANNEL_SCAN_LEN 6
*/

/*
// Sweep: CW command
static char sweepCmdStr[2]={'c','w'};
#define CMD_SWEEP_LEN 11
// Sweep response: SW response
static char sweepRespStr[2]={'s','w'};
#define RESP_SWEEP_LEN 11

// Configuration Set: CI command
static char configSetCmdStr[2]={'c','i'};
#define CMD_CONFIG_SET_LEN 11
// Configuration Set: SI response
static char configSetRespStr[2]={'s','i'};
#define RESP_CONFIG_SET_LEN 2

// Misc. Instructions: CT command
#define CMD_MISC_INST_LEN 10
static char miscInstCmdStr[2]={'c','t'};
static char miscInstRespStr[2]={'s','v'}; // "SV" as opposed to status cmd "ST" 
#define RESP_MISC_INST_LEN 10

// Set Signal Processing Mode: CA command
#define CMD_SIG_PROC_LEN 5
#define RESP_SIG_PROC_LEN 5
static char sigProcCmdStr[2]={'c','a'};
static char sigProcRespStr[2]={'s','a'};


// Set Tx Freq: CB command
//#define CMD_CB 8
//#define CMD_SET_TX_FREQ_LEN 5
//#define RESP_SET_TX_FREQ_LEN 5
//static char setTxFreqCmdStr[2]={'c','b'};
//static char setTxFreqRespStr[2]={'s','b'};

// Set FPGA Reg: CC command
//#define CMD_CC 9
#define CMD_SET_FPGA_REG_LEN 4
#define RESP_SET_FPGA_REG_LEN 3
static char setFPGARegCmdStr[2]={'c','c'};
static char setFPGARespStr[2]={'s','c'};
// Read FPGA Reg: CE command
//#define CMD_CE 10
#define CMD_READ_FPGA_REG_LEN 3
#define RESP_READ_FPGA_REG_LEN 3

static char readFPGACmdStr[2]={'c','e'};
static char readFPGARespStr[2]={'s','e'};


// Set Deviation: CF command
//#define CMD_CF 11
#define CMD_SET_DEV_LEN 4
#define RESP_SET_DEV_LEN 2
static char setDevCmdStr[2]={'c','f'};
static char setDevRespStr[2]={'s','f'};

// Read Defiation: CG command
//#define CMD_CG 12
#define CMD_READ_DEV_LEN 2
#define RESP_READ_DEV_LEN 4
static char readDevCmdStr[2]={'c','g'};
static char readDevRespStr[2]={'s','g'};

// Set Tx Freq: CH command
//#define CMD_CH 13
#define CMD_SET_TX_FREQ_LEN 5
#define RESP_SET_TX_FREQ_LEN 2
static char setTxFreqCmdStr[2]={'c','h'};

// Set Tx Freq response: SH command
static char setTxFreqRespStr[2]={'s','h'};

// Read Tx Freq: CJ command
//#define CMD_CJ 14
static char readTxFreqCmdStr[2]={'c','j'};
#define CMD_READ_TX_FREQ_LEN 2

// Read Tx Freq response: SJ command
static char readTxFreqRespStr[2]={'s','j'};
#define RESP_READ_TX_FREQ_LEN 5

// Set Delta Phase: CK command
static char setDeltaPhaseCmdStr[2]={'c','k'};
#define CMD_SET_DELTA_PHASE_LEN 5

// Set Delta Phase response: SK command
static char setDeltaPhaseRespStr[2]={'s','k'};
#define RESP_SET_DELTA_PHASE_LEN 2

// Read Delta Phase: CL command
#define CMD_READ_DELTA_PHASE_LEN 2
#define RESP_READ_DELTA_PHASE_LEN 5
static char readDeltaPhaseCmdStr[2]={'c','l'};
static char readDeltaPhaseRespStr[2]={'s','l'};

// Set Clocks Per Fs: CM command
#define CMD_SET_CLKS_PER_FS_LEN 4
#define RESP_SET_CLKS_PER_FS_LEN 2
static char setClksPerFsCmdStr[2]={'c','m'};
static char setClksPerFsRespStr[2]={'s','m'};

// Read Clocks Per Fs: CN command
//#define CMD_CN 18
#define CMD_READ_CLKS_PER_FS_LEN 2
static char readClksPerFsCmdStr[2]={'c','n'};

#define RESP_READ_CLKS_PER_FS_LEN 4
static char readClksPerFsRespStr[2]={'s','n'};

// Read Bit Error Rate values: CO command
#define CMD_READ_BER_LEN 2
static char readBERCmdStr[2]={'c','o'};

// Read Bit Error Rate response: SO command
static char readBERRespStr[2]={'s','o'};
#define RESP_READ_BER_LEN 5


// Set oscillator control command: CP command
static char setOscCtrlCmdStr[2]={'c','p'};
#define CMD_SET_OSC_CTRL_LEN 20

// Set oscillator control response: SP command 
static char setOscCtrlRespStr[2]={'s','p'};
#define RESP_SET_OSC_CTRL_LEN 2

// Read oscillator control command: CQ command
static char readOscCtrlCmdStr[2]={'c','q'};
#define CMD_READ_OSC_CTRL_LEN 2

// Read oscillator control response: SQ command 
static char readOscCtrlRespStr[2]={'s','q'};
#define RESP_READ_OSC_CTRL_LEN 20

static char restoreOscCtrlCmdStr[2]={'c','r'};
#define CMD_RESTORE_OSC_CTRL_LEN 2
//static char restoreOscCtrlRespStr[2]={'s','r'};
//#define RESP_RESTORE_OSC_CTRL_LEN 20


static char setBandSWCmdStr[2]={'c','v'};
#define CMD_SET_BAND_SW_LEN 3
static char readBandSWCmdStr[2]={'c','z'};
#define CMD_READ_BAND_SW_LEN 2
static char bandSWRespStr[2]={'s','v'};
#define RESP_BAND_SW_LEN 3

// Set squelch
static char setSquelchCmdStr[2]={'c','x'};
#define CMD_SET_SQUELCH_LEN 6
// Read squelch
static char readSquelchCmdStr[2]={'c','y'};
#define CMD_READ_SQUELCH_LEN 2
// Both commands respond with:
static char squelchRespStr[2]={'s','x'};
#define RESP_SQUELCH_LEN 6

// Read Local AGC: DA command
static char readLocalAGCCmdStr[2]={'d','a'};
#define CMD_READ_LOCAL_AGC_LEN 2
// Write Local AGC: DB command
static char writeLocalAGCCmdStr[2]={'d','b'};
#define CMD_WRITE_LOCAL_AGC_LEN 10
// Both above commands gove the following response:
// Local AGC response: TA command
static char localAGCRespStr[2]={'t','a'};
#define RESP_LOCAL_AGC_LEN 10

// Read Remote AGC: DC command
static char readRemoteAGCCmdStr[2]={'d','c'};
#define CMD_READ_REMOTE_AGC_LEN 2
// Write Remote AGC: DD command
static char writeRemoteAGCCmdStr[2]={'d','d'};
#define CMD_WRITE_REMOTE_AGC_LEN 10
// Both above commands gove the following response:
// Remote AGC response: TA command
static char remoteAGCRespStr[2]={'t','c'};
#define RESP_REMOTE_AGC_LEN 10

// Write 8 byte REMOTECTL_TX command
//static char writeREMOTECTL_TXCmdStr[2]={'d','e'};
//#define CMD_WRITE_REMOTECTL_TX_LEN 10 // 8 bytes + 2 for message ID
// Write 8 byte REMOTECTL_TX response: TE command
//static char writeREMOTECTL_TXRespStr[2]={'t','e'};
//#define RESP_WRITE_REMOTECTL_TX_LEN 3

// Write 16 byte REMOTECTL_TX command with schedule
static char writeREMOTECTL_TXSchedCmdStr[2]={'d','f'};
#define CMD_WRITE_REMOTECTL_TX_SCHED_LEN 19 // 16 bytes + 2 for message ID
// Write 8 byte REMOTECTL_TX response: TE command
static char writeREMOTECTL_TXSchedRespStr[2]={'t','f'};
#define RESP_WRITE_REMOTECTL_TX_SCHED_LEN 3

// Set record REMOTECTL_TX command mode
static char REMOTECTL_TXRecordCmdStr[2]={'d','g'};
#define CMD_REMOTECTL_TX_RECORD_LEN 3
// Set record REMOTECTL_TX command mode response
static char REMOTECTL_TXRecordRespStr[2]={'t','g'};
#define RESP_REMOTECTL_TX_RECORD_LEN 20 // returns: 2 bytes for 'tg',
// 1 byte for record on/off, 1 byte for type (0:blank, 1:normal, 2:schedule),
// and 16 bytes for REMOTECTL_TX command

// Set REMOTECTL_TX dogleash command mode
static char dogleashModeCmdStr[2]={'d','h'};
#define CMD_DOGLEASH_MODE_LEN 3
// Set record REMOTECTL_TX command mode response
static char dogleashModeRespStr[2]={'t','h'};
#define RESP_DOGLEASH_MODE_LEN 23 // returns: 2 bytes for 'th',
// 1 byte for dogleash on/off, 1 byte spare, 16 bytes for REMOTECTL_TX command,
// and 3 bytes for seconds remaining until next dogleash command

// Set time and date command
static char timeDateSetCmdStr[2]={'d','i'};
#define CMD_TIME_DATE_SET_LEN 8
// Read time and date command
static char timeDateReadCmdStr[2]={'d','j'};
#define CMD_TIME_DATE_READ_LEN 2
// Both time and date commands have the following response
static char timeDateRespStr[2]={'t','i'};
#define RESP_TIME_DATE_LEN 8 // returns: 2 bytes for 'ti',
// 1 byte each for second, minute, hour, day, month, and year

// Read SD RAM Audio Data Available
static char readSDRAMAudioCmdStr[2]={'d','k'};
#define CMD_READ_SDRAM_AUDIO_LEN 2
// has the following response
static char readSDRAMAudioRespStr[2]={'t','k'};
#define RESP_READ_SDRAM_AUDIO_LEN 6 // returns: 2 bytes for 'tk',
// 4 bytes for unsigned data value

// Set Next SD File Name: DL command
static char setFileNameCmdStr[2]={'d','l'};
#define CMD_SET_FILE_NAME_LEN 10
// Read Next SD File Name: DM command
static char readFileNameCmdStr[2]={'d','m'};
#define CMD_READ_FILE_NAME_LEN 2
// Both above commands gove the following response:
// Read Next SD Filename response: TL command
static char readFileNameRespStr[2]={'t','l'};
#define RESP_READ_FILE_NAME_LEN 10

// Read Bytes per SD Cluster: DN command
static char readBytesPerClusterCmdStr[2]={'d','n'};
#define CMD_READ_BYTES_PER_CLUSTER_LEN 2
// Read Bytes per SD Cluster response: TN command
static char readBytesPerClusterRespStr[2]={'t','n'};
#define RESP_READ_BYTES_PER_CLUSTER_LEN 3

// Set SD Encryption key
static char setSDEncryptionStr[2]={'d','p'};
#define CMD_SET_ENCRYPT_REG_LEN 18
// Response to Set SD Key
static char respSDEncryptionStr[2]={'t','p'};
#define RESP_SET_ENCRYPT_REG_LEN 3
*/

// These are in Byte 0 of the operation latch stored in EEPROM
#define OPERLATCH0_PREEMPH_MASK 1
#define OPERLATCH0_AGC_LOCAL_MASK 2
#define OPERLATCH0_AGC_REMOTE_MASK 4
#define OPERLATCH0_ANC_REMOTE_MASK 8
#define OPERLATCH0_SWAPLR_MASK 16
#define OPERLATCH0_SQUELCH_MASK 32
#define OPERLATCH0_DECLICK_MASK 64
#define OPERLATCH0_MONO_ON_MASK 128

// These are in Byte 1 of the operation latch stored in EEPROM
#define OPERLATCH1_CALTONE_ON_MASK 1
#define OPERLATCH1_CALTONE_NOLOCK_MASK 2
#define OPERLATCH1_HEADPH_MUTE_MASK 4
#define OPERLATCH1_ANALOG_MUTE_MASK 8
#define OPERLATCH1_TX_ON_MASK 16
#define OPERLATCH1_RECORD_ON_MASK 128

#define SIGPROC_BAND_SW0_MASK 1
#define SIGPROC_BAND_SW1_MASK 2

#define REMOTECTL_TX_IDLE 0
#define REMOTECTL_TX_TXMITTING 1
#define REMOTECTL_TX_COLLISION 2
#define REMOTECTL_TX_COLLIDED_TIMED_OUT 3

// These are in Byte 2 of the operation latch stored in EEPROM
#define OPERLATCH2_TXMODE_FM 0
#define OPERLATCH2_TXMODE_FMENC 1
#define OPERLATCH2_TXMODE_DST 2

// these are the 'cs' command/'st' response definitions
#define CMDBYTE1_STEREO_ON_MASK			0x40
#define CMDBYTE1_EXT_RANGE_MASK			0x20
#define CMDBYTE1_CALTONE_MASK			0x10
#define CMDBYTE1_REMOTECTL_TX_TX_MASK		0x08

#define CMDBYTE2_DECLICK_MASK			0x20
#define CMDBYTE2_HEADPHONE_MUTE_MASK	0x04
#define CMDBYTE2_TONE_NO_LOCK_MASK		0x02
#define CMDBYTE2_ANALOPG_MUTE_MASK		0x01

#define SIGPROC_PREEMPH_MASK			0x10
#define SIGPROC_AGC_LOCAL_MASK			0x08
#define SIGPROC_AGC_REMOTE_MASK			0x04
#define SIGPROC_ANC_REMOTE_MASK			0x02
#define SIGPROC_SWAPLR_MASK				0x01
