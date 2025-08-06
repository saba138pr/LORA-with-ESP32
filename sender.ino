#include <SPI.h>
#include <LoRa.h>
#include "esp_timer.h"

#define SS    5
#define RST   14
#define DIO0  2

volatile bool sendFlag = false;


void IRAM_ATTR onTimerCallback(void* arg) {
  sendFlag = true;
}

esp_timer_handle_t periodic_timer;

void setup() {
  Serial.begin(115200);
  LoRa.setPins(SS, RST, DIO0);

  if (!LoRa.begin(433E6)) {
    Serial.println("LoRa init failed!");
    while (1);
  }

  LoRa.setSyncWord(0x34);
  Serial.println("LoRa Sender Ready (1s using esp_timer)");


  const esp_timer_create_args_t periodic_timer_args = {
    .callback = &onTimerCallback,
    .arg = nullptr,
    .dispatch_method = ESP_TIMER_TASK,
    .name = "my_periodic_timer"
  };

  esp_timer_create(&periodic_timer_args, &periodic_timer);
  esp_timer_start_periodic(periodic_timer, 1000000); //1s
}

void loop() {
  if (sendFlag) {
    sendFlag = false;

    String msg = "Hello from sender";
    LoRa.beginPacket();
    LoRa.print(msg);
    LoRa.endPacket();

    Serial.print("Sent message: ");
    Serial.println(msg);
  }

//check for reicive
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    String reply = LoRa.readString();
    Serial.print("Received reply: ");
    Serial.println(reply);
  }
}
