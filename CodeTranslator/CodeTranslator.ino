//__________________________________________LOOK UP TABLE_____________________________________________________________
// Alphabet
  char ascii_A[]        = "*";
  char ascii_B[]        = "!!*";
  char ascii_C[]        = "!!@";
  char ascii_D[]        = "*!";
  char ascii_E[]        = "!";
  char ascii_F[]        = "!*!";
  char ascii_G[]        = "**";
  char ascii_H[]        = "!**";
  char ascii_I[]        = "!!";
  char ascii_J[]        = "*!!";
  char ascii_K[]        = "*@";
  char ascii_L[]        = "!*@";
  char ascii_M[]        = "!*";
  char ascii_N[]        = "!@";
  char ascii_O[]        = "@*";
  char ascii_P[]        = "!@!";
  char ascii_Q[]        = "*!@";
  char ascii_R[]        = "!@*";
  char ascii_S[]        = "@!";
  char ascii_T[]        = "@";
  char ascii_U[]        = "@@";
  char ascii_V[]        = "**!";
  char ascii_W[]        = "***";
  char ascii_X[]        = "*@!";
  char ascii_Y[]        = "!@@";
  char ascii_Z[]        = "**@";
  char ascii_SPACE[]    = " ";
  
// Numbers
  char ascii_ONE[]      = "@!!*";
  char ascii_TWO[]      = "@!!@";
  char ascii_THREE[]    = "@!*!";
  char ascii_FOUR[]     = "@!**";
  char ascii_FIVE[]     = "@!*@";
  char ascii_SIX[]      = "@!@!";
  char ascii_SEVEN[]    = "@!@*";
  char ascii_EIGHT[]    = "@!@@";
  char ascii_NINE[]     = "@*!!";
  char ascii_ZERO[]     = "@!!!";

// Specials
  char ascii_STOP[]     = "@!!";
  char ascii_COMMA[]    = "@!*";
  char ascii_APOS[]     = "@*!";
  char ascii_QUESTION[] = "@**";
  char ascii_EXCLAM[]   = "@*@";
  char ascii_PLUS[]     = "@@!";
  char ascii_MINUS[]    = "@@*";
  char ascii_MULTIPLY[] = "@@@";
  char ascii_DIVIDE[]   = "@!@";

  
//__________________________________________Variable setup_________________________________________________________________________
  char buff[400];//If string size is more than 400, it will mess up(Meaning a bigger buffer is needed).
  int bufferSize = 400; 

  int const inputBufferLength=  400;

  char input [inputBufferLength];
  int start = 0;

// Boolean
  bool inputWasASH   = false;      
  bool inputWasASCII = false;      
  bool pastWasChar   = false;      //Used to check previous char to see if a backslash should be added for ash output

// Hardware pins   
  int  potPin    = A0;           
  byte redLED    = 5;              
  byte yellowLED = 6;              
  byte amberLED  = 9;              
  byte greenLED  = 10;             
  byte blueLED   = 11;           
  int  irLED     = A1;             
  
  
  
