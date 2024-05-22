/*
Function name    : uint16_t modbusRtuParse(mbPacketParse_t *p_parseModbusRtuData, const uint8_t *p_modbusRxBuf)
 * Return Type   : Returns 0
 * Parameters    :
 *      p_modbusRxBuf        -  received input frame that contains message format of query from the client
 *      p_parseModbusRtuData -  p_parseModbusRtuData serves as a container for parsed data extracted from a received Modbus Rtu packet
 * Description   :
 *      This function parses Modbus Rtu packet data stored in p_modbusRxBuf and populates the fields of the mbPacketParse_t structure pointed to by p_parseModbusRtuData.
        Depending on the function code extracted from the packet data, it handles either single register or multiple register preset operations, extracting relevant information
        and storing it appropriately in the structure.
 * Usage         :
 *      Example  -  modbusRtuParse (&p_parseModbusRtuData, p_modbusRxBuf);
 * Required      :  modbusRtuRxBuf
*/

#include "modbusRtu.h"

/* Global variable Declaration */
unsigned int c2, d2, bytesrx;
unsigned char exceptioncode;

uint16_t modbusRtuParse(mbPacketParse_t *p_parseModbusRtuData, const uint8_t *p_modbusRxBuf)
{
    /* Parsing the recived buffer */
    p_parseModbusRtuData->slave_addr.Val = p_modbusRxBuf[0];

    p_parseModbusRtuData->functionCode = p_modbusRxBuf[1];

    p_parseModbusRtuData->startAddress.v[1] = p_modbusRxBuf[2];
    p_parseModbusRtuData->startAddress.v[0] = p_modbusRxBuf[3];

    if (p_parseModbusRtuData->functionCode == PresetSingleRegister)
    {
        p_parseModbusRtuData->preset_Data.v[1] = p_modbusRxBuf[4];
        p_parseModbusRtuData->preset_Data.v[0] = p_modbusRxBuf[5]; /* Data for preset value for single register */
    }
    else if (p_parseModbusRtuData->functionCode == PresetMultipleRegisters)
    {

        p_parseModbusRtuData->numberofRegister.v[1] = p_modbusRxBuf[4];
        p_parseModbusRtuData->numberofRegister.v[0] = p_modbusRxBuf[5];
        p_parseModbusRtuData->byteCount = p_modbusRxBuf[6];

        for (c2 = 0; c2 < p_parseModbusRtuData->numberofRegister.Val; c2++)
        {

            d2 = c2 * 2;
            p_parseModbusRtuData->data[c2].v[1] = p_modbusRxBuf[7 + d2];
            p_parseModbusRtuData->data[c2].v[0] = p_modbusRxBuf[8 + d2]; /* Data for preset value for multiple register */
        }
    }
    else
    {
        p_parseModbusRtuData->numberofRegister.v[1] = p_modbusRxBuf[4];
        p_parseModbusRtuData->numberofRegister.v[0] = p_modbusRxBuf[5];
    }

    return 0;
}
