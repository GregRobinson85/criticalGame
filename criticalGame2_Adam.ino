#define startSwitch A0
#define alarm 8

unsigned long startTime, buttonEvent1, buttonEvent2, playerOne, playerTwo, pwr, gameStartedTime;
int switchState = 0;
int startInterval = 0;
int press1 = 0;
int press2 = 0;
int dis1 = 0;
int dis2 = 0;
int disQ = 0;
int score1 =0;
int score2 =0;
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
  
  int gameStarted = 0;
  press1=  0;
  press2 = 0;

  digitalWrite(8,0);
  lcd.clear();
  lcd.noDisplay(); 
  switchState = analogRead(startSwitch);

  Serial.print("magnet: ");
  Serial.println(switchState);

  // run the program
  if (switchState > 17) {
    
    startTime = millis();
    startInterval = random(1000, 7000);

    Serial.print("timeToStart: ");
    Serial.println(startInterval);
   

    lcd.display();
    lcd.print("Get Ready!");
    lcd.print("");

    // Game is ready, loop until some player presses a button
    while (press1 < 1001 && press2 < 1001) {
      
    pwr = millis();
    
      // When the start interval is up, say GO!
      if (pwr-startTime >= startInterval && gameStarted == 0) {
        Serial.print("startTime: ");
        Serial.println(pwr-startTime);
        lcd.clear();
        lcd.print("Go!");
        digitalWrite(8,1);
        gameStarted = 1;
        gameStartedTime = millis();
       
      }

      // Read to see if either player pressed a button
      press1 = analogRead(A1);
      press2 = analogRead(A2);
   
      Serial.print(press1);
      Serial.print(": ");
      Serial.println(press2);
      
      if (press1 > 1000) {
        // player 1 pressed the button before the interval elapsed - CHEATER
        if (gameStarted == 0) {
          lcd.clear();
          lcd.print("Player 1 Cheated!");
          
          lcd.setCursor(0,1);
          
          score1--;
          
          lcd.print("score: ");
          lcd.print(score1);
          lcd.print(" to ");
          lcd.print(score2);
          delay(2000);
          lcd.clear();
        }
        else {
          // print player 1 wins and beep/light
          buttonEvent1 = millis();
          playerOne = (buttonEvent1 - gameStartedTime);
          Serial.println("player1 wins");
          lcd.clear();
          digitalWrite(8,0);
          lcd.setCursor(1,0);
          lcd.print("Player 1 wins!");
          lcd.setCursor(0,1);
          
          score1++;
          
          lcd.print("score: ");
          lcd.print(score1);
          lcd.print(" to ");
          lcd.print(score2);
          delay(2000);
          lcd.clear();
          lcd.setCursor(6,0);
          lcd.print(playerOne);
          lcd.setCursor(2,1);
          lcd.print("Milliseconds");
          
          
          Serial.print("score1: ");
          Serial.println(score1);
          delay(2000);
        }
      }

      if (press2 > 1000) {
        // player 2 pressed the button before the interval elapsed - CHEATER
        if (gameStarted == 0) {
          lcd.clear();
          lcd.print("Player 2 Cheated");
          lcd.setCursor(0,1);
          
          score2--;
          
          lcd.print("score: ");
          lcd.print(score1);
          lcd.print(" to ");
          lcd.print(score2);
          delay(2000);
          lcd.clear();
        }
        else {
          // print player2 wins and beep/light  
          buttonEvent2 = millis();
          playerTwo = (buttonEvent2 - gameStartedTime);
          Serial.println("player2 wins");
          lcd.clear();
          digitalWrite(8,0);
          lcd.setCursor(1,0);
          lcd.print("Player 2 wins!");
          lcd.setCursor(0,1);
          
          score2++;
          
          lcd.print("score: ");
          lcd.print(score1);
          lcd.print(" to ");
          lcd.print(score2);
          delay(2000);
          lcd.clear();
          lcd.setCursor(6,0);
          lcd.print(playerTwo);
          lcd.setCursor(2,1);
          lcd.print("Milliseconds");
          

         
         
          Serial.print("score2: ");
          Serial.println(score2);
          delay(2000);
        }
      }
    }

  }
  // If game not started yet, loop again, at 40hz
  else {
    delay(25);
  }
}
