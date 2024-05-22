/*
Function name : uint16_t modbusRtuFrame(const uint8_t *p_modbusRxBuf, uint16_t *p_dataMemory, uint8_t *p_modbusTxBuf, uint16_t *modBusframeLength)
 * Return Type   : Returns the modBusframeLength i.e the length of the frame to be transmitted.
 * Parameters    :
 *      p_modbusRxBuf      -  received input frame that contains message format of query from the client
 *      p_modbusTxBuf      -  response frame that is sent to client from the server after processing the query frame
 *      p_dataMemory       -  memory register to configure,monitor, and control device I/O
 *      modBusframeLength  -  the length of the Modbus Transmission frame i.e response frame
 * Description   :
 *      This function receives the query message and the Datamemory from the client. It processes the query frame
 * by parsing and checks for errors. If no error is detected , it frames the response message to be transmitted to the client.
 * Usage         :
 *      Example - modbusTxframeLength = modbusRtuFrame (&modbusRtuRxBuf[0], &dataMemory[0], &modbusRtuTxBuf[0],modBusframeLength);
 * Required      :  modbusRtuRxBuf,dataMemory
 * Error Handling: This function checks for the modbus exception cases in the query message and provide response
 * according to the nature of the error and exception code.
*/

#include "modbusRtu.h"
mbPacketParse_t p_parseModbusRtuData;

uint16_t modbusRtuFrame(const uint8_t *p_modbusRxBuf, uint16_t *p_dataMemory, uint8_t *p_modbusTxBuf, uint16_t *modBusframeLength)
{
    p_parseModbusRtuData.slave_addr.Val = p_modbusRxBuf[0];
    if (0x11 == p_parseModbusRtuData.slave_addr.Val) /* checks the slave address */
    {
        /* local variable declaration */
        uint16_t check = 0;
        unsigned int preMultiLength = 0;

        /* Parse Function */
        modbusRtuParse(&p_parseModbusRtuData, p_modbusRxBuf);

        if (!(p_parseModbusRtuData.functionCode == ReadHoldingRegister ||
              p_parseModbusRtuData.functionCode == PresetSingleRegister ||
              p_parseModbusRtuData.functionCode == PresetMultipleRegisters)) /* checks for function error */
        {
            p_parseModbusRtuData.functionCode = p_parseModbusRtuData.functionCode + 0x80;
            modbusError(&p_parseModbusRtuData, p_modbusTxBuf, Illegal_Function_Code);
            *modBusframeLength = 0x05;
        }
        else if (p_parseModbusRtuData.functionCode == ReadHoldingRegister ||
                 p_parseModbusRtuData.functionCode == PresetMultipleRegisters) /* checks for address error */
        {
            if ((p_parseModbusRtuData.startAddress.Val > (int)(DataRegistersize)) ||
                ((p_parseModbusRtuData.startAddress.Val + p_parseModbusRtuData.numberofRegister.Val) > (int)(DataRegistersize)))
            {
                p_parseModbusRtuData.functionCode = p_parseModbusRtuData.functionCode + 0x80;
                modbusError(&p_parseModbusRtuData, p_modbusTxBuf, Illegal_Data_Address);
                *modBusframeLength = 0x05;
            }
        }
        else if (p_parseModbusRtuData.functionCode == PresetSingleRegister) /* checks for address error */
        {
            if (p_parseModbusRtuData.startAddress.Val > (int)(DataRegistersize))
            {
                p_parseModbusRtuData.functionCode = p_parseModbusRtuData.functionCode + 0x80;
                modbusError(&p_parseModbusRtuData, p_modbusTxBuf, Illegal_Data_Address);
                *modBusframeLength = 0x05;
            }
        }

        preMultiLength = (p_parseModbusRtuData.functionCode != 0x10) ? 8 : (9 + p_parseModbusRtuData.byteCount); /* length for checkcrc of modbusrxbuf */
        check = checkCRC(&p_modbusRxBuf[0], preMultiLength);
        if (1 == check)
        {
            switch (p_parseModbusRtuData.functionCode)
            {
            case ReadHoldingRegister:
                *modBusframeLength = readHoldingRegisters(p_modbusTxBuf, p_dataMemory, &p_parseModbusRtuData);
                break;

            case PresetSingleRegister:
                *modBusframeLength = presetSingleRegisters(p_modbusTxBuf, p_dataMemory, &p_parseModbusRtuData);
                break;

            case PresetMultipleRegisters:
                *modBusframeLength = presetMultipleRegisters(p_modbusTxBuf, p_dataMemory, &p_parseModbusRtuData);
                break;

            default:
                break;
            }
        }
        return *modBusframeLength;
    }
    else
    {
        return 0;
    }
}
