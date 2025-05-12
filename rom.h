//-------------------------------------------------------------------------------------------------------
// FREQUENCY DATA STORED IN EEPROM  (stored in kHz

#if FREQ_RANGE==FREQ_RANGE_362_391_OR_900_940MHz     //if Receiver Freq Band = 362-391 MHz
#ROM int8 0XF00000    = {0x05, 0x88, 0x00,  // 362.496 MHz //
                          0x05, 0x98, 0x00,  // 366.952 MHz //
                          0x05, 0xA8, 0x00,  // 370.688 MHz //
                          0x05, 0xB8, 0x00,  // 374.784 MHz //
                          0x05, 0xC8, 0x00,  // 378.880 MHz //
                          0x05, 0xD8, 0x00,  // 382.976 MHz //
                          0x05, 0xE8, 0x00,  // 387.072 MHz //
                          0x05, 0xF8, 0x00,  // 391.168 MHz //
                          0x0D, 0xB8, 0x00,  // 899.072 MHz */      // w/out int8, the #rom addresses as Words, NOT Bytes
                          0x0D, 0xC8, 0x00,  // 903.168 MHz
                          0x0D, 0xD8, 0x00,  // 907.264 MHz
                          0x0D, 0xE8, 0x00,  // 911.360 MHz
                          0x0D, 0xF8, 0x00,  // 915.456 MHz
                          0x0E, 0x08, 0x00,  // 919.552 MHz
                          0x0E, 0x18, 0x00,  // 923.648 MHz
                          0x0E, 0x28, 0x00}   // 927.744 MHz
#endif
#if FREQ_RANGE==FREQ_RANGE_361_388MHz
   #ROM int8 0XF00000    = {
                     0x05, 0x80, 0x34,   /* 360.500 MHz */
                     0x05, 0x8B, 0xEC,   /* 363.500 MHz */
                     0x05, 0x97, 0xA4,   /* 366.500 MHz */
                     0x05, 0xA3, 0xC5,   /* 369.500 MHz */
                     0x05, 0xAF, 0x14,   /* 372.500 MHz */
                     0x05, 0xBA, 0xCC,   /* 375.500 MHz */
                     0x05, 0xC6, 0x84,   /* 378.500 MHz */
                     0x05, 0xE9, 0xAC,   /* 387.500 MHz */
                     0x05, 0x80, 0x34,   /* 360.500 MHz */
                     0x05, 0x8B, 0xEC,   /* 363.500 MHz */
                     0x05, 0x97, 0xA4,   /* 366.500 MHz */
                     0x05, 0xA3, 0xC5,   /* 369.500 MHz */
                     0x05, 0xAF, 0x14,   /* 372.500 MHz */
                     0x05, 0xBA, 0xCC,   /* 375.500 MHz */
                     0x05, 0xC6, 0x84,   /* 378.500 MHz */
                     0x05, 0xE9, 0xAC}   /* 387.500 MHz */
#endif


#define EEPROM_ADDR_BKLIGHT_LEVEL NUM_CHANNELS*3
#define EEPROM_ADDR_DISP_PWR_STATE EEPROM_ADDR_BKLIGHT_LEVEL+1

#ROM int8 0XF00000+EEPROM_ADDR_BKLIGHT_LEVEL = {0x03} // default high backlight level
#ROM int8 0XF00000+EEPROM_ADDR_DISP_PWR_STATE = {0x01} // default LCD power state is on
