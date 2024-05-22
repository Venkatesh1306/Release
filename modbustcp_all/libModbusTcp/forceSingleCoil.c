/* Force Single Coil - Function Code - 05
 *  The query message specifies the coil reference to be forced
 * A value of FF 00 hex requests the coil to be ON.
 * A value of 00 00 requests it to be OFF.
 *  All other values are illegal and will not affect the coil.
 *
 * QUERY FRAME:
| Transaction Identifier | Protocol Identifier | Length | Unit Identifier | Function Code | Coil Address |   Force Data Value     |
|------------------------|---------------------|--------|-----------------|---------------|--------------|------------------------|
|       2 bytes          |      2 bytes        |2 bytes |      1 byte     |     1 byte    |    2 bytes   |           2 bytes      |

RESPONSE FRAME:
| Transaction Identifier | Protocol Identifier | Length | Unit Identifier | Function Code | Coil Address |     Force Data Value   |
|------------------------|---------------------|--------|-----------------|---------------|--------------|------------------------|
|       2 bytes          |      2 bytes        |2 bytes |      1 byte     |     1 byte    |    2 bytes   |         2 bytes        |
 *
 * INPUT FRAME    = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x10, 0x05, 0x00, 0xAC, 0xFF, 0x00}
 * RESPONSE FRAME = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x10, 0x05, 0x00, 0xAC, 0xFF, 0x00}
 */

#include "ModbusTcp.h"

/* Macro definitions */
#define SET(x, y) x |= (1 << y)
#define READ(x, y) ((0u == (x & (1 << y))) ? 0u : 1u)
#define CLEAR(x, y) x &= ~(1 << y)

uint16_t forceSingleCoil(uint8_t *p_modbusTxBuf, uint16_t *p_dataMemory, mbPacketParse_t *p_parseModbusTcpData)
{
    /* Declaration of local variables*/
    unsigned int length = 0, Regbit = 0, reg = 0;

    /* Assigning values for transmitting buffer*/
    p_modbusTxBuf[0] = p_parseModbusTcpData->transactionID.v[1];
    p_modbusTxBuf[1] = p_parseModbusTcpData->transactionID.v[0];

    p_modbusTxBuf[2] = p_parseModbusTcpData->protocolID.v[1];
    p_modbusTxBuf[3] = p_parseModbusTcpData->protocolID.v[0];

    p_modbusTxBuf[4] = 0X0;
    p_modbusTxBuf[5] = p_parseModbusTcpData->length;
    p_modbusTxBuf[6] = p_parseModbusTcpData->unitID;
    p_modbusTxBuf[7] = p_parseModbusTcpData->functionCode;

    p_modbusTxBuf[8] = p_parseModbusTcpData->startAddress.v[1]; /* coil address Hi */
    p_modbusTxBuf[9] = p_parseModbusTcpData->startAddress.v[0]; /* coil address Lo */

    p_modbusTxBuf[10] = p_parseModbusTcpData->forceData[0].v[1]; /* Force data Hi (FF/00) */
    p_modbusTxBuf[11] = p_parseModbusTcpData->forceData[0].v[0]; /* Force data Lo (00) */

    Regbit = (p_parseModbusTcpData->startAddress.Val - 1) % 16; /* 20 - 1 % 16 = 4th bit */
    reg = (p_parseModbusTcpData->startAddress.Val - 1) / 16;    /* 20 - 1 /16 = 1st  reg */

    if ((p_parseModbusTcpData->forceData[0].Val == 0xff00) || (p_parseModbusTcpData->forceData[0].Val == 0x0000)) /*checks for illegal data*/
    {
        if (p_parseModbusTcpData->forceData[0].Val == 0xFF00)
        {
            SET(p_dataMemory[reg], Regbit);
        }
        else
        {
            CLEAR(p_dataMemory[reg], Regbit);
        }
    }
    else
    {
        p_parseModbusTcpData->functionCode = p_parseModbusTcpData->functionCode + 0x80;
        modbusError(p_parseModbusTcpData, p_modbusTxBuf, Illegal_Data_Value);
    }

    length = 0x6 + p_modbusTxBuf[5];
    return length;
}
