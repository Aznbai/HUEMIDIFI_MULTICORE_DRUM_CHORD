#include "Arduino.h"
#include "AiEsp32RotaryEncoder.h"
#include <TFT_eSPI.h> // Graphics and font library for ST7789 driver chip
#include <SPI.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "SPIFFS.h"
#include <ESPmDNS.h>

// own modules
#include "droneDEFINITIONS.h"
#include "droneTFT.h"
#include "droneMIDI.h"

#include "droneENCODER.h"
#include "droneWIFI.h"
#include "droneSERVER_RESPONSE.h"
#include "droneSERVER.h"
#include "droneSPIFFS.h"

/*
   This sketch can be used as a template to create your own dual core application.
   You can either pot code in codeForTask1, codeForTask2, or loop. Make sure, you
   place a delay(1000) in all unused tasks

*/
long loops1 = 800;
long loops2 = 800;
long qq;
float t1;
int t2, t3;
TaskHandle_t Task1, Task2;
SemaphoreHandle_t baton;
void artificialLoad()
{
  for (long i = 0; i < loops1; i++)
  {
    for (long j = 1; j < loops2; j++)
    {
      qq++;
      t1 = 5000.0 * i;
      t2 = 150 * 1234 * i;
      t3 = j % 554;
    }
  }
}

void codeForTask1(void *parameter)
{
  for (;;)
  {
    // Serial.print("KOKO CORE: ");
    // Serial.print(xPortGetCoreID());
    // Serial.print("\n");
    handlePPQNTiming();

    delay(1);
  }
}

void codeForTask2(void *parameter)
{
  for (;;)
  {
    // Serial.print(" MOKO  CORE: ");
    // Serial.print(xPortGetCoreID());
    // Serial.print("\n");
    handleEncoder();

    delay(1);
  }
}

// the setup function runs once when you press reset or power the board
void setup()
{
  setupSPIFFS();
  setupMIDI();
  setupTFT();
  setupEncoder();
  // pinMode(LED, OUTPUT);
  setupWIFI();
  setupServer();

  xTaskCreatePinnedToCore(
      codeForTask1,
      "led1Task",
      10000,
      NULL,
      1,
      &Task1,
      1);

  delay(500); // needed to start-up task1

  xTaskCreatePinnedToCore(
      codeForTask2,
      "led2Task",
      10000,
      NULL,
      1,
      &Task2,
      0);
}

void loop()
{
}