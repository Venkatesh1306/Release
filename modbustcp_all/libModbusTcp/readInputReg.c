/*
QUERY FRAME:

| Transaction Identifier | Protocol Identifier | Length | Unit Identifier | Function Code | Starting Address | Quantity of Registers |
|------------------------|---------------------|--------|-----------------|---------------|------------------|-----------------------|
|       2 bytes          |      2 bytes        |2 bytes |      1 byte     |     1 byte    |     2 bytes      |       2 bytes         |

RESPONSE FRAME:

| Transaction Identifier | Protocol Identifier | Length | Unit Identifier | Function Code | Byte Count | Data                |
|------------------------|---------------------|--------|-----------------|---------------|------------|---------------------|
|       2 bytes          |      2 bytes        |2 bytes |      1 byte     |     1 byte    |   1 byte   | Variable (n bytes)  |

 * INPUT FRAME  = {0x00, 0x01, 0x00, 0x03, 0x00, 0x05, 0x10, 0x04, 0x00, 0x06, 0x00, 0x03} - 12 bytes
 * DATAREGISTER = {0x0000, 0x0001, 0x0002, 0x0003, 0x0004, 0x0005, 0x0006, 0x0007, 0x0008, 0x0009, 0x0009, 0x0008, 0x0007, 0x0007, 0x0006, 0x0005, 0x0004, 0x0003, 0x0002, 0x0001, 0x0025, 0x0035, 0x0036, 0x9957, 0x7890}

 * The Query Message specifies the starting register and Quantity of registers to be read
 * This Query Request to read 3 register values from starting address 0x06 (0x06, 0x07, 0x08)
 * RESPONSE FRAME = {0x00, 0x01, 0x00, 0x03, 0x00, 0x09, 0x10, 0x04, 0x06, 0x00, 0x06, 0x00, 0x07, 0x00, 0x08} - 15 bytes(9 bytes + (2* no of Registers))
 *
 * when error detected :
 * RESPONSE FRAME = {0x00, 0x01, 0x02, 0x03, 0x00, 0x03, 0x10, 0x91, 0x01} - 9 bytes
 */

#include "ModbusTcp.h"

uint16_t readInputReg(uint8_t *p_modbusTxBuf, uint16_t *p_dataMemory, mbPacketParse_t *p_parseModbusTcpData)
{
    /* Declaration of local variable */
    unsigned int bytes = 0;
    unsigned int a = 0, b = 0;

    /* Assigning values for transmitting buffer*/
    p_modbusTxBuf[0] = p_parseModbusTcpData->transactionID.v[1];
    p_modbusTxBuf[1] = p_parseModbusTcpData->transactionID.v[0];

    p_modbusTxBuf[2] = p_parseModbusTcpData->protocolID.v[1];
    p_modbusTxBuf[3] = p_parseModbusTcpData->protocolID.v[0];

    p_modbusTxBuf[4] = 0X0;

    p_modbusTxBuf[6] = p_parseModbusTcpData->unitID;
    p_modbusTxBuf[7] = p_parseModbusTcpData->functionCode;
    p_modbusTxBuf[8] = (char)(p_parseModbusTcpData->numberofRegister.Val * 2);
    p_modbusTxBuf[5] = p_modbusTxBuf[8] + 0X03; /* length */

    for (a = 0; a < p_parseModbusTcpData->numberofRegister.Val; a++)
    {
        b = a * 2;

        p_modbusTxBuf[9 + b] = p_dataMemory[p_parseModbusTcpData->startAddress.Val + a] / 0x100;
        p_modbusTxBuf[10 + b] = p_dataMemory[p_parseModbusTcpData->startAddress.Val + a] % 0x100;
    }

    bytes = 0x9 + p_modbusTxBuf[8];
    return bytes;
}
