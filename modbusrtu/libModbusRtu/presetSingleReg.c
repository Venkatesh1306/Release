/*

 QUERY FRAME :


| Slave Address | Function Code | Starting Address (Hi)  | Starting Address (Lo)  | Preset Value (Hi) | Preset Value (Lo) | CRC (Hi) | CRC (Lo) |
|---------------|---------------|------------------------|------------------------|-------------------|-------------------|----------|----------|
|     1 byte    |    1 byte     |        1 byte          |        1 byte          |      1 byte       |      1 byte       |  1 byte  |  1 byte  |

RESPONSE FRAME:

| Slave Address | Function Code | Starting Address (Hi)  | Starting Address (Lo)  | Preset Value (Hi) | Preset Value (Lo) | CRC (Hi) | CRC (Lo) |
|---------------|---------------|------------------------|------------------------|-------------------|-------------------|----------|----------|
|     1 byte    |    1 byte     |        1 byte          |        1 byte          |      1 byte       |      1 byte       |  1 byte  |  1 byte  |

Presets a value into a single holding register (4X reference).
* INPUT FRAME = {0x11, 0x06, 0x00, 0x02, 0x09, 0x0D, 0xED, 0x0F}
* DATA REGISTER = {0x0000, 0x0001, 0x0002, 0x0003, 0x0004, 0x0005, 0x0006, 0x0007, 0x0008, 0x0009, 0x0009, 0x0008, 0x0007, 0x0007, 0x0006, 0x0005, 0x0004, 0x0003, 0x0002, 0x0001, 0x0025, 0x0035, 0x0036, 0x9957, 0x7890};


The query message specifies the register reference to be preset. Registers are addressed starting at zero: register 1 is addressed as 0.
The requested preset value is specified in the query data field (4th & 5th byte)
DATA REGISTER AFTER PRESETTING ,
DATA REGISTER = {0x0000, 0x0001, 0x090D, 0x0003, 0x0004, 0x0005, 0x0006, 0x0007, 0x0008, 0x0009, 0x0009, 0x0008, 0x0007, 0x0007, 0x0006, 0x0005, 0x0004, 0x0003, 0x0002, 0x0001, 0x0025, 0x0035, 0x0036, 0x9957, 0x7890};
The normal response is an echo of the query, returned after the register contentshave been preset.
* RESPONSE FRAME ={0x11, 0x06, 0x00, 0x02, 0x09, 0x0D, 0xED, 0x0F}
*/

#include "modbusRtu.h"

uint16_t presetSingleRegisters(uint8_t *p_modbusTxBuf, uint16_t *p_dataMemory, mbPacketParse_t *p_parseModbusRtuData)
{
    uint16_t length = 0;

    /* Assigning values for modbustx buffer */
    p_modbusTxBuf[0] = p_parseModbusRtuData->slave_addr.Val;
    p_modbusTxBuf[1] = p_parseModbusRtuData->functionCode;

    if (p_parseModbusRtuData->preset_Data.Val >= IllegalDataCheck)
    {
        p_parseModbusRtuData->functionCode = p_parseModbusRtuData->functionCode + 0x80;
        modbusError(p_parseModbusRtuData, p_modbusTxBuf, Illegal_Data_Value);
        length = 0x04;
    }
    else
    {
        p_dataMemory[p_parseModbusRtuData->startAddress.Val] = (p_parseModbusRtuData->preset_Data.v[0] + p_parseModbusRtuData->preset_Data.v[1] * 0x100);
        /* Assigning values for modbustx buffer */
        p_modbusTxBuf[2] = p_parseModbusRtuData->startAddress.v[1];
        p_modbusTxBuf[3] = p_parseModbusRtuData->startAddress.v[0];

        p_modbusTxBuf[4] = p_parseModbusRtuData->preset_Data.v[1]; /* Preset Data Hi */

        p_modbusTxBuf[5] = p_parseModbusRtuData->preset_Data.v[0]; /* Preset Data Lo */

        p_parseModbusRtuData->crc.Val = generateCRC(&p_modbusTxBuf[0], 6);

        p_modbusTxBuf[6] = p_parseModbusRtuData->crc.bytes.LB;

        p_modbusTxBuf[7] = p_parseModbusRtuData->crc.bytes.HB;

        length = 0x08;
    }

    return length;
}
