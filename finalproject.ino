#include <LiquidCrystal.h>
LiquidCrystal LcdDriver(11, 9, 5, 6, 7, 8 );//pins required to interface to the LCD, based on traces from schematic
volatile int cycleTime;//creates a volatile (will be changed often) integer to act as the encoder's position
unsigned long timer; //creates a timer to use as the basis for updating the LCD Display
float RPM;


void MonitorA() { //Method for monitoring turning encoder to the left
  if (bitRead(PIND, 2) == bitRead(PIND, 3)) { 
    cycleTime--; //decrements encoder position
  }
  else {
    cycleTime++;//increments encoder position
  }
}

void MonitorB() { //Method for monitoring turning encoder to the right
  if (bitRead(PIND, 2) == bitRead(PIND, 3)) {
    cycleTime++;//increments encoder position
  }
  else {
    cycleTime--;//decrements encoder position
  }
}

void setup() {
  pinMode(2, INPUT);//sets pin 2 to read input (in this case, the encoder)
  pinMode(3, INPUT);//sets pin 3 to read input (in this case, the encoder)
  attachInterrupt(digitalPinToInterrupt(2), MonitorA, CHANGE);//performs Monitor A Method if input changes
  attachInterrupt(digitalPinToInterrupt(3), MonitorB, CHANGE);//performs Monitor B Method if input changes
  timer = millis(); //set timer to count milliseconds
  LcdDriver.begin(16, 2);//sets up LCD Display
}

void loop() {//main method to be looped
  if (millis() - timer >= 100) {
    LcdDriver.clear();//clears LCD Display
    LcdDriver.print(RPM);//prints the encoder's position to the LCD Display
    timer = millis();//sets timer to count milliseconds
  }
}



