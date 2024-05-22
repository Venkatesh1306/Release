/*
Function name : uint16_t modbusTcpFrame(const uint8_t *p_modbusRxBuf, uint16_t *p_dataMemory, uint8_t *p_modbusTxBuf, uint16_t *modBusframeLength)
 Return Type   : Returns the modBusframeLength i.e the length of the frame to be transmitted.
 Parameters    :
 *      p_modbusRxBuf      -  received input frame that contains message format of query from the client
 *      p_modbusTxBuf      -  response frame that is sent to client from the server after processing the query frame
 *      p_dataMemory       -  memory register to configure,monitor, and control device I/O
 *      modBusframeLength  -  the length of the Modbus Transmission frame i.e response frame
 Description   :
 *      This function receives the query message and the Datamemory from the client. It processes the query frame
 * by parsing and checks for errors. If no error is detected , it frames the response message to be transmitted to the client.
 Usage         :
 *      Example - modbusTxframeLength = modbusTcpFrame (&modbusTcpRxBuf[0], &dataMemory[0], &modbusTcpTxBuf[0],modBusframeLength);
 Required      :  modbusTcpRxBuf,dataMemory
 Error Handling: This function checks for the modbus exception cases in the query message and provide response
 *               according to the nature of the error and exception code.
*/

#include "ModbusTcp.h"
mbPacketParse_t p_parseModbusTcpData;

uint16_t modbusTcpFrame(const uint8_t *p_modbusRxBuf, uint16_t *p_dataMemory, uint8_t *p_modbusTxBuf, uint16_t *modBusframeLength)
{

  modbusTcpParse(&p_parseModbusTcpData, p_modbusRxBuf); /* Parsing Function */

  if (!(p_parseModbusTcpData.functionCode == ReadHoldingRegister ||
        p_parseModbusTcpData.functionCode == PresetSingleRegister ||
        p_parseModbusTcpData.functionCode == PresetMultipleRegisters)) /* Function code error */
  {
    p_parseModbusTcpData.functionCode = p_parseModbusTcpData.functionCode + 0x80;
    modbusError(&p_parseModbusTcpData, p_modbusTxBuf, Illegal_Function_Code);
    *modBusframeLength = 0x9;
  }

  else if (p_parseModbusTcpData.numberofRegister.Val > (MaxSizeTcpTx - 8)) /* Data error */
  {
    p_parseModbusTcpData.functionCode = p_parseModbusTcpData.functionCode + 0x80;
    modbusError(&p_parseModbusTcpData, p_modbusTxBuf, Illegal_Data_Value);
    *modBusframeLength = 0x9;
  }

  else if (p_parseModbusTcpData.functionCode == ReadHoldingRegister ||
           p_parseModbusTcpData.functionCode == PresetMultipleRegisters) /* Address error*/
  {
    if ((p_parseModbusTcpData.startAddress.Val > (int)(DataRegistersize)) ||
        ((p_parseModbusTcpData.startAddress.Val + p_parseModbusTcpData.numberofRegister.Val) > (int)(DataRegistersize)))
    {
      p_parseModbusTcpData.functionCode = p_parseModbusTcpData.functionCode + 0x80;
      modbusError(&p_parseModbusTcpData, p_modbusTxBuf, Illegal_Data_Address);
      *modBusframeLength = 0x9;
    }
  }
  else if (p_parseModbusTcpData.functionCode == PresetSingleRegister) /* Addresss error for FC-0x06 */
  {
    if (p_parseModbusTcpData.startAddress.Val > (int)(DataRegistersize))
    {
      p_parseModbusTcpData.functionCode = p_parseModbusTcpData.functionCode + 0x80;
      modbusError(&p_parseModbusTcpData, p_modbusTxBuf, Illegal_Data_Address);
      *modBusframeLength = 0x9;
    }
  }

  /* Response Function specific to function code */
  switch (p_parseModbusTcpData.functionCode)
  {
  case ReadHoldingRegister:

    *modBusframeLength = readHoldingRegisters(p_modbusTxBuf, p_dataMemory, &p_parseModbusTcpData);
    break;

  case PresetSingleRegister:

    *modBusframeLength = presetSingleRegister(p_modbusTxBuf, p_dataMemory, &p_parseModbusTcpData);
    break;

  case PresetMultipleRegisters:

    *modBusframeLength = presetMultipleRegisters(p_modbusTxBuf, p_dataMemory, &p_parseModbusTcpData);
    break;
  default:
    break;
  }
  return *modBusframeLength;
}
