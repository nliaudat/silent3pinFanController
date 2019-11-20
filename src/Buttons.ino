//https://github.com/avandalen/avdweb_Switch

#include "Switch.h"

//Down BT
#define BtDown_Pin 2
//Up BT
#define BtUp_Pin 3

    // button to GND, use internal 20K pullup resistor
    //longpress down = setup mode
    //longpresse up = run mode (setup complete)
    
    //Switch BtDown = Switch(BtDown_Pin);  
    Switch BtDown = Switch(BtDown_Pin,INPUT_PULLUP,LOW, 100, 2000, 250, 10);
    Switch BtUp = Switch(BtUp_Pin,INPUT_PULLUP,LOW, 100, 2000, 250, 10);

    

void setup_buttons() {
      //nothing
        if(buttons_debug){
          //Serial.begin(9600);
          Serial.println(F("Buttons initiated"));
        }

}


void loop_buttons() {

      check_Down();
      check_Up();
 
  }


//////////////// Check's

/*
 * All switched have to be polled individually to update the status. Each switch-status has its own get function:

    pushed()
    Use only for push buttons. It returns "true" if a button was pushed after the poll() instruction was executed.
    released()
    It returns "true" if a push button was released, this will however rarely be used.
    on()
    Use only for toggle switches. It returns "true" as long as the switch is in the "on" position. The polarity of the switch in the "on" position has to be filled in correctly. There is no off() function, this is simply !on().
    longPress()
    It returns "true" if a push button is pressed longer than 300ms.
    doubleClick()
    It returns "true" if a push button is double clicked within 250ms.

 */



void check_Down() {
  
    BtDown.poll();//read state

    if(BtDown.longPress()){
        if(SetupMode_temp_min != true){
          SetupMode_temp_min = true;
          temp_min = temp_min +1; //cause the long press is make a press before
        }else{
          SetupMode_temp_max = true;
          SetupMode_temp_min = false;
        }
      return;
    }
  
    if(BtDown.pushed()){
      

             if(SetupMode_temp_min == true){
               if(temp_min > 0){
                  temp_min = temp_min - 1;
               }
             }
             if(SetupMode_temp_max == true){
              if(temp_max > 0 && temp_max > temp_min+1 ){
                temp_max = temp_max - 1;
              }              
             }
   
                 if(serial_debug){
                  Serial.println(F(" - 1 degree"));
                 }
      
              if(buttons_debug){
                  Serial.print(F("Down Button state : "));
                  Serial.println(BtDown.poll(), DEC);
               }
    }
}

void check_Up() {

    BtUp.poll();//read state

    if(BtUp.longPress()){
        SetupMode_temp_max = false;
        temp_max = temp_max -1; //cause the long press is make a press before
        SetupMode_temp_min = false;
        lcd_exit_SetupMode();
        lcd_refresh();
        return;
    }
  
    if(BtUp.pushed()){
      

             if(SetupMode_temp_min == true){
               if(temp_min < 50 && temp_max > temp_min+1){
                  temp_min = temp_min + 1;
               }
             }
             if(SetupMode_temp_max == true){
              if(temp_max <= 50 ){
                temp_max = temp_max + 1;
              }              
             }
   
                 if(serial_debug){
                  Serial.println(F(" + 1 degree"));
                 }
      
              if(buttons_debug){
                  Serial.print(F("UP Button state : "));
                  Serial.println(BtUp.poll(), DEC);
               }
    }
}
