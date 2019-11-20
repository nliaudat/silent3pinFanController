//I2C LCD : https://www.makerguides.com/character-i2c-lcd-arduino-tutorial/

#include "LiquidCrystal_I2C.h" // // LiquidCrystal_I2C.h: https://github.com/johnrickman/LiquidCrystal_I2C

//#include <hd44780.h> //to test
    
// Wiring: SDA pin is connected to A4 and SCL pin to A5.
// Connect to LCD via I2C, default address 0x27 (A0-A2 not jumpered)


//create custom icon
//https://omerk.github.io/lcdchargen/

byte thermometer[8] =
{
    B00100,
    B01010,
    B01010,
    B01010,
    B01110,
    B11111,
    B11111,
    B01110
};

byte humidity[8] =
{
    B00100,
    B00100,
    B01010,
    B01010,
    B10001,
    B10001,
    B10001,
    B01110,
};


//Custom degree character
byte degree[8] = {
  B00110,
  B01001,
  B01001,
  B00110,
  B00000,
  B00000,
  B00000,
  B00000
};


byte power[8] = {
  B00001,
  B00010,
  B00100,
  B01011,
  B00110,
  B10100,
  B11000,
  B11100
};


byte progress1[8] = {
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B11111
};

byte progress2[8] = {
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B11111,
    B11111,
    B11111
};

byte progress3[8] = {
    B00000,
    B00000,
    B00000,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111
};

byte progress4[8] = {
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111
};



LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2);


void setup_LiquidCrystal() {

       if(serial_debug){
          Serial.println(F("Setup LCD"));
        }

        lcd.init();
        //init custom chars
        lcd.createChar(1,thermometer);
        lcd.createChar(2,humidity);
        lcd.createChar(3,power);
        lcd.createChar(4,power);
        lcd.createChar(5,progress1);
        lcd.createChar(6,progress2);
        lcd.createChar(7,progress3);
        lcd.createChar(8,progress4);

        lcd.backlight();
        lcd_set_default();

}


void lcd_set_default(){

        lcd.clear();
        lcd.setCursor(0,0); 
        // print the custom char to the lcd
        // why typecast? see: http://arduino.cc/forum/index.php?topic=74666.0
        lcd.write(byte(1)); //thermometer
        //lcd.print(actual_temperature);
        lcd.print(F(": 00"));
        lcd.print((char)223);//degree
        lcd.print(F("C "));
        lcd.write((uint8_t)2);//humidity
        //lcd.print(actual_humidity);
        lcd.print(F(":00"));
        lcd.print(F("%"));
        lcd.setCursor(0,1);
        //lcd.print("Fan:");
        lcd.write((uint8_t)4);//fan_off
        //lcd.print(actual_power);
        lcd.print(F(":000")); 
        lcd.print("% ");
}



void set_progress(int count){

      //lcd.print("\\");//yen symbol - my HD44780U is Chinese =>  ROM Code is A00 //https://www.sparkfun.com/datasheets/LCD/HD44780.pdf and cannot display \
    lcd.write(0b01011100); 
    
  lcd.setCursor(15,0);
  switch (count) {
  case 1:
    //lcd.print("|");
    lcd.write((uint8_t)5);//progress 5-8
    break;
  case 2:
  lcd.write((uint8_t)6);//progress 6-8
    //lcd.print(">");
    break;
  case 3:
  lcd.write((uint8_t)7);//progress 7-8
    //lcd.print("-");
    break;
  case 4:
  lcd.write((uint8_t)8);//progress 8-8
    //lcd.print("<");
    break;
  default:
    // if nothing else matches, do the default
    // default is optional
    break;
  }
}

void lcd_SetupMode(){
        
        lcd.setCursor(8,1);
        lcd.print(F("["));
        lcd.print(temp_min);
        lcd.print((char)223);//degree
        lcd.print(F("-"));//degree
        lcd.print(temp_max);
        lcd.print(F("]"));
        lcd.print((char)223);//degree

      if(SetupMode_temp_min){
        lcd.setCursor(10,1);
        lcd.blink();
      } else{
        lcd.setCursor(14,1);
        lcd.blink();
      }

  
}

void lcd_exit_SetupMode(){
  lcd.noBlink();
  lcd.setCursor(8,1);
  //lcd.print("         ");
}

void lcd_refresh(){

 

      if(lcd_debug){
        lcd.clear();
        lcd.setCursor(0,0); 
        lcd.print(F("TA:"));
        lcd.print(actual_temperature);
        lcd.print(F("C "));
        lcd.setCursor(0,1);
        lcd.print(F("Fan:"));
        lcd.print(actual_power);
        lcd.print(F("%"));
    
      return;
      }



        //"T:" => pos 3
        lcd.setCursor(3,0); 
        lcd.print(actual_temperature);
        //"T: 00°C H:00%" => pos 10
        lcd.setCursor(10,0);
        lcd.print(actual_humidity);
        //F:000%
        lcd.setCursor(2,1);
        if(actual_power < 100){
          lcd.print(" ");
          lcd.print(actual_power);
        }else if(actual_power ==0){
          lcd.print("  0");
        }else{
          lcd.print(actual_power);
        }
        lcd.setCursor(7,1);

}
