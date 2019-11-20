// Mofset : https://arduino103.blogspot.com/2012/07/commande-moteur-avec-transitor-mosfet.html

//PWM PIN not affected by timers (Using Timer 1 disables PWM (analogWrite) on pins 9 and 10 - 16bit)
#define POWERPIN 11


void setup_power() {
         if(serial_debug){
          Serial.println(F("Setup power"));
        }
      pinMode(POWERPIN, OUTPUT);
}


void refresh_power() { 
    
  if(actual_power == 0){
    analogWrite(POWERPIN, 0);   
  }else{
    analogWrite(POWERPIN, actual_power*255/100); //max is 255
  }
}
