/*
void moveCursorToCurrentLocation() {
   char ccc[]="ABC";
   char ddd[]="DEF";
   switch (cursorLocation) {
      case 0:
         moveCursorRight(0);
         setDisplayAddress(5);
         writeStringToDisplay(ccc,3);
         delay_ms(2000);
         break;
      case 1:
         moveCursorRight(60);
        setDisplayAddress(10);
        writeStringToDisplay(ddd,3);
         delay_ms(2000);
         break;
      case 2:
         moveCursorRight(65);
         setDisplayAddress(15);
         writeStringToDisplay(ccc,3);
         delay_ms(2000);
         break;
      case 3:
         moveCursorRight(73);
         setDisplayAddress(16);
         writeStringToDisplay(ddd,3);
         delay_ms(2000);
         break;
   }
}
*/

/*
//=================================================================================================
// Code from UHorst

void display_init_42003(void);   
void Texttest_auf_42003(void);


void main(void)
{        
delay_ms(50);
init_mc();                                       
do
{
display_init_42003();
Texttest_auf_42003();
}while(1);
}

*/

// --------------------------------------------------------------------------
void writeStringToDisplay(char *c,int l) {
   int i;
   for (i=0;i<l;i++) {
      lcd_data(c[i]);
      lcd_data(c[i]<<4);
   }
}

// --------------------------------------------------------------------------
void Texttest_auf_42003(void)
{
char i; 
int j=0;         


  for(i=0;i<80;i++)  {
    j++; // just a place to break
    if (i==37) {
       lcd_busyflag_addrcount_read(&busyAddrByte0);
       lcd_busyflag_addrcount_read(&busyAddrByte1);
       j++; // just a place to break
    }
    lcd_data(txt0[i]);
    lcd_data(txt0[i]<<4);
  }

}

//=================================================================================================
// Code from example file "42003 4bit.c~" from dFeldman@Data-Modul.Com

/*Init routine and ram writing routine for BT42003 4bit (rockworks controller)*/

void display_init_42003(void) {

   //4bit   
   lcd_command(0x30);
   lcd_command(0x30);			 
   lcd_command(0x30);			 
   lcd_command(0x20);  //4 bit IF

   lcd_command(0x20); //func set RE=0
   lcd_command(0x00);

   lcd_command(0x00);  //higher nibble
   lcd_command(0xc0);  //lower nibble  disp on, cursor off, blink off

   lcd_command(0x00);  //clear disp
   lcd_command(0x10);
   delay_ms(10);

   lcd_command(0x00);  //entry mode
   lcd_command(0x60);
//   delay_ms(10);


   lcd_command(0x20);   //RE=1
   lcd_command(0x40);
//   delay_ms(10);

   lcd_command(0x00);   //4-line 
   lcd_command(0x90);
//   delay_ms(10);

   lcd_command(0x20);   //RE=0
   lcd_command(0x00); 
//   delay_ms(10);

}

// --------------------------------------------------------------------------
void return_home(void) {
   lcd_command(0x00);  //reset disp address (assume 
   lcd_command(0x20);
   delay_ms(5);
}

// --------------------------------------------------------------------------
void all_A_42003(void)
{
int i;          

for(i=0;i<160;i++)
    {
    lcd_data(0x40);   //A
    lcd_data(0x10);
    }
}     

//=================================================================================================
// my routines: "lcd_command()" and "lcd_data" are used in the above code fragment

#define DELAY_AFTER_ENABLE_USEC 1
#define DELAY_AFTER_SETUP_USEC 10
#define DELAY_AFTER_WRITE_USEC 200

// --------------------------------------------------------------------------
void lcd_command(char oneByte) {
   set_tris_d(0x00);
   output_low(DISPLAY_RS);   // RS: Low=instruction register
   output_low(DISPLAY_RW);   // R/W: Low=Write mode
   output_high(DISPLAY_E);   // E: High=Enable write
   delay_us(DELAY_AFTER_ENABLE_USEC);
   setup4bitData(oneByte);
   delay_us(DELAY_AFTER_SETUP_USEC);
   output_low(DISPLAY_E);   // E: Low=disable write
   delay_us(DELAY_AFTER_WRITE_USEC);
}

