
#include <BleKeyboard.h>

BleKeyboard bleKeyboard;
int btn = 25;
int countDwn = 0; 
int origCountDown = 0; 
bool btnState = 0; 
bool btnStateStop = 0; 
bool stopFlag = HIGH; 
bool manStop = LOW; 


void setup() {
  bleKeyboard.begin();
  pinMode(btn, INPUT);
  Serial.begin(9600);
}

void loop() {

  while(stopFlag == HIGH){
    //wait in a fast loop for button pressed
    if(digitalRead(btn) == HIGH){
    btnState = digitalRead(btn); 
    Serial.println("Caught"); 
    break; 
    }
  }
  

    if (btnState == HIGH){
      //set countdown to random value
      countDwn = 100*random(5, 20);
      origCountDown = countDwn; 
      Serial.println("Time to DANCE for " + String(countDwn/100) + " seconds!");
      
      //start the music
      bleKeyboard.write(KEY_MEDIA_PLAY_PAUSE);
      //Allow run
      stopFlag = LOW;
      //Reset "button pressed" 
      btnState = LOW;
      
    }

    //Timer stop
    if (countDwn <= 0 && stopFlag == LOW){
      //stop the music
      Serial.println("Time to Stop!");
      bleKeyboard.write(KEY_MEDIA_PLAY_PAUSE); 
      stopFlag = HIGH; 
      manStop = LOW;
      delay(500);
    }

    //Manual stop
    if (manStop == HIGH){
      //stop the music
      Serial.println("Manual Stop!");
      bleKeyboard.write(KEY_MEDIA_PLAY_PAUSE); 
      stopFlag = HIGH; 
      manStop = LOW;
      delay(500); 
    }


      //decrease counter
      countDwn--;
      //Serial.println(countDwn);
      //sleep 10 ms
      delay(10);
      //check for manual stop
      
      btnStateStop = digitalRead(btn);
      //Serial.println(origCountDown);
      //Serial.println(countDwn);
      if (btnStateStop == HIGH) {
        if (origCountDown - countDwn > 100){ 
          //Serial.println(origCountDown - countDwn);
          //disallow if less than a second has passed since start        
          manStop = HIGH;
          btnStateStop = LOW; 
        }
      btnStateStop = LOW; 
      }
      
      
      
} 
