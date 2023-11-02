#include <IRremote.hpp>

#define RECEIVER 2
#define pinLED1 4
#define pinLED2 5
#define pinLED3 6
#define pinLED4 7

bool LED1, LED2, LED3, LED4 = false;

void setup() {
  pinMode(pinLED1, OUTPUT);
  pinMode(pinLED2, OUTPUT);
  pinMode(pinLED3, OUTPUT);
  pinMode(pinLED4, OUTPUT);

  IrReceiver.begin(RECEIVER, ENABLE_LED_FEEDBACK);
  Serial.begin(9600);
}

void loop() {
  if (IrReceiver.decode()) {
   	IrReceiver.printIRResultShort(&Serial);
    IrReceiver.printIRSendUsage(&Serial);
    
    if (IrReceiver.decodedIRData.protocol == UNKNOWN) {
      Serial.println(F("Received noise or an unknown (or not yet enabled) protocol"));
      IrReceiver.printIRResultRawFormatted(&Serial, true);
    }

    Serial.println();
    IrReceiver.resume();

    if (IrReceiver.decodedIRData.command == 0x45){
      LED1 = !LED1;
      digitalWrite(pinLED1, LED1);
      delay(50);
    }
    if (IrReceiver.decodedIRData.command == 0x46){
      LED2 = !LED2;
      digitalWrite(pinLED2, LED2);
      delay(50);
    }
    if (IrReceiver.decodedIRData.command == 0x47){
      LED3 = !LED3;
      digitalWrite(pinLED3, LED3);
      delay(50);
    }
    if (IrReceiver.decodedIRData.command == 0x44){
      LED4 = !LED4;
      digitalWrite(pinLED4, LED4);
      delay(50);
    }
    if (IrReceiver.decodedIRData.command == 0x40){
      digitalWrite(pinLED1, LOW);
      digitalWrite(pinLED2, LOW);
      digitalWrite(pinLED3, LOW);
      digitalWrite(pinLED4, LOW);
      LED1, LED2, LED3, LED4 = false;
    }
  }

  delay(100);
}