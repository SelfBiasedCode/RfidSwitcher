#include <SPI.h>
#include "RfidSwitcher.h"

// dynamically get the size of an array at low performance cost
#define ARRAY_SIZE(array) (*(&array + 1) - array)

/* SPI Setup */
#define SS_PIN 10
#define RST_PIN 9

/* RFID Switcher Config*/
#define TAG_READ_WAIT_MS 1000
const uint8_t uid_tag1[] = {0x9A, 0xF2, 0xB8, 0x80};
const uint8_t uid_tag2[] = {0x6A, 0xB5, 0x9F, 0x7F};
const uint8_t uid_tag1_spare[] = {0x8A, 0x17, 0xBB, 0x80};
const uint8_t uid_tag2_spare[] = {0xBA, 0xFB, 0xFF, 0x85};

// instantiate RfidSwitcher
RfidSwitcher rfid;

void rfidSetup()
{
  /* Tag List Construction */
  RfidTaginfo tags[] =
  {
    // Main Tags
    RfidTaginfo(uid_tag1, &func_tag1),
    RfidTaginfo(uid_tag2, &func_tag2),

    // Spare Tags
    RfidTaginfo(uid_tag1_spare, &func_tag1),
    RfidTaginfo(uid_tag2_spare, &func_tag2)
  };
 
  /* Switcher initialization & tag registration */
  SPI.begin();
  rfid.init(SS_PIN, RST_PIN);
  rfid.registerTags(tags, ARRAY_SIZE(tags));
}

void setup()
{
  // initiate communication with PC host
  Serial.begin(9600);
  
  rfidSetup();
}

void loop()
{
  int8_t rfidState = rfid.poll();

  switch (rfidState)
  {
    case RfidSwitcher::NO_TAG_FOUND:
      // no tag found: do nothing
      break;

    case RfidSwitcher::NO_MATCH_FOUND:
      // no match: show error
      Serial.println("Unknown Tag!");
      delay(TAG_READ_WAIT_MS);
      break;

    default:
      Serial.print("Read Tag: ");
      Serial.println(rfidState);
      delay(TAG_READ_WAIT_MS);
      break;
  }
}

void func_tag1()
{
  Serial.println("Tag 1");
}

void func_tag1()
{
  Serial.println("Tag 2");
}
