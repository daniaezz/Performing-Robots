/*
   Example using the nRF24L01 radio module to communicate
   between two Arduinos,
   the transmitter is connected to two momentary switches
   the receiver is connected to two LEDs

   Both sketches are present in this file; first the transmitter
   The receiver is included as a comment below

   These sketches require the RF24 library by TMRH20
*/


// Transmitter

// Pin usage
//
// The switches are on pins 2 and 4:
const int SWITCH1PIN = 2;
const int SWITCH2PIN = 4;
int pot_pin = 0;

// nRF24L01 uses SPI which is fixed on pins 11, 12, and 13.
// It also requires two other signals
// (CE = Chip Enable, CSN = Chip Select Not)
// Which can be any pins:

const int CEPIN = 9;
const int CSNPIN = 10;

int dataArr[3];
int POTval; 
int data;

// In summary,
// nRF 24L01 pin    Arduino pin   name
//          1                     GND
//          2                     3.3V
//          3             9       CE
//          4             10      CSN
//          5             13      SCLK
//          6             11      MOSI/COPI
//          7             12      MISO/CIPO

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(CEPIN, CSNPIN);                // CE, CSN

// Byte of array representing the address.
// This is the address where we will send the data.
// This should be same on the receiving side.
const byte address[6] = "00500";

//struct Data_Package{
//  byte a = 
//}

void setup() {
  Serial.begin(9600);

  pinMode(SWITCH1PIN, INPUT);
  pinMode(SWITCH2PIN, INPUT);

  // RF24 setup
  if (!radio.begin()) {
    Serial.println("radio  initialization failed");
    while (1)
      ;
  } else {
    Serial.println("radio successfully initialized");
  }
  radio.openWritingPipe(address);  //destination address
  radio.setPALevel(RF24_PA_MIN);   // min or max
  radio.stopListening();           //This sets the module as transmitter
}
void loop() {
  POTval = map(analogRead(A0), 0, 1023, 0, 180);
  int left = B00000000;
  if (digitalRead(SWITCH1PIN) == HIGH) {
    left = B00000001;
    dataArr[0] = 1;
  }else{
    dataArr[0] = 0;
  }
  int right = B00000000;
  if (digitalRead(SWITCH2PIN) == HIGH) {
    right = B00000010;
    dataArr[1] = 1;
  } else{
    dataArr[1] = 0;
  }
  
  if (POTval >=2){
    dataArr[2] = POTval;
  }else{
    dataArr[2] = 0;
  }

//  int pot = 0;
//  int val = 0;
//  if((val = analogRead(pot_pin))){
//    pot = val;
//    pot *= 10;
//  }



//  dataArr ;
  if (dataArr) {
//    Serial.println("works");
//    Serial.println(data)
    Serial.print( "sending data = " );
    for (int i = 0; i<3; i++){
    Serial.println(dataArr[i]);
    }
    radio.write(&dataArr, sizeof(dataArr)) ;
  }
}




/* Receiver

// Pin usage
  //
  #include <Servo.h> 

  // The LEDs are on pins 2 and 4:
  const int LED1PIN = 2;
  const int LED2PIN = 4;
  int servoPin = 3; 
  Servo Servo1; 

 // int data[3];
  // nRF24L01 uses SPI which is fixed on pins 11, 12, and 13.
  // It also requires two other signals
  // (CE = Chip Enable, CSN = Chip Select Not)
  // Which can be any pins:
  const int CEPIN = 9;
  const int CSNPIN = 10;
  // In summary,
  // nRF 24L01 pin    Arduino pin   name
  //          1                     GND
  //          2                     3.3V
  //          3             9       CE
  //          4             10      CSN
  //          5             13      SCLK
  //          6             11      MOSI/COPI
  //          7             12      MISO/CIPO
  #include <SPI.h>
  #include <nRF24L01.h>
  #include <RF24.h>
  RF24 radio(CEPIN, CSNPIN);                // CE, CSN
  // Byte of array representing the address.
  // This is the address where we will send the data.
  // This should be same on the receiving side.
  const byte address[6] = "00500";
  void setup() {
    Servo1.attach(servoPin);
  Serial.begin(9600);
  pinMode(LED1PIN, OUTPUT);
  pinMode(LED2PIN, OUTPUT);
  // RF24 setup
  if (!radio.begin()) {
    Serial.println("radio  initialization failed");
    while (1)
      ;
  } else {
    Serial.println("radio successfully initialized");
  }
  radio.openReadingPipe(0,address);  //destination addres
  radio.setPALevel(RF24_PA_MIN);   // min or max
  radio.startListening();           //This sets the module as transmitter
  }
  void loop() {
  uint8_t pipeNum;
  if (radio.available(&pipeNum))  //Looking for the data.
  {
    int data[3];
    //Serial.print("data available on pipe ");
    //Serial.println(pipeNum);
    radio.read(&data, sizeof(data));  //Reading the data
    Serial.print("data = ");
    Servo1.write(data[2]); 


for (int i=0; i<3; i++){
      Serial.println( data[i]);
}
 if (data[0] == 1){
  digitalWrite(LED1PIN, HIGH);
 }else {
  digitalWrite(LED1PIN, LOW);
 }

 if (data[1] == 1){
  digitalWrite(LED2PIN, HIGH);
 }else {
  digitalWrite(LED2PIN, LOW);
 }
  }


  }

*/