// --------------------------------------------------------------------------
void lcd_data(char oneByte) {
   set_tris_d(0x00);
   output_high(DISPLAY_RS);   // RS: High=data register
   output_low(DISPLAY_RW);   // R/W: Low=Write mode
   output_high(DISPLAY_E);   // E: High=Enable write
   delay_us(DELAY_AFTER_ENABLE_USEC);
   setup4bitData(oneByte);
   delay_us(DELAY_AFTER_SETUP_USEC);
   output_low(DISPLAY_E);   // E: Low=disable write
   delay_us(DELAY_AFTER_WRITE_USEC);
}

// --------------------------------------------------------------------------
void lcd_data_read(char *oneByte) {
   set_tris_d(0xf0);
   output_high(DISPLAY_RS);   // RS: High=data register
   output_high(DISPLAY_RW);   // R/W: High=read mode
   output_high(DISPLAY_E);   // E: High=Enable write
   read4bitData(oneByte);
   delay_us(100);
   output_low(DISPLAY_E);   // E: Low=disable write
}

// -----------------------------------------------wr---------------------------
void lcd_busyflag_addrcount_read(char *oneByte) {
   set_tris_d(0xf0);
   output_low(DISPLAY_RS);   // RS: Low=instruction register
   output_high(DISPLAY_RW);   // R/W: High=Read mode
   output_high(DISPLAY_E);   // E: High=Enable write
   read4bitData(oneByte);
   delay_us(100);
   output_low(DISPLAY_E);   // E: Low=disable write
}

// --------------------------------------------------------------------------
void setup4bitData(char xxx) {
   if ((xxx&0x10)!=0) {
      output_high(DISPLAY_BIT4);
   } else {
      output_low(DISPLAY_BIT4);
   } 
   if ((xxx&0x20)!=0) {
      output_high(DISPLAY_BIT5);
   } else {
      output_low(DISPLAY_BIT5);
   } 
   if ((xxx&0x40)!=0) {
      output_high(DISPLAY_BIT6);
   } else {
      output_low(DISPLAY_BIT6);
   } 
   if ((xxx&0x80)!=0) {
      output_high(DISPLAY_BIT7);
   } else {
      output_low(DISPLAY_BIT7);
   } 
}

// --------------------------------------------------------------------------
void read4bitData(char *xxx2) {
   *xxx2=0;
   if (input(DISPLAY_BIT4)) {
      (*xxx2)|=0x10;
   }
   if (input(DISPLAY_BIT5)) {
      (*xxx2)|=0x20;
   }
   if (input(DISPLAY_BIT6)) {
      (*xxx2)|=0x40;
   }
   if (input(DISPLAY_BIT7)) {
      (*xxx2)|=0x80;
   }
}

// --------------------------------------------------------------------------
void moveCursorOneRight() {
   lcd_command(0x10);  //higher nibble
   lcd_command(0x40);  //shift cursor to right
}

// --------------------------------------------------------------------------
void setDisplayAddress(int x) {
   char oneByte;
   oneByte=0x80;
   oneByte|=(x&0x70);
   lcd_command(oneByte);  //higher nibble
   oneByte=((x<<4)&0xf0);
   lcd_command(oneByte);  //lower nibble
}

// --------------------------------------------------------------------------
void moveCursorRight(int r) {
   int i;
   for (i=0;i<r;i++) {
      moveCursorOneRight();
   }
}
// --------------------------------------------------------------------------
void waitForDisplayNotBusy() {
   char testByte1;
   char testByte2;
   int busyFlag;
   busyFlag=1;
   do {
      lcd_busyflag_addrcount_read(&testByte1);
      lcd_busyflag_addrcount_read(&testByte2);
      if ((testByte1&0x80)==0) {
         busyFlag=0;
         busyCounter++;
      }
   } while (busyFlag==1);   
}

