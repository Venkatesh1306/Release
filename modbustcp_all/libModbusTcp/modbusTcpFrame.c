/*
Function name : uint16_t modbusTcpFrame(const uint8_t *p_modbusRxBuf, uint16_t *p_dataMemory, uint8_t *p_modbusTxBuf, uint16_t *modBusframeLength)
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
 *      Example - modbusTxframeLength = modbusTcpFrame (&modbusTcpRxBuf[0], &dataMemory[0], &modbusTcpTxBuf[0],modBusframeLength);
 * Required      :  modbusTcpRxBuf,dataMemory
 * Error Handling: This function checks for the modbus exception cases in the query message and provide response
 * according to the nature of the error and exception code.
 */

#include "modbusTcp.h"

/*Global Declaration*/
mbPacketParse_t p_parseModbusTcpData;

uint16_t modbusTcpFrame(const uint8_t *p_modbusRxBuf, uint16_t *p_dataMemory, uint8_t *p_modbusTxBuf, uint16_t *modBusframeLength) {

    modbusTcpParse(&p_parseModbusTcpData, p_modbusRxBuf); /* Parse Function*/

    /* Function Code Error */
    if (!(ReadCoilStatus == p_parseModbusTcpData.functionCode ||
            ReadInputStatus == p_parseModbusTcpData.functionCode ||
            ReadHoldingRegister == p_parseModbusTcpData.functionCode ||
            ReadInputRegisters == p_parseModbusTcpData.functionCode ||
            ForceSingleCoil == p_parseModbusTcpData.functionCode ||
            PresetSingleRegister == p_parseModbusTcpData.functionCode ||
            ForceMultipleCoils == p_parseModbusTcpData.functionCode ||
            PresetMultipleRegisters == p_parseModbusTcpData.functionCode)) {
        p_parseModbusTcpData.functionCode = p_parseModbusTcpData.functionCode + 0x80;
        modbusError(&p_parseModbusTcpData, p_modbusTxBuf, Illegal_Function_Code);
        *modBusframeLength = 0x9;
    }
        /* ModtbusTcptx packet size overflow considered as Data Error */
    else if (p_parseModbusTcpData.numberofRegister.Val > (MaxSizeTcpTx - 8)) {
        p_parseModbusTcpData.functionCode = p_parseModbusTcpData.functionCode + 0x80;
        modbusError(&p_parseModbusTcpData, p_modbusTxBuf, Illegal_Data_Value);
        *modBusframeLength = 0x9;
    }
        /* Address Error for Function code - 03,04,10(Hex) */
    else if (ReadHoldingRegister == p_parseModbusTcpData.functionCode ||
            ReadInputRegisters == p_parseModbusTcpData.functionCode ||
            PresetMultipleRegisters == p_parseModbusTcpData.functionCode) {
        if ((p_parseModbusTcpData.startAddress.Val > (int) (DataRegistersize)) ||
                ((p_parseModbusTcpData.startAddress.Val + p_parseModbusTcpData.numberofRegister.Val) > (int) (DataRegistersize))) {
            p_parseModbusTcpData.functionCode = p_parseModbusTcpData.functionCode + 0x80;
            modbusError(&p_parseModbusTcpData, p_modbusTxBuf, Illegal_Data_Address);
            *modBusframeLength = 0x9;
        }
    }
        /* Address Error for Function code - 01,02,0f(Hex) */
    else if (ReadCoilStatus == p_parseModbusTcpData.functionCode ||
            ReadInputStatus == p_parseModbusTcpData.functionCode ||
            ForceMultipleCoils == p_parseModbusTcpData.functionCode) {
        if ((p_parseModbusTcpData.startAddress.Val > (int) (CoilDatasize)) ||
                ((p_parseModbusTcpData.startAddress.Val + p_parseModbusTcpData.numberofRegister.Val) > (int) (CoilDatasize))) {
            p_parseModbusTcpData.functionCode = p_parseModbusTcpData.functionCode + 0x80;
            modbusError(&p_parseModbusTcpData, p_modbusTxBuf, Illegal_Data_Address);
            *modBusframeLength = 0x9;
        }
    }
        /* Address Error for Function code - 05(Hex) */
    else if (p_parseModbusTcpData.functionCode == ForceSingleCoil) {
        if (p_parseModbusTcpData.startAddress.Val > (int) (CoilDatasize)) {

            p_parseModbusTcpData.functionCode = p_parseModbusTcpData.functionCode + 0x80;
            modbusError(&p_parseModbusTcpData, p_modbusTxBuf, Illegal_Data_Address);
            *modBusframeLength = 0x9;
        }
    }
        /* Address Error for Function code - 06(Hex) */
    else if (p_parseModbusTcpData.functionCode == PresetSingleRegister) {
        if (p_parseModbusTcpData.startAddress.Val > (int) (DataRegistersize)) {
            p_parseModbusTcpData.functionCode = p_parseModbusTcpData.functionCode + 0x80;
            modbusError(&p_parseModbusTcpData, p_modbusTxBuf, Illegal_Data_Address);
            *modBusframeLength = 0x9;
        }
    }

    /* Response function, specific to function code */
    switch (p_parseModbusTcpData.functionCode) {

        case ReadHoldingRegister:

            *modBusframeLength = readHoldingRegisters(p_modbusTxBuf, p_dataMemory, &p_parseModbusTcpData);
            break;

        case PresetSingleRegister:

            *modBusframeLength = presetSingleRegister(p_modbusTxBuf, p_dataMemory, &p_parseModbusTcpData);
            break;

        case PresetMultipleRegisters:

            *modBusframeLength = presetMultipleRegisters(p_modbusTxBuf, p_dataMemory, &p_parseModbusTcpData);
            break;

        case ReadInputStatus:

            *modBusframeLength = readInputStatus(p_modbusTxBuf, p_dataMemory, &p_parseModbusTcpData);
            break;

        case ReadCoilStatus:

            *modBusframeLength = readCoilStatus(p_modbusTxBuf, p_dataMemory, &p_parseModbusTcpData);
            break;

        case ReadInputRegisters:

            *modBusframeLength = readInputReg(p_modbusTxBuf, p_dataMemory, &p_parseModbusTcpData);
            break;

        case ForceMultipleCoils:

            *modBusframeLength = forceMultipleCoils(p_modbusTxBuf, p_dataMemory, &p_parseModbusTcpData);
            break;

        case ForceSingleCoil:

            *modBusframeLength = forceSingleCoil(p_modbusTxBuf, p_dataMemory, &p_parseModbusTcpData);
            break;

        default:
            break;
    }
    return *modBusframeLength;
}
