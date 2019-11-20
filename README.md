# silent3pinFanController
Yet another 3 pins Fan Controller for Arduino and so on, but a silent one :)

##Reduce PWM noise :

PWM is not good to control 3 pin fan ;(

A 1N4004 diode + 100 Ohms resistor + 220uF capacitor hep to reduce noise at low speed. 
PWW frequency is reduced at 31Hz on board

## Schematics
![alt text](https://github.com/nliaudat/silent3pinFanController/raw/master/imgsfritzing.png "Board")
