/*
QUERY FRAME:

| Transaction Identifier | Protocol Identifier | Length | Unit Identifier | Function Code | Starting Address | Quantity of Registers |
|------------------------|---------------------|--------|-----------------|---------------|------------------|-----------------------|
|       2 bytes          |      2 bytes        |2 bytes |      1 byte     |     1 byte    |     2 bytes      |       2 bytes         |

RESPONSE FRAME:

| Transaction Identifier | Protocol Identifier | Length | Unit Identifier | Function Code + 0x80 | Exceptional Code    |
|------------------------|---------------------|--------|-----------------|----------------------|---------------------|
|       2 bytes          |      2 bytes        |2 bytes |      1 byte     |     1 byte           |   1 byte            |

FUNCTION CODE ERROR:(0X01)
 * INPUT FRAME  = {0x00, 0x01, 0x00, 0x03, 0x00, 0x05, 0x03, 0x09, 0x00, 0x6, 0x00, 0x03} - 12 bytes
 * Here the function code is invalid (0x09)
 * RESPONSE FRAME = {0x0, 0x1, 0x0, 0x3, 0x0, 0x3, 0x03, 0x89, 0x01} - 9 bytes

ADDRESS ERROR:(0X02)
 * INPUT FRAME  = {0x00, 0x01, 0x00, 0x03, 0x00, 0x05, 0x03, 0x03, 0x00, 0x8D, 0x00, 0x03} - 12 bytes
 * Here the Start Address is invalid (0x008D).Address size should not exceed DataRegistersize. DataRegistersize is defined as 0x7D.
 * RESPONSE FRAME = {0x0, 0x1, 0x0, 0x3, 0x0, 0x3, 0x03, 0x83, 0x02} - 9 bytes

DATA ERROR:(0X03) -- for Function code - 0x06 and 0x10:
 * INPUT FRAME  = {0x00, 0x01, 0x00, 0x03, 0x00, 0x06, 0x03, 0x06, 0x00, 0x05, 0xFF, 0x09} - 12 bytes
 * Here the Data to be enter is invalid (0xFF09).Address size should not 65000(0xFDE8).
 * RESPONSE FRAME = {0x0, 0x1, 0x0, 0x3, 0x0, 0x3, 0x03, 0x86, 0x03} - 9 bytes
 */

#include "modbusTcp.h"

void modbusError(mbPacketParse_t *p_parseModbusTcpData, uint8_t *p_modbusTxBuf, uint8_t exceptioncode) {

    /* Assigning values for transmitting buffer*/
    p_modbusTxBuf[0] = p_parseModbusTcpData->transactionID.v[1];
    p_modbusTxBuf[1] = p_parseModbusTcpData->transactionID.v[0];
    p_modbusTxBuf[2] = p_parseModbusTcpData->protocolID.v[1];
    p_modbusTxBuf[3] = p_parseModbusTcpData->protocolID.v[0];
    p_modbusTxBuf[4] = 0X00;
    p_modbusTxBuf[5] = 0X03; /* length - no. of bytes contained in the data plus function code and Unit identifier */
    p_modbusTxBuf[6] = p_parseModbusTcpData->unitID;
    p_modbusTxBuf[7] = p_parseModbusTcpData->functionCode;
    p_modbusTxBuf[8] = exceptioncode;
}
