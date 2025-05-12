/*================================================================================================================================
Sx II LCD Interface Controller Program
Firmware for Microchip PIC18LF4320
Circuit Card: 1334 Device: U1

Author: Mark Patten

Date: 10-21-11

Revision History:

Date     Version  Notes
---------------------------------------------------------------------------------------------------------------------------------
10-21-11 v1.00d Version with Pvt7 frequencies
07-13-11 v1.00c Fixed problem when COM connected and power cycled, also changed filter names
07-12-11 v1.00b Version for 900 MHz (eventually I'll make a version that automatically detects freq range from config response)
07-07-11 v1.00a Improved key combo for display on/off, added display off when analog and headphone mute selected remotely
07-05-11 v0.11f Added RS232 detect prevents any RS, CT, or CG messages
07-05-11 v0.11e Fixed keys for actual overlay; added mute on scan
07-01-11 v0.11d Added scan down as well as scan up, fixed tying pins 22 and 23 together (instead of 23 & 24)
06-30-11 v0.11c Changing key scan function and reducing interrupt time for better button responses
06-28-11 v0.11b Added mono/stereo search feature and shutoff display feature
06-24-11 v0.11a Finally got a good 6 button version---fixed that message problem
06-21-11 v0.10b Continuing making version for 6 button
06-21-11 v0.10a Started making version for 6 button, got 3 buttons working, stripped button timers down to 1 to save space
06-17-11 v0.07e 
06-16-11 v0.07d 
06-18-11 v0.07c Everything sorta works in this version 
05-18-11 v0.07b Working on using screen commands like write to address and read status
05-16-11 v0.07a Works pretty well
05-13-11 v0.06a Reads frequency and status correctly
05-09-11 v0.05a
05-06-11 v0.04a Continuing with new display
04-27-11 v0.03a Working on detecting buttons and turning on LCD backlight
04-25-11 v0.02a Making it look like it might actually be
04-13-11 v0.01a First attempt at program---draws shifting characters

=================================================================================================================================
*/

//------------
// includes
//------------
#include <18F4320.h>
#include <STDLIB.H>

#include "fuses.h"
#include "about.h"
#include "config.h"
#include "defines.h"
#include "rom.h"
#include "pin_config.h"
#include "prototypes.h"
#include "globals.h"
#include "msg_defs.h"

#include "lcd_display.c"
#include "rs232.c"
#include "msgs.c"
#include "screenText.c"

//#device ADC=8
//#device HIGH_INTS=TRUE


//======================================================================================================================
void main(void) {

   int returnVal;
   int ii;
   setup_oscillator(OSC_8MHZ);
   delay_ms(10); // delay for a few milisecs
   setup_timer_1(T1_INTERNAL|T1_DIV_BY_1);   // Set up 16-bit timer; interrupts every 1ms (see also timer1_isr())
   set_timer1(TIMER1_INITIAL_VALUE); //implemented as a 1ms clock
   setup_timer_2(T2_DIV_BY_1,49,1); //for PWM control; cycle time = (1/clock)*4*t2div*(period+1) = 25us =40kHz (for clock/1, period = 50)
   setup_CCP1(CCP_PWM); 
   bklightLevel=read_eeprom(EEPROM_ADDR_BKLIGHT_LEVEL);
   setBacklightLevel();
   displayPowerState=read_eeprom(EEPROM_ADDR_DISP_PWR_STATE);
   setDisplayPowerState();

   port_b_pullups(TRUE);
   clear_interrupt(INT_TIMER1);
   enable_interrupts(INT_TIMER1);
   clear_interrupt(INT_RDA);   // clear any existing RS232 receive interrupt flag
   enable_interrupts(INT_RDA);   //enable the RS232 receive interrupt
   enable_interrupts(GLOBAL);
   set_tris_a(0b11110111); // ports A3 is the only output---the output message enable---so a jumper from pin 23 (A4) to pin 22 (A3) is required
   output_low(WRITE_MSG_ENABLE); // set output message enable to default low so that external messages have the priority...


   display_init_42003();    //4bit
   updateDisplay();
   delay_ms(2000);
   cursorLocation=1;

// Loop forever
   while(TRUE) {
   
      updateTimers(); // update all timers
      scanSwitches(); // scan to see if any switches pressed
      processSwitches(); // process any switches pressed

      readInputMsg(); // read and process any input COM messages
      writeOutputMsgs(); // write any output messages if necessary

// can't decide if this timer based screen update is necessary...it should always update upon receiving 'st' commands
      if (displayUpdateTimer>DISPLAY_UPDATE_TIME) {
         displayUpdateTimer=0;
         updateDisplay();
      }

   }

}


