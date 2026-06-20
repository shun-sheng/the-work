#ifndef __CAN_SPI_H
#define	__CAN_SPI_H

#include "MY_Define.h"

uint8_t CANSPI_Initialize(SPI_HandleTypeDef *hspi);
void CANSPI_Sleep(SPI_HandleTypeDef *hspi);
uint8_t CANSPI_Transmit(SPI_HandleTypeDef *hspi, uCAN_MSG *tempCanMsg);
uint8_t CANSPI_Receive(SPI_HandleTypeDef *hspi, uCAN_MSG *tempCanMsg);
void WHW_MCP2515_IRQHandler(SPI_HandleTypeDef *hspi);
uint8_t WHW_CANSPI_Receive(SPI_HandleTypeDef *hspi, uCAN_MSG *tempCanMsg);
uint8_t CANSPI_messagesInBuffer(SPI_HandleTypeDef *hspi);
uint8_t CANSPI_isBussOff(SPI_HandleTypeDef *hspi);
uint8_t CANSPI_isRxErrorPassive(SPI_HandleTypeDef *hspi);
uint8_t CANSPI_isTxErrorPassive(SPI_HandleTypeDef *hspi);
void CANSPI_SEND(SPI_HandleTypeDef *hspi, int16_t stdid, uint8_t *data);

#endif	/* __CAN_SPI_H */
