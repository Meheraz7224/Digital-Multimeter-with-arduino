
//This code is written by Meheraz Rifat
//Install the libraries first
//Use Liquid Crystal library by Marco Schwartz


#include <Wire.h>
#include <LiquidCrystal.h>
#include <Adafruit_INA219.h>

Adafruit_INA219 ina219;

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);


void setup(void) 
{
  Serial.begin(9600);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  
  while (!Serial) {
      // will pause  until serial console opens
      delay(1);
  }
    
  
  
  
  if (! ina219.begin()) {
    Serial.println("Failed to find INA219 chip");
    while (1) { delay(10); }
  }
  

  
}

void loop(void) 
{
  float shuntvoltage = 0;
  float busvoltage = 0;
  float current_mA = 0;
  float loadvoltage = 0;
  float power_mW = 0;

  shuntvoltage = ina219.getShuntVoltage_mV();
  busvoltage = ina219.getBusVoltage_V();
  current_mA = ina219.getCurrent_mA();
  power_mW = ina219.getPower_mW();
  loadvoltage = busvoltage + (shuntvoltage / 1000);

  lcd.setCursor(0, 0);
  lcd.print("BV:"); lcd.print(busvoltage,1); lcd.print("V ");
  
  lcd.print("LV:"); lcd.print(loadvoltage,1); lcd.print("V");
  
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  lcd.print("I:"); lcd.print(current_mA,1); lcd.print("mA ");
  lcd.print("P:"); lcd.print(power_mW,1); lcd.print("mW");
  

  delay(2000);
}
