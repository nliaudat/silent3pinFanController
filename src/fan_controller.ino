
//arduino nano
//Processor ATmega328P (old bootloader)

static const bool serial_debug = false;
static const bool lcd_debug = false;
static const bool buttons_debug = false;


volatile uint8_t temp_min = 27; //(uint8_t) 0 to 255 no signed int  ("uint8_t" free 2 bytes compared to "volatile unsigned int" )
volatile uint8_t temp_max = 37;

static const uint8_t power_min = 40; //my 12V fan cannot run under 4V of power. 5V is noisy

volatile uint8_t actual_temperature = 0;
volatile uint8_t actual_power = 0;
volatile uint8_t actual_humidity = 0;

volatile bool fan_state_icon = false;

volatile uint8_t last_temperature = 0;
volatile uint8_t diff = 100;

volatile bool need_refresh = false;

//volatile bool SetupMode = false;
volatile bool SetupMode_temp_min = false;
volatile bool SetupMode_temp_max = false;

uint8_t progress_counter = 1;

static const uint8_t check_temperature_interval = 15; //test temperature sensor every X seconds
uint8_t check_temperature_counter = 1; //counter

//const int buzzerPin = 12;

void setup(){

        if(serial_debug){
          Serial.begin(9600);
          //https://www.baldengineer.com/arduino-f-macro.html
          //Serial.println("main debug :");
          Serial.println(F("main debug :"));
        }

     setPwmFrequency(11,1024); //reduce noise of the fans by setting pwm at 31Hz (min)
     //TCCR2B = TCCR2B & 0b11111000 | 0x07;
     
     setup_LiquidCrystal();// Initiate the LCD
     setup_timer1(); //timer1 = 1 sec
     setup_power(); //
     setup_buttons();

     
}

void loop() {
  //timer1 set need_refresh every 1 second 
  if (need_refresh==1) 
  {
    refresh();
    need_refresh=0;
    }

  loop_buttons();
}


void refresh(){ 

      if(SetupMode_temp_min || SetupMode_temp_max){
        lcd_SetupMode();
        return;
      }
      
      if(progress_counter < 4){
        progress_counter += 1;
      }else{
        progress_counter = 1;
      }
      set_progress(progress_counter); //lcd display progress (to check if hang ;))


      if(check_temperature_counter < check_temperature_interval){
        check_temperature_counter += 1;
      }else{
        check_temperature_counter = 1;
        check_temperature(); //check sensor and update lcd
      }

  
}

void check_temperature(){ 

      
      //check temp
      dht11_refresh();

      diff = actual_temperature - last_temperature;
      last_temperature = actual_temperature;

      if(diff == 0){
        //exit
        return;
      }

      actual_power = map(actual_temperature, temp_min, temp_max, power_min, 100);

      if(actual_temperature < temp_min){
          actual_power = 0; //stop
          //fan_state_change();
      }

      if(actual_temperature > temp_max){
        actual_power = 100;
      }



      //refresh lcd
      lcd_refresh();

      //adjust power
      refresh_power();
  
}
