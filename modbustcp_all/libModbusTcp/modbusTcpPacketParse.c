/*
Function name    : uint16_t modbusTcpParse(mbPacketParse_t *p_parseModbusTcpData, const uint8_t *p_modbusRxBuf)
 * Return Type   : Returns 0
 * Parameters    :
 *      p_modbusRxBuf        -  received input frame that contains message format of query from the client
 *      p_parseModbusTcpData -  p_parseModbusTcpData serves as a container for parsed data extracted from a received Modbus TCP packet
 * Description   :
 *      This function parses Modbus TCP packet data stored in p_modbusRxBuf and populates the fields of the mbPacketParse_t structure pointed to by p_parseModbusTcpData.
        Depending on the function code extracted from the packet data, it handles single register or multiple register preset operations and Force single or multiple coils extracting the datas
        and storing it appropriately in the structure.
 * Usage         :
 *      Example  -  modbusTcpParse (&p_parseModbusTcpData, p_modbusRxBuf);
 * Required      :  modbusTcpRxBuf
*/

#include "ModbusTcp.h"

/* Global declaration of variables*/
unsigned int c2, d2, bytesrx;
unsigned char exceptioncode;

uint16_t modbusTcpParse(mbPacketParse_t *p_parseModbusTcpData, const uint8_t *p_modbusRxBuf)
{
  /* Parsing of Recieving buffer */
  p_parseModbusTcpData->transactionID.v[1] = p_modbusRxBuf[0];
  p_parseModbusTcpData->transactionID.v[0] = p_modbusRxBuf[1];

  p_parseModbusTcpData->protocolID.v[1] = p_modbusRxBuf[2];
  p_parseModbusTcpData->protocolID.v[0] = p_modbusRxBuf[3];

  p_parseModbusTcpData->length = p_modbusRxBuf[5];

  p_parseModbusTcpData->unitID = p_modbusRxBuf[6];

  p_parseModbusTcpData->functionCode = p_modbusRxBuf[7];

  p_parseModbusTcpData->startAddress.v[1] = p_modbusRxBuf[8];
  p_parseModbusTcpData->startAddress.v[0] = p_modbusRxBuf[9];

  /* Allocates data for PresetSingleRegister */
  if (p_parseModbusTcpData->functionCode == PresetSingleRegister)
  {
    p_parseModbusTcpData->preset_Data.v[1] = p_modbusRxBuf[10];
    p_parseModbusTcpData->preset_Data.v[0] = p_modbusRxBuf[11];
  }

  /* Allocates data for PresetMultipleRegister */
  else if (p_parseModbusTcpData->functionCode == PresetMultipleRegisters)
  {

    p_parseModbusTcpData->numberofRegister.v[1] = p_modbusRxBuf[10];
    p_parseModbusTcpData->numberofRegister.v[0] = p_modbusRxBuf[11];

    p_parseModbusTcpData->byteCount = p_modbusRxBuf[12];

    if (p_parseModbusTcpData->numberofRegister.Val < 0x7d) /* checks for overflow of data array size*/
    {
      for (c2 = 0; c2 < p_parseModbusTcpData->numberofRegister.Val; c2++)
      {
        d2 = c2 * 2;

        p_parseModbusTcpData->data[c2].v[1] = p_modbusRxBuf[13 + d2];
        p_parseModbusTcpData->data[c2].v[0] = p_modbusRxBuf[14 + d2];
      }
    }
  }

  /* Allocates data for ForceSingleCoil */
  else if (p_parseModbusTcpData->functionCode == ForceSingleCoil)
  {
    p_parseModbusTcpData->forceData[0].v[1] = p_modbusRxBuf[10];
    p_parseModbusTcpData->forceData[0].v[0] = p_modbusRxBuf[11];
  }

  /* Allocates data for ForceMultipleCoils */
  else if (p_parseModbusTcpData->functionCode == ForceMultipleCoils)
  {
    p_parseModbusTcpData->numberofRegister.v[1] = p_modbusRxBuf[10];
    p_parseModbusTcpData->numberofRegister.v[0] = p_modbusRxBuf[11];

    p_parseModbusTcpData->byteCount = p_modbusRxBuf[12];
    if (p_parseModbusTcpData->numberofRegister.Val <= MaxSizeCoilData) /* checks for overflow of coildata array size*/
    {
      for (c2 = 0; c2 < p_parseModbusTcpData->byteCount / 2; c2++)
      {

        p_parseModbusTcpData->coilData[c2] = (p_modbusRxBuf[14 + c2 * 2] << 8) | p_modbusRxBuf[13 + c2 * 2];
      }
    }
  }

  /* Allocates Number of registers for required functions */
  else
  {

    p_parseModbusTcpData->numberofRegister.v[1] = p_modbusRxBuf[10];
    p_parseModbusTcpData->numberofRegister.v[0] = p_modbusRxBuf[11];
  }

  return 0;
}
