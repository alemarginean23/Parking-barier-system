
#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>

#define SS_PIN 10
#define RST_PIN 9
#define RED_LED_PIN 7
#define GREEN_LED_PIN 6
#define SERVO_PIN 5  // Replace with the actual pin for the servo
#define IR_RECEIVER_PIN A0  // Replace with the actual pin for the IR receiver


MFRC522 mfrc522(SS_PIN, RST_PIN);
Servo myServo;

const String authorizedUID = "63 7A 96 12";  // Replace with the UID of the authorized card

void setup() {
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  myServo.attach(SERVO_PIN);
  
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(IR_RECEIVER_PIN, INPUT);

  digitalWrite(RED_LED_PIN, HIGH);  // Red LED always on
  digitalWrite(GREEN_LED_PIN, LOW);  // Green LED initially off
  
  Serial.println("Approximate your card to the reader...");
  Serial.println();
}

int ifRead;

void loop() {
  
  myServo.write(145);//unghi inchis
  char inputMessage[5];
  
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    

  Serial.print("UID tag:");
  String content = "";

  for (byte i = 0; i < mfrc522.uid.size; i++) {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }

  Serial.println();
  Serial.print("Message: ");
  content.toUpperCase();

  if (content.substring(1) == authorizedUID) {
      Serial.println("Authorized access");
      digitalWrite(RED_LED_PIN, LOW);
      digitalWrite(GREEN_LED_PIN, HIGH);  // Turn on green LED
  
  
      myServo.write(95);
      
        ifRead = analogRead(A0);
          Serial.println(ifRead);
    int readings[20];
    for(int i=0; i<20;i++){
      readings[i]=0;
      
    }
    int index=0;
    
  
      while(true){
        
          ifRead = analogRead(A0);
          
          Serial.println(ifRead);
          
          delay(5);
          readings[(index++)%20]=ifRead;
          int counterOfZero=0;
          
          for(int i=0;i<20;i++){
            if(readings[i]<30){
              counterOfZero++;
            }
          }
          if(counterOfZero<5){
            break;
          }
      }
  
      index=0;
      
      
      delay(4000);
        myServo.write(145); // Move the servo back to the initial position (0 degrees)
  
      
      digitalWrite(GREEN_LED_PIN, LOW); // Turn off green LED
      digitalWrite(RED_LED_PIN, HIGH);
    } else {
      Serial.println("Access denied");
      digitalWrite(RED_LED_PIN, LOW);  // Turn off red LED
      delay(200);
      digitalWrite(RED_LED_PIN, HIGH);  // Blink red LED
      delay(200);
      digitalWrite(RED_LED_PIN, LOW);  // Turn off red LED
      delay(200);
      digitalWrite(RED_LED_PIN, HIGH);  // Blink red LED
      delay(200);
    }
  
    
  }


  int index2 = 0;
  int openGate=0;
  while(Serial.available()){
    char c = Serial.read();
    inputMessage[index2++] = c;
    if( strcmp(inputMessage, "open")==0){
      openGate = 1;
      break;
    }
  }
  

  if(openGate==1){
    Serial.println("Authorized access");
      digitalWrite(RED_LED_PIN, LOW);
      digitalWrite(GREEN_LED_PIN, HIGH);  // Turn on green LED
  
  
      myServo.write(95);
      
        ifRead = analogRead(A0);
          Serial.println(ifRead);
    int readings[20];
    for(int i=0; i<20;i++){
      readings[i]=0;
      
    }
    int index=0;
    
  
      while(true){
        
          ifRead = analogRead(A0);
          
          Serial.println(ifRead);
          
          delay(5);
          readings[(index++)%20]=ifRead;
          int counterOfZero=0;
          
          for(int i=0;i<20;i++){
            if(readings[i]<30){
              counterOfZero++;
            }
          }
          if(counterOfZero<5){
            break;
          }
      }
  
      index=0;
      
      
      delay(4000);
        myServo.write(145); // Move the servo back to the initial position (0 degrees)
  
      
      digitalWrite(GREEN_LED_PIN, LOW); // Turn off green LED
      digitalWrite(RED_LED_PIN, HIGH);
    }
  
  

  //Serial.println();
}