//__________________________________________Void setup___________________________________________________________________
void setup() {
  Serial.begin(9600);
  
  pinMode(redLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(amberLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(blueLED, OUTPUT);
  pinMode(irLED, OUTPUT);
}


//__________________________________________ASCII String to Ash String____________________________________________________
void ascii2ASH (char* ip, char* buff, int bufferLength){
  inputWasASCII = true;
  
  for (int i = 0; ip[i] != 0; i++){
    if  (i == 0){
     strcpy(buff, char2ASCII(ip[i])); // Strcpying the first time as you can't
    }
    else if (i != bufferLength){
      if (pastWasChar == true && (ip[i] != ' ')){
       strcat(buff,"/"); 
      }
     strcat(buff, char2ASCII(ip[i]));
     }
  }
    Serial.println(buff);
    flashTheAsh();
}


//___________________________________________Ash string to ASCII string function___________________________________________
void ashToASCII (char* ip, char* buf, int bufferLength){
  char redLEDValueAsChar[4];
  char yellowLEDValueAsChar[4];
  char amberLEDValueAsChar[4];
  char greenLEDValueAsChar[4];
  
  int redLEDBightness;
  int yellowLEDBrightness;
  int amberLEDBrightness;
  int greenLEDBrightness;
  
  inputWasASH = true;
  char localBuffer[20];
  byte localCounter = 0;
  byte bufferIncrementer =0;
  for (int i=0; i <= strlen(ip);i++){
    
    if (ip[i] == '!' || (ip[i] == '*') || (ip[i] == '@')){
      localBuffer[localCounter] = ip[i];
      localCounter++;
    }

    else if (ip[i] == '/'){
      localBuffer[localCounter] = '\0';
      buff[bufferIncrementer] = ash2char(localBuffer);
      bufferIncrementer++;
      localCounter = 0;
    }
    
    else if (ip[i] == ' '){
      // Dealing with previous morse
      localBuffer[localCounter] = '\0';
      localCounter = 0;
      buff[bufferIncrementer] = ash2char(localBuffer);
      bufferIncrementer++;
      
      // Dealing with the space
      buff[bufferIncrementer] = ' ';
      bufferIncrementer++;
    }
    
    else if (ip[i] == '\0'){
      localBuffer[localCounter] = '\0';
      buff[bufferIncrementer] = ash2char(localBuffer);
      bufferIncrementer++;
      localCounter = 0;
    }
    
  }
  
  if (buff[0]=='L' && buff[1]=='P' && strlen(buff)==14){
    redLEDValueAsChar[0]    = buff[2];
    redLEDValueAsChar[1]    = buff[3];
    redLEDValueAsChar[2]    = buff[4];
    redLEDValueAsChar[3]    = '\0';
    
    yellowLEDValueAsChar[0] = buff[5];
    yellowLEDValueAsChar[1] = buff[6];
    yellowLEDValueAsChar[2] = buff[7];
    yellowLEDValueAsChar[3] = '\0';
    
    amberLEDValueAsChar[0] = buff[8];
    amberLEDValueAsChar[1] = buff[9];
    amberLEDValueAsChar[2] = buff[10];
    amberLEDValueAsChar[3] = '\0';
      
    greenLEDValueAsChar[0] = buff[11];
    greenLEDValueAsChar[1] = buff[12];
    greenLEDValueAsChar[2] = buff[13];
    greenLEDValueAsChar[3] = '\0';

    redLEDBightness = atoi(redLEDValueAsChar);
    yellowLEDBrightness = atoi(yellowLEDValueAsChar);
    amberLEDBrightness = atoi(amberLEDValueAsChar);
    greenLEDBrightness = atoi(greenLEDValueAsChar);
    
    analogWrite(redLED, redLEDBightness);
    analogWrite(yellowLED, yellowLEDBrightness);
    analogWrite(amberLED, amberLEDBrightness);
    analogWrite(greenLED, greenLEDBrightness);
  }
  Serial.println(buff);
  flashTheAsh();
}

//______________________________Storing user input_________________________________________________________________________
void valuePrompt(char* input, int inputBufferLength){
  while (!Serial.available()){
    ;
  }
  for(int i=0; Serial.available() > 0;){
    if(i < inputBufferLength){  
       input[i] = Serial.read();
       i++;
       input[i] = '\0';
       delay(10); 
    }
  }
}

//_______________________________Waiting for input and checking type______________________________________________________
void loop(){
  valuePrompt(input, inputBufferLength);
  while(input[start] == ' '){
    start++;
  }
  
    if(input[start] == '*' || input[start] == '@' || input[start] == '!'){
      checkDataMessage();
      ashToASCII(input, buff, bufferSize);  
      start = 0;
    }
    
    else{
      ascii2ASH(input, buff, bufferSize);  
      start = 0;
    }

  for(int i = 0; i < 99; i++){  
    buff[i]  = '\0';
    input[i] = '\0';
  }
}


//________________________________Checking if ASH was a data message______________________________________________________
void checkDataMessage(){
// Setting local variables
  char formatBuffer[10]; // This will store potentiometer values before ascii2ASH is called on it
  char mainLocalBuffer[10];
  
  char CMD_IR_ON[]   = "@/*@!/!!/!@*";    // Equal to the ASCII "TXIR"    ~ This command will turn the IR LED ON
  char CMD_IR_OFF[]  = "@@*/@@*/!!/!@*";  // Equal to the ASCII "--IR"    ~ This Command will turn the IR LED OFF
  char CMD_PT[]      = "!@!/@";           // Equal to the ASCII "PT"      ~ This command will display the potentiometer value
  
  
  if (strcmp(input,CMD_IR_ON) == 0){      //Checks if user tried to turn on IR LED
     pinMode(irLED, OUTPUT);              //Sets the IR pin as an output
     digitalWrite(irLED, HIGH);           //Turns on the IR LED
  }
  
  else if(strcmp(input,CMD_IR_OFF) == 0){ //Checks if user tried to turn off the IR LED
     digitalWrite(irLED, LOW);            //Turns off the IR LED
  }
  
  
  // Reading and converting the value from the potentiometer
  else if(strcmp(input, CMD_PT) == 0){     //Checks if the user requested the value from the potentiometer
    
    if (analogRead(potPin) >= 1000){
      String potValue = String(analogRead(potPin));     // Converting the Pot int value into a string
      potValue.toCharArray(formatBuffer, 10);              // Convering the string to a Char Array
      formatBuffer[4] = '\0';                             // Null terminating the buffer for reuse
      strcpy(mainLocalBuffer, formatBuffer);                
      ascii2ASH(mainLocalBuffer, buff, bufferSize); 
    }
    
    else if(analogRead(potPin) < 1000 && analogRead(potPin) > 100){
      String potValue = String(analogRead(potPin));     // Converting the Pot int value into a string
      potValue.toCharArray(formatBuffer, 10);              // Converting the string to a char Array
      formatBuffer[3] = '\0';                             // Null terminating the format buffer for reuse
      mainLocalBuffer[0] = '0';                             // Adding a 0 before the Pot value to give correct format
      mainLocalBuffer[1] = '\0';                            // Null terminating the buffer before concatenation 
      strcat(mainLocalBuffer, formatBuffer);                 // Copying format buffer into mainLocalBuffer
      ascii2ASH(mainLocalBuffer, buff, bufferSize); 
    }
    
    else if(analogRead(potPin) < 100 && analogRead(potPin) >= 10){
      String potValue = String(analogRead(potPin));     
      potValue.toCharArray(formatBuffer, 10);              
      formatBuffer[2] = '\0';                             
      mainLocalBuffer[0] = '0';                             
      mainLocalBuffer[1] = '0';                             
      mainLocalBuffer[2] = '\0';
      strcat(mainLocalBuffer, formatBuffer);                 
      ascii2ASH(mainLocalBuffer, buff, bufferSize); 
    }
    
    else if (analogRead(potPin) < 10){
      String potValue = String(analogRead(potPin));     
      potValue.toCharArray(formatBuffer, 10);              
      formatBuffer[1] = '\0';                            
      mainLocalBuffer[0] = '0';                             
      mainLocalBuffer[1] = '0';                             
      mainLocalBuffer[2] = '0';                             
      mainLocalBuffer[3] = '\0';
      strcat(mainLocalBuffer, formatBuffer);             
      ascii2ASH(mainLocalBuffer, buff, bufferSize); 
    }
    
    for(int i = 0; i < 9; i++){  
      mainLocalBuffer[i] = '\0';
      formatBuffer[i] = '\0';
      buff[2] = '\0';
    }
  }
}


//__________________________________________FlashTheAsh___________________________________________________________________
void flashTheAsh(){
  int  timeUnit;
  byte LED;
  timeUnit = readPot(); // Time unit determined by potentiometer

  if (inputWasASH == true){
    LED = blueLED;
  }
  else if (inputWasASCII == true){
    LED = redLED;
  } 
  pinMode (LED, OUTPUT);
  
  if (inputWasASCII == true){
    for (int index=0; index < strlen(buff); index++){
      if (buff[index] == '!'){
        delay(timeUnit);              //Adds delay between signals forming the same letter
        digitalWrite(LED, HIGH);      //Turns on the LED
        delay(timeUnit);              //Delays by one time unit
        digitalWrite(LED,LOW);        //Turns off the LED
      }
      
      else if (buff[index] == '*'){
        delay(timeUnit);             
        digitalWrite(LED, HIGH);     
        delay(timeUnit*2);            
        digitalWrite(LED,LOW);      
      }
      
      else if (buff[index] == '@'){
        delay(timeUnit);             
        digitalWrite(LED, HIGH);     
        delay(timeUnit*4);            
        digitalWrite(LED,LOW);       
      }
      
      else if (buff[index] == '/'){
        delay(timeUnit*4);            // Adds delay between chars in the same word (four time units)
      }
      
      else if (buff[index] == ' '){
        delay(timeUnit*8);            // Delay between words (Eight time units) 
      }
    }
  }
  
  else if (inputWasASH == true){
    for (int index=0; index < strlen(input);index++){
      if (input[index] == '!'){
        delay(timeUnit);              // Adds delay between signals forming the same letter
        digitalWrite(LED, HIGH);      // Turns the LED on
        delay(timeUnit);              // Delays by one time unit
        digitalWrite(LED, LOW);        // Turns the LED off
      }
      
      else if (input[index] == '*'){
        delay(timeUnit);              
        digitalWrite(LED, HIGH);      
        delay(timeUnit*2);            
        digitalWrite(LED, LOW);       
      }
      
      else if (input[index] == '@'){
        delay(timeUnit);              
        digitalWrite(LED, HIGH);    
        delay(timeUnit*4);            
        digitalWrite(LED, LOW);        
      }
      
      else if (input[index] == '/'){
        delay(timeUnit*4);          
      }
      
      else if (input[index] == ' '){
        delay(timeUnit*8);            
      }
    }
  }

      inputWasASH   = false;
      inputWasASCII = false;
}


//____________________Function to read value from potentiometer_______________________________________________________
int readPot(){
  int val;
  
  if ((analogRead(potPin)/2) <= 40){
    val = 20;
  }
  else if ((analogRead(potPin) / 2) >= 500){
    val = 500; 
  }
  else {
    val = (analogRead(potPin) / 2);
  }
  return val;
}


//__________________________________________Switch statment___________________________________________________________
char* char2ASCII(char c){
  
   // This uses the ascii table char values to convert lower case chars to upper case. 
   if(c > 96 && c < 123){
     c -= 32; 
   }
  
  switch(c){
  case 'A':
    pastWasChar = true;
    return ascii_A;
  case 'B':
    pastWasChar = true;
    return ascii_B; 
  case 'C':
    pastWasChar = true;
    return ascii_C;
  case 'D':
    pastWasChar = true;
    return ascii_D;
  case 'E':
    pastWasChar = true;
    return ascii_E;  
  case 'F':
    pastWasChar = true;
    return ascii_F;
  case 'G':
    pastWasChar = true;
    return ascii_G;
  case 'H':
    pastWasChar = true;
    return ascii_H;
  case 'I':
    pastWasChar = true;
    return ascii_I;
  case 'J':
    pastWasChar = true;
    return ascii_J;
  case 'K':
    pastWasChar = true;
    return ascii_K;
  case 'L':
    pastWasChar = true;
    return ascii_L;
  case 'M':
    pastWasChar = true;
    return ascii_M;
  case 'N':
    pastWasChar = true;
    return ascii_N;
  case 'O':
    pastWasChar = true;
    return ascii_O;
  case 'P':
    pastWasChar = true;
    return ascii_P;
  case 'Q':
    pastWasChar = true;
    return ascii_Q;
  case 'R':
    pastWasChar = true;
    return ascii_R;
  case 'S':
    pastWasChar = true;
    return ascii_S;
  case 'T':
    pastWasChar = true;
    return ascii_T;
  case 'U':
    pastWasChar = true;
    return ascii_U;
  case 'V':
    pastWasChar = true;
    return ascii_V;
  case 'W':
    pastWasChar = true;
    return ascii_W;
  case 'X':
    pastWasChar = true;
    return ascii_X;
  case 'Y':
    pastWasChar = true;
    return ascii_Y;
  case 'Z':
    pastWasChar = true;
    return ascii_Z;
  case ' ':
    pastWasChar = false;
    return ascii_SPACE;
  case '1':
    pastWasChar = true;
    return ascii_ONE;
  case '2':
    pastWasChar = true;
    return ascii_TWO;
  case '3':
    pastWasChar = true;
    return ascii_THREE;
  case '4':
    pastWasChar = true;
    return ascii_FOUR;
  case '5':
    pastWasChar = true;
    return ascii_FIVE;
  case '6':
    pastWasChar = true;
    return ascii_SIX;
  case '7':
    pastWasChar = true;
    return ascii_SEVEN;
  case '8':
    pastWasChar = true;
    return ascii_EIGHT;
  case '9':
    pastWasChar = true;
    return ascii_NINE;
  case '0':
    pastWasChar = true;
    return ascii_ZERO;
  case '.':
    pastWasChar = true;
    return ascii_STOP;
  case ',':
    pastWasChar = true;
    return ascii_COMMA;
  case '\'':
    pastWasChar = true;
    return ascii_APOS;
  case '?':
    pastWasChar = true;
    return ascii_QUESTION;
  case '!':
    pastWasChar = true;
    return ascii_EXCLAM;
  case '+':
    pastWasChar = true;
    return ascii_PLUS;
  case '-':
    pastWasChar = true;
    return ascii_MINUS;
  case '*':
    pastWasChar = true;
    return ascii_MULTIPLY;
  case '/':
    pastWasChar = true;
    return ascii_DIVIDE;
  }
}

//__________________________________________If statements_____________________________________________________________
char ash2char(char* m){
  if (strcmp(m, ascii_A) == 0){
    return 'A';
  } 
  else if (strcmp(m, ascii_B) == 0){
    return 'B';
  } 
  else if (strcmp(m, ascii_C) == 0){
    return 'C';
  } 
  else if (strcmp(m, ascii_D) == 0){
    return 'D';
  } 
  else if (strcmp(m, ascii_E) == 0){
    return 'E';
  } 
  else if (strcmp(m, ascii_F) == 0){
    return 'F';
  } 
  else if (strcmp(m, ascii_G) == 0){
    return 'G';
  } 
  else if (strcmp(m, ascii_H) == 0){
    return 'H';
  } 
  else if (strcmp(m, ascii_I) == 0){
    return 'I';
  } 
  else if (strcmp(m, ascii_J) == 0){
    return 'J';
  } 
  else if (strcmp(m, ascii_K) == 0){
    return 'K';
  } 
  else if (strcmp(m, ascii_L) == 0){
    return 'L';
  } 
  else if (strcmp(m, ascii_M) == 0){
    return 'M';
  } 
  else if (strcmp(m, ascii_N) == 0){
    return 'N';
  } 
  else if (strcmp(m, ascii_O) == 0){
    return 'O';
  } 
  else if (strcmp(m, ascii_P) == 0){
    return 'P';
  } 
  else if (strcmp(m, ascii_Q) == 0){
    return 'Q';
  } 
  else if (strcmp(m, ascii_R) == 0){
    return 'R';
  } 
  else if (strcmp(m, ascii_S) == 0){
    return 'S';
  } 
  else if (strcmp(m, ascii_T) == 0){
    return 'T';
  } 
  else if (strcmp(m, ascii_U) == 0){
    return 'U';
  } 
  else if (strcmp(m, ascii_V) == 0){
    return 'V';
  } 
  else if (strcmp(m, ascii_W) == 0){
    return 'W';
  } 
  else if (strcmp(m, ascii_X) == 0){
    return 'X';
  } 
  else if (strcmp(m, ascii_Y) == 0){
    return 'Y';
  } 
  else if (strcmp(m, ascii_Z) == 0){
    return 'Z';
  } 
  else if (strcmp(m, ascii_SPACE) == 0){
    return '/';
  } 
  else if (strcmp(m, ascii_ONE) == 0){
    return '1';
  } 
  else if (strcmp(m, ascii_TWO) == 0){
    return '2';
  } 
  else if (strcmp(m, ascii_THREE) == 0){
    return '3';
  } 
  else if (strcmp(m, ascii_FOUR) == 0){
    return '4';
  } 
  else if (strcmp(m, ascii_FIVE) == 0){
    return '5';
  } 
  else if (strcmp(m, ascii_SIX) == 0){
    return '6';
  } 
  else if (strcmp(m, ascii_SEVEN) == 0){
    return '7';
  } 
  else if (strcmp(m, ascii_EIGHT) == 0){
    return '8';
  } 
  else if (strcmp(m, ascii_NINE) == 0){
    return '9';
  } 
  else if (strcmp(m, ascii_ZERO) == 0){
    return '0';
  }
  else if (strcmp(m, ascii_STOP) == 0){
    return '.';
  }
  else if (strcmp(m, ascii_COMMA) == 0){
    return ',';
  }
  else if (strcmp(m, ascii_APOS) == 0){
    return '\'';
  }
  else if (strcmp(m, ascii_QUESTION) == 0){
    return '?';
  }
  else if (strcmp(m, ascii_EXCLAM) == 0){
    return '!';
  }
  else if (strcmp(m, ascii_PLUS) == 0){
    return '+';
  }
  else if (strcmp(m, ascii_MINUS) == 0){
    return '-';
  }
  else if (strcmp(m, ascii_MULTIPLY) == 0){
    return '*';
  }
  else if (strcmp(m, ascii_DIVIDE) == 0){
    return '/';
  }
}







