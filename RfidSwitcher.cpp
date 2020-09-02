#include "RfidSwitcher.h"

void RfidSwitcher::init(uint8_t spi_ss_pin, uint8_t spi_rst_pin)
{
  m_controller = MFRC522(spi_ss_pin, spi_rst_pin);
  m_controller.PCD_Init();
}

void RfidSwitcher::registerTags(RfidTaginfo * tagList, uint8_t numTags)
{
  m_tags = tagList;
  m_numTags = numTags;
}

int8_t RfidSwitcher::poll()
{
	// only continue if a card is present and the UID has been read successfully
	if ( ! (m_controller.PICC_IsNewCardPresent() && m_controller.PICC_ReadCardSerial() )) 
	  { 
		return NO_TAG_FOUND;
	  }
  
	// invoke linear seach through list of known tags to find a match
	for (uint8_t currTagId = 0; currTagId < m_numTags; currTagId++)
	{
	  RfidTaginfo currTag = m_tags[currTagId];
	  
	  bool equal = true;
	  
	  // compare read uid to stored uid
	  for (uint8_t i = 0; i < m_controller.uid.size; i++) 
	  {
		 equal &= m_controller.uid.uidByte[i] == currTag.uid[i];
	  }
	  
	  // check if UID has matched
	  if (equal)
	  {
		  // call callback and return tag index
		  currTag.callback();
		  return currTagId;
	  }
	  else
	  {
		  // check next tag
		  continue;
	  }
	  
	}
	
	// if we are here, no matches were found
	return NO_MATCH_FOUND;
}
