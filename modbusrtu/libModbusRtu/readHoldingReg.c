/*

QUERY FRAME :

|Slave Address |  Function Code   |   Starting Address (Hi)   |   Starting Address (Lo)   |   Quantity of Registers (Hi)  |   Quantity of Registers (Lo)  |   CRC (Cyclic Redundancy Check)|
|--------------|------------------|---------------------------|---------------------------|-------------------------------|-------------------------------|--------------------------------|
|    1 byte    |     1 byte       |         1 byte            |          1 byte           |            1 byte             |            1 byte             |     2 bytes                    |

RESPONSE FRAME :

| Slave Address | Function Code | Byte Count | Data (Hi) | Data (Lo) | ... | Data (Hi) | Data (Lo) | CRC (Cyclic Redundancy Check) |
|---------------|---------------|------------|------------|------------|-----|------------|------------|--------------------------------|
|     1 byte    |    1 byte     |   1 byte   |   1 byte   |   1 byte   | ... |   1 byte   |   1 byte   |           2 bytes              |

* Reads the binary contents of holding registers (4X) in the slave
 * INPUT FRAME  = {0x11, 0x03, 0x00, 0x6, 0x00, 0x03, 0x5A, 0xE7} - 8 bytes
 * DATAREGISTER = {0x0000, 0x0001, 0x0002, 0x0003, 0x0004, 0x0005, 0x0006, 0x0007, 0x0008, 0x0009, 0x0009, 0x0008, 0x0007, 0x0007, 0x0006, 0x0005, 0x0004, 0x0003, 0x0002, 0x0001, 0x0025, 0x0035, 0x0036, 0x9957, 0x7890}
 *
 * The Query Message specifies the starting register and Quantity of registers to be read and the CRC for the respective query frame
 * The register data in the response message are packed as two bytes per register
 * The first byte contains the high order bits and the second contains the low order bits
 * This Query Request to read 3 register values from starting address 0x06 (0x06, 0x07, 0x08)
 * The CRC for the Response Frame is calculated and appended to the response frame ( 0xd4, 0xb2 )
 * RESPONSE FRAME = {0x11, 0x03, 0x00, 0x06, 0x06, 0x00, 0x06, 0x00, 0x07, 0x00, 0x08, 0xd4, 0xb2} - 13 bytes ( 5 bytes + (2*No.of Registers) + 2 bytes )


*/
#include "modbusRtu.h"

uint16_t readHoldingRegisters(uint8_t *p_modbusTxBuf, uint16_t *p_dataMemory, mbPacketParse_t *p_parseModbusRtuData)
{
    /* local variable declaration */
    uint16_t length = 0;
    uint16_t txlength = 0;
    uint16_t a = 0, b = 0;

    /* Assigning values for modbustx buffer */
    p_modbusTxBuf[0] = p_parseModbusRtuData->slave_addr.Val;
    p_modbusTxBuf[1] = p_parseModbusRtuData->functionCode;
    p_modbusTxBuf[2] = p_parseModbusRtuData->numberofRegister.Val * 2; /* Byte Count = no of points(registers)*2 */

    for (a = 0; a < p_parseModbusRtuData->numberofRegister.Val; a++)
    {
        b = a * 2;

        p_modbusTxBuf[3 + b] = p_dataMemory[p_parseModbusRtuData->startAddress.Val + a] / 0x100;
        p_modbusTxBuf[4 + b] = p_dataMemory[p_parseModbusRtuData->startAddress.Val + a] % 0x100;
    }
    length = 0x03 + p_modbusTxBuf[2];

    p_parseModbusRtuData->crc.Val = generateCRC(&p_modbusTxBuf[0], length);

    p_modbusTxBuf[length] = p_parseModbusRtuData->crc.bytes.LB;

    p_modbusTxBuf[length + 1] = p_parseModbusRtuData->crc.bytes.HB;

    txlength = 0x05 + p_modbusTxBuf[2];
    return txlength;
}