/*
 *make sure you go back and set a 2 step margin on each side
 *the 'on' switch for motors must be HIGH reading on hot line
 *up/down buttons to adjust/set presets
 *preset buttons
 *shut hot valve if exceeds threshold for safety
 *add sensor on hot side to trigger loop once hot water is present
*/

#define momentary A2
#define onSwitch A1
#define ONE_WIRE_BUS 2 //2 is digital pin number




#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal.h>

int switchState = 0;
int prevSwitchState = 0;

int target =-200;
int Temp =0;

int valveCold =35;
int valveHot =35;
int stepCounter =0;
int Cold =0;
int Hot = 0;

LiquidCrystal lcd(12, 11, 7, 8, 9, 10);//(RS,E,DB4,DB5,DB6,DB7) don't forget the pins are backward from silkscreen!

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire); 

void setup(){

  lcd.begin(16, 2);
  lcd.print("Waiting");
  
pinMode(3, OUTPUT); //define all pinModes here
pinMode(4, OUTPUT);
pinMode(12,OUTPUT);
pinMode(5, OUTPUT);
pinMode(6, OUTPUT);

Serial.begin(9600);
//turn on power save mode


sensors.begin();

}


void loop(){
 sensors.requestTemperatures(); // Send the command to get temperatures
 int Temp = (((sensors.getTempCByIndex(0))*1.8)+32); 

 //I think these next two blocks are designed to prevent shitty water pressure
 while(valveCold <20){
   for(valveCold=19; valveCold<35; valveCold++){
    digitalWrite(4, HIGH);
    digitalWrite(3, HIGH);
    delay(1);          
    digitalWrite(3, LOW); 
    delay(500);
    Serial.print("Cold: ");
    Serial.println(valveCold);
   }
  }
   
 while(valveHot < 20){
   for (valveHot =19; valveHot<35; valveHot++){
    digitalWrite(6, HIGH);
    digitalWrite(5, HIGH);
    delay(1);          
    digitalWrite(5, LOW); 
    delay(500);
     Serial.print("Hot: ");
    Serial.println(valveHot);
   }
 }
  
   Serial.print("Current Temp:  ");
   Serial.print(Temp);
   Serial.print(",  Target:  ");
   Serial.print(target);
   Serial.print(",  Differential:  ");
   Serial.println(target-Temp);
   
   
   int switchState=analogRead(onSwitch);
   Serial.println(switchState);
   
   if(switchState > 1000){
     
     
     
   //keep 1 degree margin
   if(Temp > (target+1)){
    digitalWrite(6, LOW);
    digitalWrite(5, HIGH);
    delay(1);          
    digitalWrite(5, LOW); 
    delay(1);
    valveHot --;
      
    Serial.print ("Hot Valve Position:  ");
    Serial.println(valveHot);
    Serial.println("");
    }
    
    
    if(Temp < (target-1)){ 
    digitalWrite(4, LOW);
    digitalWrite(3, HIGH);
    delay(1);          
    digitalWrite(3, LOW); 
    delay(1);
    valveCold --;
    
    Serial.print ("Cold Valve Position:  ");
    Serial.println (valveCold);
    Serial.println("");
    }
  }
  
  
    if(switchState < 1000){
      //I have a feeling these while/for blocks are redundant but I'm not sure how to get around it or if it's a problem
      while(valveCold <35){
        for(valveCold<35; valveCold<35; valveCold++){
    digitalWrite(4, HIGH);
    digitalWrite(3, HIGH);
    delay(1);          
    digitalWrite(3, LOW); 
    delay(500);
    valveCold++;
    Serial.print("Cold: ");
    Serial.println(valveCold);
   }
  }
   while(valveHot < 35){
     for (valveHot <35; valveHot<35; valveHot++){
    digitalWrite(6, HIGH);
    digitalWrite(5, HIGH);
    delay(1);          
    digitalWrite(5, LOW); 
    delay(500);
    valveHot ++;
    Serial.print("Cold: ");
    Serial.println(valveHot);
   }
 }
 

}
lcd.clear();
lcd.setCursor(0, 0);
lcd.print("Current Temp:  ");
lcd.setCursor(0, 1);
lcd.print(Temp);
}
