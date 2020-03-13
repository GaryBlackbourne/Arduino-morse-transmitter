String message = "ha5kfu";
String code;

const int output = LED_BUILTIN;

String lettercode[] = {
  ".-",   //A
  "-...", //B
  "-.-.",  //C
  "-..",   //D
  ".",     //E
  "..-.",  //F
  "--.",   //G
  "....",  //H
  "..",    //I
  ".---",  //J
  "-.-",   //K
  ".-..",  //L
  "--",    //M
  "-.",    //N
  "---",   //O
  ".--.",  //P
  "--.-",  //Q
  ".-.",   //R
  "...",   //S
  "-",     //T
  "..-",   //U
  "...-",  //V
  ".--",   //W
  "-..-",  //X
  "-.--",  //Y
  "--.."  //Z
  };

String numode[] = {
  "-----",  //0
  ".----",  //1
  "..---",  //2
  "...--",  //3
  "....-",  //4
  ".....",  //5 
  "-....",  //6
  "--...",  //7
  "---..",  //8
  "----."   //9
  };


void beep(){
  digitalWrite(output, 1);
  delay(300);
  digitalWrite(output, 0);
  delay(300);
  return;
}

void bip(){
  digitalWrite(output, 1);
  delay(100);
  digitalWrite(output, 0);
  delay(100);
  return;
}

void space(){
  delay(700);
  return;
}

//case insensitive message conversion:
String chartomorse(char input){
  if(input >= 'a' && input <= 'z'){
    return lettercode[input-'a'];  
  }else if(input >= 'A' && input <= 'Z'){
    return lettercode[input-'A'];  
  }else if('0' <= input && input <= '9'){
    return lettercode[input-'0'];
  }else if(input == '\n' || input == ' '){
    return "spc";
  }else{
    return "err";
  }
}

void setup() {
    pinMode(output, OUTPUT);
    digitalWrite(output, 0); //set initial transmitter state to 0 (in cases of built in led, 0 is OFF)
    Serial.begin(9600);
}



void loop() {

    // if there is input, read new message:
    while(Serial.available()>0){
      message = Serial.readString();
    }

    
    for(int i = 0; i < message.length(); i++){
      
        code = chartomorse(message[i]);


        //todo: fix stupid empty serial print at the end
        Serial.print("'");
        Serial.print(code);
        Serial.print("'");
        Serial.print(" --> ");
        Serial.print(message[i]);
        Serial.println("");

        
        if(code != "err"){
          for(int j = 0; j < code.length(); j++){
            if(code[j] == '.'){
              bip();
            }
            if(code[j] == '-'){
              beep();
            }
            if(code[j]== "spc"){
              space();
            }
        }
      }
    }
    space();
}