//======================================================================================================================
void updateTimers() {
   disable_interrupts(INT_TIMER1);

   statusMsgTimer+=msCounter;
   configMsgTimer+=msCounter;
   miscMsgTimer+=msCounter;
   switchTimer+=msCounter;
   displayUpdateTimer+=msCounter;
   channelChangeTimeoutTimer+=msCounter;

   msCounter=0;

   enable_interrupts(INT_TIMER1);
}
//======================================================================================================================
void incrementChannel() {
   if ((channelNumber&0x07)==7) {
      channelNumber&=0x08;
   } else {
      channelNumber++;
   }
}
//======================================================================================================================
void decrementChannel() {
   if ((channelNumber&0x07)>0) channelNumber--;
   else channelNumber=(channelNumber&0x08)+7;
}
//======================================================================================================================
void  processSwitches() {
   if (displayPowerState==0) return; // don't process switches if powered down...

   if (switchChanUpFlag>0) {
      if (switchChanUpFlag>=2 && !input(RS232_DETECT)) { // if button held .5 sec and not scanning
         scanFlag=1; // 1 means scan up
      } else {
         stopScanning();
      }
      channelChangeFlag=1; // indicates channel just changed---this will be used for checking both mono and stereo settings
      incrementChannel();

      writeFreqOperCmd();
//      updateDisplay();
   }
   if (switchChanDownFlag>0) {
      if (switchChanDownFlag>=2 && !input(RS232_DETECT)) { // if button held .5 sec and not scanning
         scanFlag=2; // 2 means scan down
      } else {
         stopScanning();
      }
      channelChangeFlag=1; // indicates channel just changed---this will be used for checking both mono and stereo settings
      decrementChannel();


      writeFreqOperCmd();
//      updateDisplay();
   }
   if ((switchValueUpFlag>0 || switchValueDownFlag>0) && input(SWITCH_FUNCT_DOWN)) {  // if either up or down value pressed and not function down (function down is start of secret power key combination)
      stopScanning();
      switch (cursorLocation) {
//         case 0:
//            if (switchValueUpFlag>0) {
//               channelNumber++;
//               if (channelNumber>=NUMBER_CHANNELS) channelNumber=0;
//            } else {
//               if (channelNumber>0) channelNumber--;
//               else channelNumber=NUMBER_CHANNELS-1;
//            }
//            break;
         case 1:
            toggleMonoStereo();
//            if (monoMode==1) monoMode=0;
//            else monoMode=1;
//            writeFreqOperCmd();
            break;
         case 2:
            if (maxRange==1) maxRange=0;
            else maxRange=1;
            break;
         case 3:
            if (switchValueUpFlag>0) {
               filterNumber++;
               if (filterNumber>=NUMBER_FILTERS) filterNumber=0;
            } else {
               if (filterNumber>0) filterNumber--;
               else filterNumber=NUMBER_FILTERS-1;
            }
            break;
         case 4:
            if (desiredToneNoLockMode>0) desiredToneNoLockMode=0;
            else desiredToneNoLockMode=1;
            break;
         case 5:
            if (switchValueUpFlag>0) {
               bklightLevel++;
               if (bklightLevel>=4) bklightLevel=0;
            } else {
               if (bklightLevel>0) bklightLevel--;
               else bklightLevel=3;
            }
            write_eeprom(EEPROM_ADDR_BKLIGHT_LEVEL,bklightLevel);
            setBacklightLevel();
            updateDisplay();
            break;
      }
      if (cursorLocation<5) {
         writeFreqOperCmd();
      }
//      updateDisplay();
   }
   if (switchFunctUpFlag>0) {
      stopScanning();
      cursorLocation++;
      if (cursorLocation>5) cursorLocation=1;
      scrollMenuLine();

//      txt0[0]=' '; // is this necessary every time?
//      txt0[60]=ARROW_CHARACTER;
   }
   if (switchFunctDownFlag>0) {
      stopScanning();
      cursorLocation--;
      if (cursorLocation<1) cursorLocation=5;
      scrollMenuLine();
   }
}
//======================================================================================================================
void stopScanning() {
   if (scanFlag!=0) {
      scanFlag=0; // if scanning, stop
      if (channelChangeMuteFlag!=0) {
         channelChangeMuteFlag=0;
         writeFreqOperCmd(); // send to restore desired status of tone no lock
      }
   }
}
//======================================================================================================================
void scanSwitches() {

   checkSwitchTimers(input(SWITCH_VALUE_UP),&switchValueUpCounter,&switchValueUpFlag,&switchValueUpRepeatFlag);
   checkSwitchTimers(input(SWITCH_VALUE_DOWN),&switchValueDownCounter,&switchValueDownFlag,&switchValueDownRepeatFlag);
   checkSwitchTimers(input(SWITCH_FUNCT_UP),&switchFunctUpCounter,&switchFunctUpFlag,&switchFunctUpRepeatFlag);
   checkSwitchTimers(input(SWITCH_FUNCT_DOWN),&switchFunctDownCounter,&switchFunctDownFlag,&switchFunctDownRepeatFlag);
   checkSwitchTimers(input(SWITCH_CHAN_UP),&switchChanUpCounter,&switchChanUpFlag,&switchChanUpRepeatFlag);
   checkSwitchTimers(input(SWITCH_CHAN_DOWN),&switchChanDownCounter,&switchChanDownFlag,&switchChanDownRepeatFlag);
   switchTimer=0;

   checkSecretKeyPowerToggle();

}
//======================================================================================================================
void checkSecretKeyPowerToggle() {
   if (!input(SWITCH_FUNCT_DOWN) && !input(SWITCH_VALUE_UP)) { // if funct down is held and value up is pressed, then continue to check for secret combination (hold function down, then press value up, function up, and value down
      while (!input(SWITCH_VALUE_UP)) {} // wait for switch value up to be released
      secretSwitchCodeIndex=1; // first level of secret key combo reached---function down is held and value up is pressed
      while (secretSwitchCodeIndex>0) { // loop until invalid key state reached
         if (input(SWITCH_FUNCT_DOWN)) { // if function down not still pressed
            secretSwitchCodeIndex=0; // exit loop
//         } else if (!input(SWITCH_FUNCT_UP)) { // if function up key pressed...
//            if (secretSwitchCodeIndex==1) { // and at first level...
//               secretSwitchCodeIndex++; // advance to second level,
//               while (!input(SWITCH_FUNCT_UP)) {} // wait for function up switch to be released
//            } else secretSwitchCodeIndex=0; // if function up key pressed and not at first level, then exit loop
         } else if (!(input(SWITCH_VALUE_DOWN))) { // if value down key pressed...
            if (secretSwitchCodeIndex==1) { // and at first level...
               if (displayPowerState==0) { // we have successful key sequence, so toggle power state
                  displayPowerState=1;
               } else {
                  displayPowerState=0;
               }
               setDisplayPowerState(); // set the power state
               writeFreqOperCmd(); // activate or deactivate mute
               writeFreqOperCmd(); // important enough to do twice
               write_eeprom(EEPROM_ADDR_DISP_PWR_STATE,displayPowerState); // save it in the EEPROM
               while (!input(SWITCH_VALUE_DOWN)) {} // wait for switch value up to be released
               delay_ms(1000);
            }
         } else if (!input(SWITCH_CHAN_UP) || !input(SWITCH_CHAN_DOWN) || !input(SWITCH_VALUE_UP) || !input(SWITCH_FUNCT_UP)) { // any other key pressed...
            secretSwitchCodeIndex=0; // exit loop
         }
      }
   }
}
//======================================================================================================================
void setDisplayPowerState() {
   if (displayPowerState==0) {
      output_high(LCD_DISPLAY_POWER); // turn off LCD power (high=off)
      bklightLevel=0; // backlight off
      muteMode=1; // mute outputs
   } else {
      output_low(LCD_DISPLAY_POWER); // turn on LCD power (low=on)
      bklightLevel=read_eeprom(EEPROM_ADDR_BKLIGHT_LEVEL); // backlight is saved value
      if (bklightLevel>3) bklightLevel=3;
      muteMode=0; // dont mute
   }
   setBacklightLevel();
   delay_ms(2000);
}
//======================================================================================================================
void checkSwitchTimers(int swx, int *c, int *fx, int *rf) {
   (*fx)=0;
   if (swx==0) { // if switch is pressed...
      (*c)+=switchTimer; // increment its timer
      if ((*rf)==0) { // if it's not repeating yet...
         if ((*c)>INITIAL_TIME_SW0_MS) { // if switch held down longer than initial time
            (*fx)=1; // set switch flag to indicate first response
            (*rf)=1; // set repeat flag
            (*c)=0; // and restart counter to time for repeats
         }
      } else { // it's repeating so use the repeat time
         if ((*c)>REPEAT_TIME_SW0_MS) {
            (*fx)=2; // set switch flag to indicate second or later response
            (*c)-=REPEAT_RATE_SW0_MS; // reduce counter by repeat rate (hopefully repeat rate is less than repeatt time)
         }
      }
   } else { // switch is not pressed...
      (*c)=0; // clear its timer
      (*rf)=0; // clear its repeat flag
   }
}

