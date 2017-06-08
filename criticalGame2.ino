unsigned long startTime, buttonEvent1, buttonEvent2, playerOne, playerTwo;
int startInterval = 0;
#define startSwitch  A0
int switchState=0;
#define player1 9
#define player2 10
#define alarm 8
unsigned long startNow =0;
int press1 = 0;
int press2 =0;
int dis1 = 0;
int dis2 = 0;
int disQ = 0;
int cheater1=0;
int cheater2=0;
int progTop =1;
#include <LiquidCrystal.h> 
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);


void setup() {
   lcd.begin(16, 2);
  pinMode (2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode (8, OUTPUT);
  pinMode (9,INPUT);
  pinMode (10, INPUT);
  Serial.begin(9600);
  Serial.println("criticalGame2");
  
}



void loop() {
  
  digitalWrite(8,0);
lcd.clear();
lcd.noDisplay(); 
switchState=analogRead(startSwitch);
startInterval  = random(1000,7000);
Serial.println("magnet says: ");
Serial.println(switchState);
  if (switchState > 0) {//run the program//
  
    Serial.println("timeToStart: ");
    Serial.println(" ");
    Serial.println(startInterval);
    disQ = millis();
    lcd.display();
    lcd.print("Get Ready!");
    lcd.print("");
   /*while (disQ < startInterval){
    dis1 = analogRead(A1);
    dis2 = analogRead(A2);
    if (dis1>1000){
      lcd.clear();
      lcd.print("Player 1");
     lcd.setCursor(0,1);
    lcd.print("Disqualifed!");
      delay(2000);
      lcd.clear();
   }
   }*/
    
    delay(startInterval);
    startTime = millis();
    lcd.clear();
    lcd.print("Go!");
    digitalWrite(8,1);
    check:
    press1 = analogRead(A1);
    press2 = analogRead(A2);
 
    Serial.print(press1);
    Serial.print(": ");
    Serial.println(press2);
    
if(press1 > 1000){
  buttonEvent1 = millis();
  playerOne = (buttonEvent1 - startTime);
Serial.println("player1 wins");
  lcd.clear();
  digitalWrite(8,0);
lcd.setCursor(1,0);
lcd.print("Player 1 wins!");
delay(2000);
lcd.clear();
lcd.setCursor(6,0);
lcd.print(playerOne);
lcd.setCursor(2,1);
lcd.print("Milliseconds");
delay(5000);
  //print player 1 wins and beep/light
}

if(press2 > 1000){
  buttonEvent2 = millis();
  playerTwo = (buttonEvent2 - startTime);
  Serial.println("player2 wins");
  lcd.clear();
  digitalWrite(8,0);
  lcd.setCursor(1,0);
  lcd.print("Player 2 wins!");
  delay(2000);
  lcd.clear();
  lcd.setCursor(6,0);
  lcd.print(playerTwo);
  lcd.setCursor(2,1);
  lcd.print("Milliseconds");
  delay(5000);
  //print player2 wins and beep/light//
  
}
if (press1 < 1001 && press2 < 1001){ goto check;}

}


 
  
    
    

  if (switchState <1){

    
  
  delay(25);
}

 }
 
