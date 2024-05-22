/*

QUERY FRAME :

| Slave Address | Function Code | Starting Address (Hi)  |  Starting Address (Lo) | Quantity of Registers (Hi)  | Quantity of Registers (Lo)  | Byte Count  | Preset (register values)  | CRC (Cyclic Redundancy Check)  |
|---------------|---------------|------------------------|------------------------|-----------------------------|-----------------------------|-------------|---------------------------|--------------------------------|
|     1 byte    |    1 byte     |        1 byte          |        1 byte          |           1 byte            |           1 byte            |   1 byte    |     Variable              |           2 bytes              |

RESPONSE FRAME :

| Slave Address | Function Code | Starting Address (Hi)  | Starting Address (Lo)  | Quantity of Registers (Hi)  | Quantity of Registers (Lo)  | CRC (Cyclic Redundancy Check)  |
|---------------|---------------|------------------------|------------------------|-----------------------------|-----------------------------|--------------------------------|
|     1 byte    |    1 byte     |        1 byte          |        1 byte          |           1 byte            |           1 byte            |           2 bytes              |

FUNCTION CODE - 0x10

EXAMPLE :
*INPUT FRAME = {0x11,0x10,0x00,0x01,0x00,0x02,0x04,0x00,0x02,0x03,0x09,0x07,0x95}
*DATA REGISTER = {0x0000, 0x0001, 0x0002, 0x0003, 0x0004, 0x0005, 0x0006, 0x0007, 0x0008, 0x0009, 0x0009, 0x0008, 0x0007, 0x0007, 0x0006, 0x0005, 0x0004, 0x0003, 0x0002, 0x0001, 0x0025, 0x0035, 0x0036, 0x9957, 0x7890} ;

The query message specifies the register references to be preset. Registers are addressed starting at zero: register 1 is addressed as 0.
The requested preset values are specified in the query data field.
After Presetting,
DATA REGISTER = {0x0000, 0x0002, 0x0309, 0x0003, 0x0004, 0x0005, 0x0006, 0x0007, 0x0008, 0x0009, 0x0009, 0x0008, 0x0007, 0x0007, 0x0006, 0x0005, 0x0004, 0x0003, 0x0002, 0x0001, 0x0025, 0x0035, 0x0036, 0x9957, 0x7890} ;

*RESPONSE FRAME = {0x11,0x10,0x00,0x01,0x00,0x02,0x12,0x98}

*/

#include "modbusRtu.h"

uint16_t presetMultipleRegisters(uint8_t *p_modbusTxBuf, uint16_t *p_dataMemory, mbPacketParse_t *p_parseModbusRtuData)
{
    /* Local variable Declaration */
    uint16_t length = 0;
    uint16_t limit = 0;

    /* Assigning values for modbustx buffer */
    p_modbusTxBuf[0] = p_parseModbusRtuData->slave_addr.Val;
    p_modbusTxBuf[1] = p_parseModbusRtuData->functionCode;

    for (limit = 0; limit < p_parseModbusRtuData->numberofRegister.v[0]; limit++)
    {
        if (p_parseModbusRtuData->data[limit].Val >= IllegalDataCheck)
        {

            p_parseModbusRtuData->functionCode = p_parseModbusRtuData->functionCode + 0x80;
            modbusError(p_parseModbusRtuData, p_modbusTxBuf, Illegal_Data_Value); /* Data error */
            limit = p_parseModbusRtuData->numberofRegister.v[0] + 1;
            length = 0X03;
        }
        else
        {
            p_dataMemory[p_parseModbusRtuData->startAddress.Val + limit] = p_parseModbusRtuData->data[limit].v[0] + (p_parseModbusRtuData->data[limit].v[1] * 0x100);
        }
    }
    if (p_parseModbusRtuData->functionCode == 0x10)
    {
        /* Assigning values for modbustx buffer */
        p_modbusTxBuf[2] = p_parseModbusRtuData->startAddress.v[1];
        p_modbusTxBuf[3] = p_parseModbusRtuData->startAddress.v[0];
        p_modbusTxBuf[4] = p_parseModbusRtuData->numberofRegister.v[1];
        p_modbusTxBuf[5] = p_parseModbusRtuData->numberofRegister.v[0];

        p_parseModbusRtuData->crc.Val = generateCRC(&p_modbusTxBuf[0], 6);

        p_modbusTxBuf[6] = p_parseModbusRtuData->crc.bytes.LB;

        p_modbusTxBuf[7] = p_parseModbusRtuData->crc.bytes.HB;

        length = 0x08;
    }

    return length;
}
