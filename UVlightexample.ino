/*


  The LCD circuit:
   LCD RS pin to digital pin 12
   LCD Enable pin to digital pin 11
   LCD D4 pin to digital pin 5
   LCD D5 pin to digital pin 4
   LCD D6 pin to digital pin 3
   LCD D7 pin to digital pin 2
   LCD R/W pin to ground
   LCD VSS pin to ground
   LCD VCC pin to 5V
   10K resistor:
   ends to +5V and ground
   wiper to LCD VO pin (pin 3)
*/

// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int waterPin = 6; //set water sensor pin
 int in1 = 7; //set input pin for the pump
 int in3 = 8; //input for light and power inverter
 int hasRun = 0; //keeps track of whether the code has run or not since we only want it to do this once
 int lightRun = 0; //if the light has run the arduino will only display voltages
 int AnalogPin = A0; //for voltages
 float BatteryVoltage; //you need float type so it is accurate
 float oldBatteryVoltage;

void setup() {
    // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("assessing water and battery...");
  pinMode(in1, OUTPUT);
  pinMode(in3, OUTPUT);
  digitalWrite(in1, LOW); //basically sets it as initially off
  digitalWrite(in3, LOW);
  BatteryVoltage = analogRead(AnalogPin);  //reading  the analog  input value
  float realBatteryVoltage = 15*BatteryVoltage/1023; //you need this because it is analog
  float oldBatteryVoltage = realBatteryVoltage; //keep track of last battery voltage

  }

void loop() {
  BatteryVoltage = analogRead(AnalogPin);  //reading  the analog  input value
  float realBatteryVoltage = 15*BatteryVoltage/1023;
  lcd.setCursor(0, 0);
  lcd.print(realBatteryVoltage);
  lcd.print("V ");
  if (oldBatteryVoltage > realBatteryVoltage) { //to see if it is charging or discharging
    lcd.print("discharging-pedal");
  }
  else if (realBatteryVoltage > oldBatteryVoltage) {
    lcd.print("charging-good");
  }
  oldBatteryVoltage = realBatteryVoltage; //set the voltage for the next loop
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  //lcd.print(millis() / 1000);
   if (digitalRead(waterPin) == LOW) { //since our code was only for the UV light, we simulated this part with sweaty fingers
     lcd.setCursor(0, 1);
    lcd.print("not full yet");
   } //if the water level is low the below doesn't run
   else {
    lcd.setCursor(0, 1);
    lcd.print("                "); //need this to clear the LCD
    lcd.setCursor(0, 1);
    lcd.print("water level ok"); //if water is detected...
    delay(1000);
     lcd.setCursor(0, 1);
    lcd.print("                ");
    delay(2000);
     if (hasRun==0){
     lcd.setCursor(0, 1);
    lcd.print("LID! light soon"); //warn you to make sure the lid is on
  delay(20000);
     lcd.setCursor(0, 1);
      lcd.print("                ");
       lcd.setCursor(0, 1);
  lcd.print("light-dont look!"); //warn the user to not look at the light
  digitalWrite(in3, HIGH); //turn on the light
  delay(30000);
  digitalWrite(in3, LOW); //30 seconds later, but you might want to revise this to longer, turn light off
  delay(1000);
   lcd.setCursor(0, 1);
  lcd.print("                ");
   lcd.setCursor(0, 1);
  lcd.print("light off-drink!");
  delay(10000);
  hasRun = 1;
   }
   }
   
}

//if you want to add the pump, add controls for in1 or whatever relay your pump is on
//to HIGH and LOW 
//as in the examples for in3 above, where the light is hooked up

