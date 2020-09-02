#ifndef RFID_TAGINFO_H
#define RFID_STAGINFO_H

#include <stdint.h>
struct RfidTaginfo
{
  RfidTaginfo(){}
  RfidTaginfo(uint8_t * uidArray, void (*callback)(void)):uid(uidArray), callback(callback){}
  
  uint8_t * uid;
  void (*callback)(void);
};


#endif
