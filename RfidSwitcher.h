#ifndef RFID_SWITCHER_H
#define RFID_SWITCHER_H

#include "RfidTaginfo.h"
#include <MFRC522.h>

class RfidSwitcher
{
  public:
  RfidSwitcher():m_tags(NULL), m_numTags(0){}
  
  void init(uint8_t spi_ss_pin, uint8_t spi_rst_pin);
  int8_t poll();
  void registerTags(RfidTaginfo * tagList, uint8_t numTags);

  /* return values for poll() */
  static const int8_t NO_TAG_FOUND = -1;
  static const int8_t NO_MATCH_FOUND = -2;
  
  private:
  RfidTaginfo * m_tags;
  uint8_t m_numTags;
  MFRC522 m_controller;
	
};

#endif
