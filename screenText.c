void updateMenuLine() {
   int i;
   char oneChar;
   char tempStr[20];
//   newMenuLine[0]=0;
   switch(cursorLocation) {
      case 0:
      case 1:
         newMenuLine[0]=' ';
         newMenuLine[1]='M';
         newMenuLine[2]='o';
         newMenuLine[3]='d';
         newMenuLine[4]='e';
         newMenuLine[5]=':';
         newMenuLine[6]=' ';
         if (rcvdMonoMode==0) {
            newMenuLine[7] ='S';
            newMenuLine[8] ='t';
            newMenuLine[9] ='e';
            newMenuLine[10]='r';
            newMenuLine[11]='e';
            newMenuLine[12]='o';
         } else {
            newMenuLine[7] ='M';
            newMenuLine[8] ='o';
            newMenuLine[9] ='n';
            newMenuLine[10]='o';
            newMenuLine[11]=' ';
            newMenuLine[12]=' ';
         }      
         newMenuLine[13]=' ';
         newMenuLine[14]=' ';
         newMenuLine[15]=' ';
         newMenuLine[16]=' ';
         newMenuLine[17]=' ';
         newMenuLine[18]=' ';
         newMenuLine[19]=' ';
         break;
      case 2:
         newMenuLine[0]=' ';
         newMenuLine[1]='S';
         newMenuLine[2]='q';
         newMenuLine[3]='u';
         newMenuLine[4]='e';
         newMenuLine[5]='l';
         newMenuLine[6]='c';
         newMenuLine[7]='h';
         newMenuLine[8]=':';
         newMenuLine[9]=' ';
         if (maxRange==0) {
            newMenuLine[10]='N';
            newMenuLine[11]='o';
            newMenuLine[12]='i';
            newMenuLine[13]='s';
            newMenuLine[14]='e';
            newMenuLine[15]=' ';
            newMenuLine[16]='R';
            newMenuLine[17]='e';
            newMenuLine[18]='d';
            newMenuLine[19]='u';
         } else {
            newMenuLine[10]='M';
            newMenuLine[11]='a';
            newMenuLine[12]='x';
            newMenuLine[13]=' ';
            newMenuLine[14]='R';
            newMenuLine[15]='a';
            newMenuLine[16]='n';
            newMenuLine[17]='g';
            newMenuLine[18]='e';
            newMenuLine[19]=' ';
         }
         break;
      case 3:
         strcpy(newMenuLine," Filter: ");
#if DEBUG_DISABLE_FILTTYPES_FOR_MORE_RAM!=1 // use this to get more RAM for debugging (disables the filter labels) RAM must be below 91% for debugger to work
         switch (filterNumber) {
            case 0:
               strcpy(newMenuLine+9,"Flat");
               break;
            case 1:
               strcpy(newMenuLine+9,"Flat DeClik");
               break;
            case 2:
               strcpy(newMenuLine+9,"200Hz");
               break;
            case 3:
               strcpy(newMenuLine+9,"400Hz");
               break;
            case 4:
               strcpy(newMenuLine+9,"200Hz Sharp");
               break;
            case 5:
               strcpy(newMenuLine+9,"400Hz Sharp");
               break;
            case 6:
               strcpy(newMenuLine+9,"200Hz Shrpr");
               break;
            case 7:
               strcpy(newMenuLine+9,"400Hz Shrpr");
               break;
         }
#endif
         break;
      case 4:
         strcpy(newMenuLine," Tone No Lock: ");
         if (reportedToneNoLockMode==0) {
            newMenuLine[15]='O';
            newMenuLine[16]='f';
            newMenuLine[17]='f';
         } else if (reportedToneNoLockMode==1) {
            newMenuLine[15]='O';
            newMenuLine[16]='n';
            newMenuLine[17]=' ';
         } else {
            newMenuLine[15]=' ';
            newMenuLine[16]='-';
            newMenuLine[17]=' ';
         }
         newMenuLine[18]=' ';
         newMenuLine[19]=' ';
         break;
      case 5:
/*
         strcpy(newMenuLine," Backlight: ");
         newMenuLine[12]='0'+bklightLevel;
*/

         newMenuLine[0]=' ';
         newMenuLine[1]='B';
         newMenuLine[2]='a';
         newMenuLine[3]='c';
         newMenuLine[4]='k';
         newMenuLine[5]='l';
         newMenuLine[6]='i';
         newMenuLine[7]='g';
         newMenuLine[8]='h';
         newMenuLine[9]='t';
         newMenuLine[10]=':';
         newMenuLine[11]=' ';
         if (bklightLevel==0) {
            newMenuLine[12]='O';
            newMenuLine[13]='f';
            newMenuLine[14]='f';
         } else if (bklightLevel==1) {
            newMenuLine[12]='L';
            newMenuLine[13]='o';
            newMenuLine[14]='w';
         } else if (bklightLevel==2) {
            newMenuLine[12]='M';
            newMenuLine[13]='e';
            newMenuLine[14]='d';
         } else {
            newMenuLine[12]='H';
            newMenuLine[13]='i';
            newMenuLine[14]=' ';
         }

//         newMenuLine[12]='0'+bklightLevel;
//         newMenuLine[13]=' ';
//         newMenuLine[14]=' ';
         newMenuLine[15]=' ';
         newMenuLine[16]=' ';
         newMenuLine[17]=' ';
         newMenuLine[18]=' ';
         newMenuLine[19]=' ';

/*
         if (bklightLevel==0) {
            newMenuLine[12]='O';
            newMenuLine[13]='f';
            newMenuLine[14]='f';
            newMenuLine[15]=' ';
            newMenuLine[16]=' ';
            newMenuLine[17]=' ';
            newMenuLine[18]=' ';
            newMenuLine[19]=' ';
         }
         if (bklightLevel==1) {
            newMenuLine[12]='L';
            newMenuLine[13]='o';
            newMenuLine[14]='w';
            newMenuLine[15]=' ';
            newMenuLine[16]=' ';
            newMenuLine[17]=' ';
            newMenuLine[18]=' ';
            newMenuLine[19]=' ';
         }
         if (bklightLevel==2) {
            newMenuLine[12]='M';
            newMenuLine[13]='e';
            newMenuLine[14]='d';
            newMenuLine[15]=' ';
            newMenuLine[16]=' ';
            newMenuLine[17]=' ';
            newMenuLine[18]=' ';
            newMenuLine[19]=' ';
         }
         if (bklightLevel==3) {
            newMenuLine[12]='H';
            newMenuLine[13]='i';
            newMenuLine[14]='g';
            newMenuLine[15]='h';
            newMenuLine[16]=' ';
            newMenuLine[17]=' ';
            newMenuLine[18]=' ';
            newMenuLine[19]=' ';
         }
*/
         break;
      default: // this is done the first time through to display the serial number
         newMenuLine[0]=' ';
         for (i=0;i<6;i++) {
            newMenuLine[i+1]=versionString[i];
         }
         for (i=7;i<20;i++) {
            newMenuLine[i]=' ';
         }
         break;

/**/

   }
   i=0;
   oneChar=newMenuLine[i];
   while (oneChar!=0 && i<20) { // move to end of string
      i++;
      oneChar=newMenuLine[i];
   }
   while (i<20) { // fill rest with blanks
      newMenuLine[i]=' ';
      i++;
   }

}

void strcpy99(char *a,char *b) {
   int i;
   char oneChar;
   i=0;
   oneChar=1;
   while (oneChar!=0) {
      oneChar=*(b+i);
      *(a+i)=oneChar;
      i++;
   }
}