#include <SPI.h>
#include <LoRa.h>

#define SS    5
#define RST   14
#define DIO0  2
#define LED_PIN  22  

volatile bool packetReceived = false;

void IRAM_ATTR onReceiveInterrupt() {
  packetReceived = true;
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);

  LoRa.setPins(SS, RST, DIO0);
  if (!LoRa.begin(433E6)) {
    Serial.println("LoRa init failed!");
    while (1);
  }
  LoRa.setSyncWord(0x34);

  pinMode(DIO0, INPUT);
  attachInterrupt(digitalPinToInterrupt(DIO0), onReceiveInterrupt, RISING);

  LoRa.receive();  // receiving...

  Serial.println("LoRa Receiver Ready (Can Send Anytime)");
}

void loop() {
  if (packetReceived) {
    packetReceived = false;

    int packetSize = LoRa.parsePacket();
    if (packetSize) {
      String msg = LoRa.readString();
      Serial.print("Received message: ");
      Serial.println(msg);

   
      LoRa.idle(); // exit from reciver
      String reply = "ACK: Got your message -> " + msg;
      LoRa.beginPacket();
      LoRa.print(reply);
      LoRa.endPacket();
      Serial.print("Sent response: ");
     // Serial.println(reply);

      LoRa.receive(); //return to reciever
    }
  }


}
