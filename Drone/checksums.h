#ifndef CHECKSUM_DOT_H
#define CHECKSUM_DOT_H
#include <stdint.h>

uint8_t CRC8_Table_Get(uint8_t *buffer, int32_t offset, int32_t len);
void calChecksum(void);
void Umbus_PackToSend(uint8_t msgID,  uint8_t* p_data, uint8_t DataNum, uint8_t  dest,  uint8_t src);
void taskOffLed();

#endif