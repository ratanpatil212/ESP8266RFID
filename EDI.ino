
#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
#include <SPI.h>
#include <MFRC522.h>
 
#define SS_PIN D4
#define RST_PIN D3
#define LED_G D1 //define green LED pin
#define LED_R D8 //define red LED
#define RELAY D0 //relay pin
#define BUZZER D8 //buzzer pin
#define ACCESS_DELAY 2000
#define DENIED_DELAY 1000
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.

// Set these to run example.
#define FIREBASE_HOST "rfid-doorlock-3bf96-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "d68n9YQ8AvuTFZWCG0TrtjESneMvZmqIAsDeBXJT"
#define WIFI_SSID "AthPat"
#define WIFI_PASSWORD "athpat45"

FirebaseData firebaseData;

void setup() {
  Serial.begin(9600);

  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  
  SPI.begin();          // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  pinMode(LED_G, OUTPUT);
  pinMode(LED_R, OUTPUT);
  pinMode(RELAY, OUTPUT);
  noTone(BUZZER);
  digitalWrite(RELAY, HIGH);
  Serial.println("Put your card to the reader...");
  Serial.println();

  
}

int n = 0;
int ACCESS_VAR = 0;

void loop() {

  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  
    if(Firebase.getString(firebaseData, "/tags/c_lvl_1")) { 
      if (firebaseData.stringData() == "allow") {

          if (content.substring(1) == "73 F4 25 15") //change here the UID of the card/cards that you want to give access
          {
            Serial.println("Authorized Entry!");
            Serial.println();
            digitalWrite(RELAY, LOW);
            digitalWrite(LED_G, HIGH);
            ACCESS_VAR = 1;
            delay(ACCESS_DELAY);
            digitalWrite(RELAY, HIGH);
            digitalWrite(LED_G, LOW);

                      
            //Code for unlocking
          }

          if (content.substring(1) == "63 9D C8 16") //change here the UID of the card/cards that you want to give access
          {
            Serial.println("Authorized Entry!");
            Serial.println();
            digitalWrite(RELAY, LOW);
            digitalWrite(LED_G, HIGH);
            ACCESS_VAR = 1;
            delay(ACCESS_DELAY);
            digitalWrite(RELAY, HIGH);
            digitalWrite(LED_G, LOW);

                      
            //Code for unlocking
          }

             
      } ;
    };
    
    if(Firebase.getString(firebaseData, "/tags/c_lvl_2")) { 
      if (firebaseData.stringData() == "allow") {
        
        if (content.substring(1) == "53 4E 3F 2F") //change here the UID of the card/cards that you want to give access
          {
            Serial.println("Authorized Entry!");
            Serial.println();
            digitalWrite(RELAY, LOW);
            digitalWrite(LED_G, HIGH);
            ACCESS_VAR = 1;
            delay(ACCESS_DELAY);
            digitalWrite(RELAY, HIGH);
            digitalWrite(LED_G, LOW);

                      
            //Code for unlocking
          }

          if (content.substring(1) == "D3 BC 17 15") //change here the UID of the card/cards that you want to give access
          {
            Serial.println("Authorized Entry!");
            Serial.println();
            digitalWrite(RELAY, LOW);
            digitalWrite(LED_G, HIGH);
            ACCESS_VAR = 1;
            delay(ACCESS_DELAY);
            digitalWrite(RELAY, HIGH);
            digitalWrite(LED_G, LOW);

                      
            //Code for unlocking
          } 
        
       
            
      } 
    };

    if(Firebase.getString(firebaseData, "/tags/c_lvl_3")) {
      if (firebaseData.stringData() == "allow") {
        if (content.substring(1) == "43 44 65 2F") //change here the UID of the card/cards that you want to give access
          {
            Serial.println("Authorized Entry!");
            Serial.println();
            digitalWrite(RELAY, LOW);
            digitalWrite(LED_G, HIGH);
            ACCESS_VAR = 1;
            delay(ACCESS_DELAY);
            digitalWrite(RELAY, HIGH);
            digitalWrite(LED_G, LOW);

                      
            //Code for unlocking
          }
    }
        
        
    };
            
    if(Firebase.getString(firebaseData, "/tags/c_lvl_4")) { 
      if (firebaseData.stringData() == "allow") {
        
        if (content.substring(1) == "C0 F1 2E 1A") //change here the UID of the card/cards that you want to give access
          {
            Serial.println("Authorized Entry!");
            Serial.println();
            digitalWrite(RELAY, LOW);
            digitalWrite(LED_G, HIGH);
            ACCESS_VAR = 1;
            delay(ACCESS_DELAY);
            digitalWrite(RELAY, HIGH);
            digitalWrite(LED_G, LOW);

                      
            //Code for unlocking
          }
                
          
      
      } 
    };

    if(Firebase.getString(firebaseData, "/tags/c_lvl_5")) { 
      if (firebaseData.stringData() == "allow") {
        
        if (content.substring(1) == "51 56 88 1B") //change here the UID of the card/cards that you want to give access
          {
            Serial.println("Authorized Entry!");
            Serial.println();
            digitalWrite(RELAY, LOW);
            digitalWrite(LED_G, HIGH);
            ACCESS_VAR = 1;
            delay(ACCESS_DELAY);
            digitalWrite(RELAY, HIGH);
            digitalWrite(LED_G, LOW);
            

                      
            //Code for unlocking
          }

            
        
      }
    };

    if (ACCESS_VAR == 0) {
      digitalWrite(LED_R, HIGH);
      delay(DENIED_DELAY);
      digitalWrite(LED_R, LOW);
      Serial.println("Unauthorized Entry!");
    }
    
      ACCESS_VAR = 0;
}
