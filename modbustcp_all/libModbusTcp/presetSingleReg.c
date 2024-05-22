/*QUERY FRAME:
| Transaction Identifier | Protocol Identifier | Length | Unit Identifier | Function Code | Address | Value |
|------------------------|---------------------|--------|-----------------|---------------|---------|-------|
|       2 bytes          |      2 bytes        |2 bytes |      1 byte     |     1 byte    |  2 bytes| 2 bytes|

RESPONSE FRAME:
| Transaction Identifier | Protocol Identifier | Length | Unit Identifier | Function Code | Address | Value |
|------------------------|---------------------|--------|-----------------|---------------|---------|-------|
|       2 bytes          |      2 bytes        |2 bytes |      1 byte     |     1 byte    |  2 bytes| 2 bytes|
 *
 *
 * Function Code - 06
 * DataRegister[25]={0x0000, 0x0001, 0x0002, 0x0003, 0x0004, 0x0005, 0x0006, 0x0007, 0x0008, 0x0009, 0x0009, 0x0008, 0x0007, 0x0007, 0x0006, 0x0005, 0x0004, 0x0003, 0x0002, 0x0001, 0x0025, 0x0035, 0x0036, 0x9957, 0x7890};
 * INPUT FRAME = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x10, 0x06, 0x00, 0x01, 0x00, 0x03}
 *
 * Preset Register 01 to 0x0003
 * RESPONSE FRAME = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x10, 0x06, 0x00, 0x01, 0x00, 0x03}
 * DATAREGISTER [] ={0x0000, 0x0003, 0x0002, 0x0003, 0x0004, 0x0005, 0x0006, 0x0007, 0x0008, 0x0009, 0x0009, 0x0008, 0x0007, 0x0007, 0x0006, 0x0005, 0x0004, 0x0003, 0x0002, 0x0001, 0x0025, 0x0035, 0x0036, 0x9957, 0x7890}
 *
 *When Error detected
 * RESPONSE FRAME = {0x0, 0x1, 0x2, 0x3, 0x0, 0x3, 0x10, 0x86, 0x3} - 9 bytes
 * DATAREGISTER UNMODIFIED.
 *
 *
 */

#include "modbusTcp.h"

uint16_t presetSingleRegister(uint8_t *p_modbusTxBuf, uint16_t *p_dataMemory, mbPacketParse_t *p_parseModbusTcpData) {

    uint16_t length = 0;

    /* Assigning values for transmitting buffer*/
    p_modbusTxBuf[0] = p_parseModbusTcpData->transactionID.v[1];
    p_modbusTxBuf[1] = p_parseModbusTcpData->transactionID.v[0];

    p_modbusTxBuf[2] = p_parseModbusTcpData->protocolID.v[1];
    p_modbusTxBuf[3] = p_parseModbusTcpData->protocolID.v[0];

    p_modbusTxBuf[4] = 0X0;
    p_modbusTxBuf[5] = p_parseModbusTcpData->length;

    p_modbusTxBuf[6] = p_parseModbusTcpData->unitID;
    p_modbusTxBuf[7] = p_parseModbusTcpData->functionCode;

    if (p_parseModbusTcpData->preset_Data.Val >= IllegalDataCheck) /* checks for illegal data value */ {
        p_parseModbusTcpData->functionCode = p_parseModbusTcpData->functionCode + 0x80;
        modbusError(p_parseModbusTcpData, p_modbusTxBuf, Illegal_Data_Value);
        length = 0x9;
    } else {
        p_dataMemory[p_parseModbusTcpData->startAddress.Val] = (p_parseModbusTcpData->preset_Data.v[0] + p_parseModbusTcpData->preset_Data.v[1] * 0x100);

        /* Assigning values for transmitting buffer*/
        p_modbusTxBuf[8] = p_parseModbusTcpData->startAddress.v[1];
        p_modbusTxBuf[9] = p_parseModbusTcpData->startAddress.v[0];

        p_modbusTxBuf[10] = p_parseModbusTcpData->preset_Data.v[1]; /* Preset Data Hi */

        p_modbusTxBuf[11] = p_parseModbusTcpData->preset_Data.v[0]; /* Preset Data Lo */
        length = 0x6 + p_parseModbusTcpData->length;
    }
    return length;
}