//======================================================================================================================
void updateDisplay() {

   int i;
   updateScreenText();

   delay_ms(1);

   return_home();
   delay_ms(1);
   Texttest_auf_42003();
   delay_ms(1);

//   moveCursorToCurrentLocation();
}

//=================================================================================================
#int_TIMER1
TIMER1_ISR() {
   set_timer1(TIMER1_INITIAL_VALUE); //implemented as a 10ms clock

#if DEBUG_PIN_E0_TIMER_TOGGLE==1
   if (togglePinState==0) {
      togglePinState=1;
      output_high(PIN_E0);
      
   } else {
      togglePinState=0;
      output_low(PIN_E0);
   }
#endif

   if (msCounter<(unsigned int16)0xFFFF) msCounter++;

} // end of #int_TIMER1


//=================================================================================================
unsigned int scanArrowLoop=0;
void updateScreenText() {
   int i;
   unsigned int16 tempInt,tempRxID;
   char tempStr[10];

   if (rcvdChannelNumber<NUM_CHANNELS) {
      txt0[5]=(char)'1'+(char)(rcvdChannelNumber&0x07);
      if (rcvdChannelNumber&0x08) { // if it's 900 MHz, then print a colon in the "Chan:" label as a indicator
         txt0[4]=':';
      } else {
         txt0[4]=' '; // "Chan " indicates 360 MHz
      }
   } else {
      txt0[5]='-';
   }
   tempRxID=rxID;


#if DEBUG_DISPLAY_MSG_STATUS_BYTES==1
// Display of message status bytes where voltage goes
   sprintf(tempStr,"%2x",statusByte1);
   txt0[14]=(char)tempStr[0];
   txt0[15]=(char)tempStr[1];
   sprintf(tempStr,"%2x",statusByte2);
   txt0[16]=(char)tempStr[0];
   txt0[17]=(char)tempStr[1];
   txt0[18]=' ';
   txt0[19]=' ';

#else
   if (rxVoltage>255) rxVoltage=99.9;
   sprintf(tempStr,"%3u",rxVoltage);
   txt0[14]=(char)tempStr[0];
   if (tempStr[1]==' ') tempStr[1]='0';
   txt0[15]=(char)tempStr[1];
   txt0[16]='.';
   txt0[17]=(char)tempStr[2];
   txt0[19]='V';
#endif

   if (input(RS232_DETECT)) {
      txt0[10]='E';
      txt0[11]='x';
      txt0[12]='t';
   } else {
      txt0[10]=' ';
      txt0[11]=' ';
      txt0[12]=' ';
   }

   txt0[6]=' ';
   txt0[7]=' ';
   txt0[8]=' ';
   if (scanFlag!=0) {
      if (scanFlag==1) {
         scanArrowLoop++;
         if (scanArrowLoop>2) scanArrowLoop=0;
         tempInt=UP_ARROW_CHARACTER;
      } else {
         if (scanArrowLoop==0) scanArrowLoop=2;
         else scanArrowLoop--;
         tempInt=DOWN_ARROW_CHARACTER;
      }
      switch(scanArrowLoop) {
         case 0:
            txt0[6]=tempInt;
            break;
         case 1:
            txt0[7]=tempInt;
            break;
         case 2:
         default:
            txt0[8]=tempInt;
            break;
      }

   }

// RSSI Antenna A
// put into range of [0,60] indicating [-100dBm,-40dBm]
   if (rssiA>27) tempInt=rssiA-27;  
   else tempInt=0;
   tempInt/=2; // divide by 2 since each pixel equals 2 dBm
   if (tempInt>30) tempInt=30; // clamp to maxium value
   drawBargraph(22,MAX_RSSI_CHARS,tempInt);


// RSSI Antenna B
// put into range of [0,60] indicating [-100dBm,-40dBm]
   if (rssiB>27) tempInt=rssiB-27;  
   else tempInt=0;
   tempInt/=2; // divide by 2 since each pixel equals 2 dBm
   if (tempInt>30) tempInt=30;
   drawBargraph(42,MAX_RSSI_CHARS,tempInt);

// Lock indicators
   if (lockA==0) txt0[29]=' ';
   else txt0[29]=LOCK_CHARACTER;
   if (lockB==0) txt0[49]=' ';
   else txt0[49]=LOCK_CHARACTER;

// VU Left
   drawBargraph(33,MAX_VU_CHARS,vuLeft);
// VU Right
   drawBargraph(53,MAX_VU_CHARS,vuRight);

   
   updateMenuLine();
   for (i=0;i<20;i++) {
      txt0[60+i]=newMenuLine[i];
   }
   txt0[60]=UP_ARROW_CHARACTER;

/*
   if (cursorLocation==0) {
      txt0[0]=UP_ARROW_CHARACTER;
      txt0[60]=' ';
   } else {
      txt0[0]=' ';
      txt0[60]=UP_ARROW_CHARACTER;
   }
*/
}

//======================================================================================================================
void drawBargraph(int startLoc,int numSegments,int value) {
// draw bargraph
// starts at character number starting at character postion "startLoc"
// Draw a bargraph with the number of character segments equal to "numSegments"
// The value is the displayed width of the bargraph
// 0 is zero width bargraph
// numSegments*5 is full bargraph (since bargraph characters are 5 pixels wide, numSegments*5 is the total bargraph resolution)


   int i;
   if (value>5*numSegments) value=5*numSegments;
   tempDigit=value/5; // calculate number of bargraph characters that are complete segments
   for (i=0;i<tempDigit;i++) {
      txt0[startLoc+i]=208; // fill those characters with complete segments
   }
   tempDigit2=(value-(tempDigit*5)); // calculate width in led pixels (range 0--4) of last bargraph character
   if (tempDigit2>0) {
      txt0[startLoc+i]=213-tempDigit2;
      i++;
   }
   while(i<numSegments) { // fill the remaining characters with blanks
      txt0[startLoc+i]=' ';
      i++;
   }
}

void setBacklightLevel() {
   switch(bklightLevel) {
      case 0:
         set_pwm1_duty(100);
         break;
      case 1:
         set_pwm1_duty(40);
         break;
      case 2:
         set_pwm1_duty(20);
         break;
      case 3:
      default:
         set_pwm1_duty(2);
         bklightLevel=3; // safety max
         break;
   }

}
/*
void scrollMenuLine() {
   int i;
   int j;
   int endp;

   updateMenuLine();
 
   endp=19;
   if (switchFunctDownFlag>0) endp=18;
   for (j=0;j<endp;j++) {

      // scroll menu line
      txt0[60]=ARROW_CHARACTER;
      for (i=1;i<19;i++) {
         if (switchFunctDownFlag>0) { // if it's scroll down...
            txt0[79-i]=txt0[78-i];
         } else {  // otherwise it's scroll up...
            txt0[60+i]=txt0[61+i];
         }
      }
      if (switchFunctDownFlag>0) { // if it's scroll down...
         txt0[61]=newMenuLine[19-j];
      } else {  // otherwise it's scroll up...
         txt0[79]=newMenuLine[j];
      }
      setDisplayAddress(96);
      waitForDisplayNotBusy();
      writeStringToDisplay(txt0+60,20);
      delay_ms(20);
   }
}
*/

void scrollMenuLine() {
   int i;
   for (i=0;i<20;i++) {
      txt0[60+i]=newMenuLine[i];
   }
}

